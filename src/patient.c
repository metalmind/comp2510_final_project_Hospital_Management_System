//
// Created by Owen on 10/02/2025.
//

#include <stdio.h>
#include <string.h>
#include "../inc/patient.h"

#include <stdlib.h>

#include "../inc/tools.h"

Node* patientRecordsStart = NULL;
Node* dischargedPatientsStart = NULL;
int totalPatients = 0;
int dischargedPatients = 0;


/*********Public Functions Begin************/
void addNewPatientRecord(void)
{
    // if(totalPatients >= MAX_PATIENTS)
    // {
    //     printf("The hospital is full! Cannot take any more patients.\n");
    //     return;
    // }

    int id;
    char name[FULL_NAME_MAX_CHAR];
    int age;
    char diagnosis[DIAGNOSIS_MAX_CHAR];
    int roomNumber;

    id = getUniquePatientID();

    getPatientName("Enter patient name: ",
                   name);

    age = getPatientAge();

    getStringInput("Enter patient diagnosis: ",
                   diagnosis,
                   DIAGNOSIS_MAX_CHAR);

    roomNumber = getPatientRoomNumber();

    createNewPatientEntry(id, name, age, diagnosis, roomNumber, time(NULL));
}

void viewAllPatientRecords()
{
    if (totalPatients == 0)
    {
        printf("No patient records on file.\n");
        return;
    }

    printPatientRecordsHeader();

    for (Node* node = patientRecordsStart; node != NULL; node = node->next)
    {
        patient* patientRecord;
        patientRecord = node->record;
        printPatientRecord(patientRecord);
    }

    printPatientRecordDivider();
}

void searchForPatientRecord()
{
    int sel;
    sel = INVALID_INPUT;

    do
    {
        printPatientMenu();
        getInput("Enter your selection: ",
                 &sel);
        searchCriteriaSelection(sel);
    }
    while (sel != RETURN_TO_MAIN_MENU);
}

void dischargePatient()
{
    int id;
    patient* patientRecord;

    id = getPatientID();
    patientRecord = getPatient(id);

    if (patientRecord != NULL)
    {
        removePatientRecord(patientRecord);
        addPatientToDischargedList(patientRecord);
    }
    else
    {
        printf("Patient record not found.\n");
    }
}

/*********Public Functions End**************/

/*********Private Functions Begin************/
void createNewPatientEntry(const int id, const char name[25], const int age, const char diagnosis[25],
                           const int roomNumber, const time_t admissionDate)
{
    patient* newPatient;
    newPatient = (patient*)malloc(sizeof(patient));

    if (newPatient == NULL)
    {
        printf("Could not add new patient - not enough memory!\n");
    }

    newPatient->patientID = id;
    strcpy(newPatient->name,
           name);
    newPatient->age = age;
    strcpy(newPatient->diagnosis,
           diagnosis);
    newPatient->roomNumber = roomNumber;
    newPatient->admissionDate = admissionDate;

    addPatientToList(newPatient);
}

void addPatientToList(const patient* const newPatient)
{
    int id;
    Node* newNode;

    id = newPatient->patientID;
    newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Could not add patient - not enough memory!\n");
        return;
    }

    newNode->record = newPatient; // assign patient pointer to node
    newNode->next = NULL;

    Node* previous;
    Node* current;

    findPatientSortedPosition(id,
                              &previous,
                              &current);

    // insert new node at beginning of list
    if (previous == NULL)
    {
        newNode->next = patientRecordsStart;
        patientRecordsStart = newNode;
    }
    // insert new node between previous and current
    else
    {
        previous->next = newNode;
        newNode->next = current;
    }

    totalPatients++;
    printf("Patient added successfully!\n");
}

void findPatientSortedPosition(int id,
                               Node** previous,
                               Node** current)
{
    *previous = NULL;
    *current = patientRecordsStart;

    // loop to find sorted position in list
    while (*current != NULL)
    {
        patient* thisPatient;
        thisPatient = (*current)->record;

        // if id is larger than current node, keep traversing the list
        if (id > thisPatient->patientID)
        {
            *previous = *current;
            *current = (*current)->next;
        }
        else
        {
            break;
        }
    }
}

void addPatientToDischargedList(const patient* const dischargedPatient)
{
    Node* newNode;
    newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Could not log discharged patient - not enough memory!\n");
        return;
    }

    newNode->record = dischargedPatient; // assign patient pointer to node
    newNode->next = dischargedPatientsStart; // add to start of list
    dischargedPatientsStart = newNode; // move pointer to start

    dischargedPatients++;
}

patient* getPatient(const int id)
{
    for (Node* node = patientRecordsStart; node != NULL; node = node->next)
    {
        patient* patientRecord;
        patientRecord = node->record;

        if (patientRecord->patientID == id)
        {
            return patientRecord;
        }
    }

    return NULL;
}

int isUniquePatientId(const int id)
{
    if (getPatient(id) == NULL)
    {
        return TRUE;
    }

    return FALSE;
}

void removePatientRecord(const patient* const patientRecord)
{
    Node* previous;
    previous = NULL;

    for (Node* node = patientRecordsStart; node != NULL; node = node->next)
    {
        patient* thisPatient;
        thisPatient = node->record;

        if (patientRecord == thisPatient)
        {
            if (previous == NULL)
            {
                // if the record to remove is the head, point head to next element
                patientRecordsStart = patientRecordsStart->next;
            }
            else
            {
                // set the previous record's next node reference to the node
                // following this node
                previous->next = node->next;
            }

            free(node);
            thisPatient->dischargeDate = time(NULL);
            totalPatients--;

            printf("Patient successfully discharged - record removed.\n");

            return;
        }

        previous = node;
    }
}

int getUniquePatientID()
{
    int id;

    char prompt[PROMPT_MAX_CHAR];

    sprintf(prompt, "Enter patient ID (next available is %d): ",
            getNextAvailPatientID());

    id = promptForUniqueInput(prompt,
                              "Invalid patient ID! Please enter a positive integer.\n",
                              "Duplicate patient ID! Please enter a unique ID.\n",
                              &isUniquePatientId,
                              ID_MIN_VALUE,
                              ID_MAX_VALUE);

    return id;
}

int getPatientID()
{
    int id;

    id = promptForInput("Enter patient ID: ",
                        "Invalid patient ID! Please enter a positive integer.\n",
                        ID_MIN_VALUE,
                        ID_MAX_VALUE);

    return id;
}

int getNextAvailPatientID()
{
    for (int i = ID_MIN_VALUE; i <= ID_MAX_VALUE; i++)
    {
        if (getPatient(i) == NULL)
        {
            return i;
        }
    }

    return ID_NOT_FOUND;
}

void getPatientName(const char* prompt,
                    char* const name)
{
    promptForNameStr(prompt,
                     name,
                     FULL_NAME_MAX_CHAR);
}

int getPatientAge()
{
    int age;

    age = promptForInput("Enter patient age: ",
                         "Invalid age! Please enter a positive integer.\n",
                         MIN_AGE_YEARS,
                         MAX_AGE_YEARS);

    return age;
}

int getPatientRoomNumber()
{
    int roomNumber;

    roomNumber = promptForInput("Enter patient room number: ",
                                "Invalid room number! Please enter a positive integer.\n",
                                ROOM_NUMBER_MIN,
                                ROOM_NUMBER_MAX);

    return roomNumber;
}

void printPatientMenu()
{
    printf("\n%d. Return to Menu\n", RETURN_TO_MAIN_MENU);
    printf("%d. Search by Patient ID\n", SEARCH_BY_PATIENT_ID);
    printf("%d. Search by Patient Name\n", SEARCH_BY_PATIENT_NAME);
}

void searchCriteriaSelection(const int sel)
{
    switch (sel)
    {
    case SEARCH_BY_PATIENT_ID:
        searchPatientByID();
        break;
    case SEARCH_BY_PATIENT_NAME:
        searchPatientByName();
        break;
    case RETURN_TO_MAIN_MENU:
        printf("Returning to menu...\n");
        break;
    default:
        printf("Invalid input! Try again.\n");
    }
}

void handlePatientSearchResult(const patient* const patientRecord)
{
    if (patientRecord != NULL)
    {
        printPatientRecordsHeader();
        printPatientRecord(patientRecord);
        printPatientRecordDivider();
    }
    else
    {
        printf("Patient record not found.\n");
    }
}

void handleMultiplePatientSearchResults(const patient** const patientsFound,
                                        const int numRecordsFound)
{
    if (numRecordsFound != NO_RECORDS)
    {
        printPatientRecordsHeader();

        for (int i = 0; i < numRecordsFound; i++)
        {
            printPatientRecord(*(patientsFound + i));
        }

        printPatientRecordDivider();
    }
    else
    {
        printf("Patient record not found.\n");
    }

    free(patientsFound);
}

void searchPatientByID()
{
    int id;
    patient* patientRecord;

    id = getPatientID();
    patientRecord = getPatient(id);

    handlePatientSearchResult(patientRecord);
}

void searchPatientByName()
{
    patient** patientsFound;
    int numRecordsFound;

    patientsFound = NULL;
    numRecordsFound = NO_RECORDS;

    char name[FULL_NAME_MAX_CHAR];

    getStringInput("Enter patient name: ",
                   name,
                   FULL_NAME_MAX_CHAR);

    for (Node* node = patientRecordsStart; node != NULL; node = node->next)
    {
        patient* thisPatient;
        thisPatient = node->record;

        if (strcmp(thisPatient->name, name) == RECORD_FOUND)
        {
            patientsFound = realloc(patientsFound,
                                    (numRecordsFound + 1) * sizeof(patient*));
            patientsFound[numRecordsFound] = thisPatient;
            numRecordsFound++;

            printf("Name Found: %s\n", thisPatient->name);
        }
    }

    handleMultiplePatientSearchResults(patientsFound,
                                       numRecordsFound);
}

void printPatientRecord(patient* patientRecord)
{
    char date[DATE_MAX_CHARS];
    dateFormat(patientRecord->admissionDate,
               date);

    printf("%-2s%-8d%-2s%-28s%-2s%-8d%-2s%-28s%-2s%-16d%-2s%-28s%c\n",
           "|",
           patientRecord->patientID,
           "|",
           patientRecord->name,
           "|",
           patientRecord->age,
           "|",
           patientRecord->diagnosis,
           "|",
           patientRecord->roomNumber,
           "|",
           date,
           '|');
}

void printPatientRecordsHeader()
{
    printPatientRecordDivider();

    printf("%-2s%-8s%-2s%-28s%-2s%-8s%-2s%-28s%-2s%-16s%-2s%-28s%c\n",
           "|",
           "ID",
           "|",
           "Name",
           "|",
           "Age",
           "|",
           "Diagnosis",
           "|",
           "Room Number",
           "|",
           "Admission Date",
           '|');

    printPatientRecordDivider();
}

void printPatientRecordDivider()
{
    printf("+");
    printDashes(INT_FIELD_SPACING);
    printf("+");
    printDashes(STRING_FIELD_SPACING);
    printf("+");
    printDashes(INT_FIELD_SPACING);
    printf("+");
    printDashes(STRING_FIELD_SPACING);
    printf("+");
    printDashes(ROOM_NUM_FIELD_SPACING);
    printf("+");
    printDashes(STRING_FIELD_SPACING);
    printf("+");
    printf("\n");
}

void readPatientRecords()
{
    FILE* fPtr;

    if ((fPtr = fopen("../res/patientRecords.txt", "r")) == NULL)
    {
        puts("File could not be opened.");
    }
    else
    {
        int id;
        char name[FULL_NAME_MAX_CHAR];
        int age;
        char diagnosis[DIAGNOSIS_MAX_CHAR];
        int roomNumber;
        time_t admissionTime;

        char patientData[NUM_PATIENT_FIELDS][DIAGNOSIS_MAX_CHAR];
        char buffer[BUFFER_SIZE];

        while (fgets(buffer, sizeof(buffer), fPtr) != NULL)
        {
            int patientDataIndex;
            patientDataIndex = 0;
            char* tokenPtr = strtok(buffer, " ");
            while (tokenPtr != NULL)
            {
                strcpy(patientData[patientDataIndex], tokenPtr);
                tokenPtr = strtok(NULL, " ");
                patientDataIndex++;
            }

            if (feof(fPtr))
            {
                printf("\nEnd of file reached.\n");
            }
            else if (ferror(fPtr))
            {
                printf("\nAn error occurred.\n");
            }

            id = atoi(patientData[ID_INDEX]);
            if (isUniquePatientId(id))
            {
                sanitizeStr(patientData[NAME_INDEX], '#', ' ');
                strcpy(name, patientData[NAME_INDEX]);

                age = atoi(patientData[AGE_INDEX]);

                sanitizeStr(patientData[DIAGNOSIS_INDEX], '#', ' ');
                strcpy(diagnosis, patientData[DIAGNOSIS_INDEX]);

                roomNumber = atoi(patientData[ROOM_NUMBER_INDEX]);
                admissionTime = strToTime(patientData[ADMIT_TIME_INDEX]);

                createNewPatientEntry(id, name, age, diagnosis, roomNumber, admissionTime);
            }
        }
    }
    fclose(fPtr);
    viewAllPatientRecords();
}

void writePatientRecord(const patient* p)
{
    FILE* fPtr;

    if ((fPtr = fopen("../res/patientRecords.txt", "w")) == NULL)
    {
        puts("File could not be opened.");
    }
    else
    {
        puts("Preparine file...");
        int error;
        char pStr[400];
        char pIDStr[25];
        char pNameStr[FULL_NAME_MAX_CHAR];
        char pAgeStr[3];
        char pDiagnosisStr[DIAGNOSIS_MAX_CHAR];
        char pRoomNumStr[3];
        char admissTime[DATE_MAX_CHARS];
        char dischargeTime[DATE_MAX_CHARS];

        puts("Preparing values...");
        itoa(p->patientID, pIDStr, 10);
        itoa(p->age, pAgeStr, 10);
        itoa(p->roomNumber, pRoomNumStr, 10);
        strcpy(pNameStr, p->name);
        strcpy(pDiagnosisStr, p->diagnosis);
        sanitizeStr(pNameStr, ' ', '#');
        sanitizeStr(pDiagnosisStr, ' ', '#');

        dateFormat(p->admissionDate, admissTime);
        dateFormat(p->dischargeDate, dischargeTime);

        puts("Creating string...");
        strcat(pStr, pIDStr);
        strcat(pStr, " ");
        strcat(pStr, pNameStr);
        strcat(pStr, " ");
        strcat(pStr, pAgeStr);
        strcat(pStr, " ");
        strcat(pStr, pDiagnosisStr);
        strcat(pStr, " ");
        strcat(pStr, pRoomNumStr);
        strcat(pStr, " ");
        strcat(pStr, admissTime);
        strcat(pStr, " ");
        strcat(pStr, dischargeTime);
        strcat(pStr, "\n");
        puts("Getting file ready...");
        error = fprintf(fPtr, pStr);
        puts(pStr);
        if (error < 1)
        {
            puts("Error writing to file.");
        }
        else
        {
            puts("Patient sucessfully saved.");
        }
    }
    fclose(fPtr);
}

void saveAllPatientRecord()
{
    int patientID = 1;
    patient* patient;

    patient = getPatient(patientID);

    for(int patientID = 1; getPatient(patientID) != NULL; patientID++)
    {
        patient = getPatient(patientID);
        writePatientRecord(patient);
    }
}

/*********Private Functions End************/
