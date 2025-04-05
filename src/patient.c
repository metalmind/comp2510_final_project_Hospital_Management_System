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
    printf("\nActive Patients\n");
    if(totalPatients == 0)
    {
        printf("No patient records on file.\n");
        return;
    }

    printPatientRecordsHeader();

    for(Node* node = patientRecordsStart; node != NULL; node = node->next)
    {
        patient* patientRecord;
        patientRecord = node->record;
        printPatientRecord(patientRecord);
    }

    printPatientRecordDivider();
}

void viewAllDischargedPatientRecords()
{
    printf("\nDischarged Patients\n");
    if(dischargedPatients == 0)
    {
        printf("No discharged patient records on file.\n");
        return;
    }

    printDischargedPatientRecordsHeader();

    for(Node* node = dischargedPatientsStart; node != NULL; node = node->next)
    {
        patient* dischargedPatientRecord;
        dischargedPatientRecord = node->record;
        printDischargedPatientRecord(dischargedPatientRecord);
    }

    printDischargedPatientRecordDivider();
}

void searchForPatientRecord()
{
    int sel;

    do
    {
        sel = INVALID_INPUT;
        printPatientSearchMenu();
        getInput("Enter your selection: ",
                 &sel);
        searchCriteriaSelection(sel);
    }
    while(sel != RETURN_TO_MAIN_MENU);
}

void dischargePatient()
{
    int id;
    patient* patientRecord;

    id = getPatientID();
    patientRecord = getPatient(id);

    if(patientRecord != NULL)
    {
        removePatientRecord(patientRecord);
        addPatientToDischargedList(patientRecord);
    }
    else
    {
        printf("Patient record not found.\n");
    }
}

int getTotalPatients()
{
    return totalPatients;
}

void saveAllPatientRecord()
{
    savePatientRecordToFile(patientRecordsStart, PATIENT_RECORD_FILE_PATH);
}

void saveAllDischargedPatientRecord()
{
    savePatientRecordToFile(dischargedPatientsStart, DISCHARGED_PATIENT_FILE_PATH);
}

/*********Public Functions End**************/

/*********Private Functions Begin************/
void createNewPatientEntry(const int id,
                           const char name[25],
                           const int age,
                           const char diagnosis[25],
                           const int roomNumber,
                           const time_t admissionDate)
{
    patient* newPatient;
    newPatient = (patient*)malloc(sizeof(patient));

    if(newPatient == NULL)
    {
        printf("Could not add new patient - not enough memory!\n");
        return;
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

void createNewDischargedPatientEntry(const int id,
                           const char name[25],
                           const int age,
                           const char diagnosis[25],
                           const int roomNumber,
                           const time_t admissionDate,
                           const time_t dischargeDate)
{
    patient* newPatient;
    newPatient = (patient*)malloc(sizeof(patient));

    if(newPatient == NULL)
    {
        printf("Could not add new patient - not enough memory!\n");
        return;
    }

    newPatient->patientID = id;
    strcpy(newPatient->name,
           name);
    newPatient->age = age;
    strcpy(newPatient->diagnosis,
           diagnosis);
    newPatient->roomNumber = roomNumber;
    newPatient->admissionDate = admissionDate;
    newPatient->dischargeDate = dischargeDate;

    addPatientToDischargedList(newPatient);
}

void addPatientToList(const patient* const newPatient)
{
    int id;
    Node* newNode;

    id = newPatient->patientID;
    newNode = (Node*)malloc(sizeof(Node));

    if(newNode == NULL)
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
    if(previous == NULL)
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

void addPatientToDischargedList(const patient* const newPatient)
{
    int id;
    Node* newNode;

    id = newPatient->patientID;
    newNode = (Node*)malloc(sizeof(Node));

    if(newNode == NULL)
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
    if(previous == NULL)
    {
        newNode->next = dischargedPatientsStart;
        dischargedPatientsStart = newNode;
    }
    // insert new node between previous and current
    else
    {
        previous->next = newNode;
        newNode->next = current;
    }

    dischargedPatients++;
    printf("Patient discharged successfully!\n");
}

void findPatientSortedPosition(int id,
                               Node** previous,
                               Node** current)
{
    *previous = NULL;
    *current = patientRecordsStart;

    // loop to find sorted position in list
    while(*current != NULL)
    {
        patient* thisPatient;
        thisPatient = (*current)->record;

        // if id is larger than current node, keep traversing the list
        if(id > thisPatient->patientID)
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

patient* getPatient(const int id)
{
    for(Node* node = patientRecordsStart; node != NULL; node = node->next)
    {
        patient* patientRecord;
        patientRecord = node->record;

        if(patientRecord->patientID == id)
        {
            return patientRecord;
        }
    }

    return NULL;
}

patient* getDischargedPatient(const int id)
{
    for(Node* node = dischargedPatientsStart; node != NULL; node = node->next)
    {
        patient* patientRecord;
        patientRecord = node->record;

        if(patientRecord->patientID == id)
        {
            return patientRecord;
        }
    }

    return NULL;
}

int isUniquePatientId(const int id)
{
    if(getPatient(id) == NULL && getDischargedPatient(id) == NULL)
    {
        return TRUE;
    }

    return FALSE;
}

void removePatientRecord(const patient* const patientRecord)
{
    Node* previous;
    previous = NULL;

    for(Node* node = patientRecordsStart; node != NULL; node = node->next)
    {
        patient* thisPatient;
        thisPatient = node->record;

        if(patientRecord == thisPatient)
        {
            if(previous == NULL)
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

            time_t today = getCurrentDate();
            thisPatient->dischargeDate = today;
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
    for(int i = ID_MIN_VALUE; i <= ID_MAX_VALUE; i++)
    {
        if(getPatient(i) == NULL && getDischargedPatient(i) == NULL)
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

void printPatientSearchMenu()
{
    printf("\n%d. Return to Menu\n", RETURN_TO_MAIN_MENU);
    printf("%d. Search by Patient ID\n", SEARCH_BY_PATIENT_ID);
    printf("%d. Search by Patient Name\n", SEARCH_BY_PATIENT_NAME);
}

void searchCriteriaSelection(const int sel)
{
    switch(sel)
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
    if(patientRecord != NULL)
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
    if(numRecordsFound != NO_RECORDS)
    {
        printPatientRecordsHeader();

        for(int i = 0; i < numRecordsFound; i++)
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

    for(Node* node = patientRecordsStart; node != NULL; node = node->next)
    {
        patient* thisPatient;
        thisPatient = node->record;

        if(strcmp(thisPatient->name, name) == RECORD_FOUND)
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

    printf("%-2s%-8d%-2s%-28s%-2s%-8d%-2s%-28s%-2s%-8d%-2s%-20s%c\n",
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

void printDischargedPatientRecord(patient* patientRecord)
{
    char admissTime[DATE_MAX_CHARS] = {0};
    char dischargeTime[DATE_MAX_CHARS] = {0};

    dateFormat(patientRecord->admissionDate, admissTime);
    dateFormat(patientRecord->dischargeDate, dischargeTime);

    printf("%-2s%-8d%-2s%-28s%-2s%-8d%-2s%-28s%-2s%-8d%-2s%-20s%-2s%-20s%c\n",
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
           admissTime,
           "|",
           dischargeTime,
           '|');
}


void printPatientRecordsHeader()
{
    printPatientRecordDivider();

    printf("%-2s%-8s%-2s%-28s%-2s%-8s%-2s%-28s%-2s%-8s%-2s%-20s%c\n",
           "|",
           "ID",
           "|",
           "Name",
           "|",
           "Age",
           "|",
           "Diagnosis",
           "|",
           "Room #",
           "|",
           "Admission Date",
           '|');

    printPatientRecordDivider();
}

void printDischargedPatientRecordsHeader()
{
    printDischargedPatientRecordDivider();

    printf("%-2s%-8s%-2s%-28s%-2s%-8s%-2s%-28s%-2s%-8s%-2s%-20s%-2s%-20s%c\n",
           "|",
           "ID",
           "|",
           "Name",
           "|",
           "Age",
           "|",
           "Diagnosis",
           "|",
           "Room #",
           "|",
           "Admission Date",
           "|",
           "Discharge Date",
           '|');

    printDischargedPatientRecordDivider();
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
    printDashes(INT_FIELD_SPACING);
    printf("+");
    printDashes(DATE_FIELD_SPACING);
    printf("+");
    printf("\n");
}

void printDischargedPatientRecordDivider()
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
    printDashes(INT_FIELD_SPACING);
    printf("+");
    printDashes(DATE_FIELD_SPACING);
    printf("+");
    printDashes(DATE_FIELD_SPACING);
    printf("+");
    printf("\n");
}

void readPatientRecords()
{
    readPatientFile(PATIENT_RECORD_FILE_PATH);
}

void readDischargedPatientRecords()
{
    readPatientFile(DISCHARGED_PATIENT_FILE_PATH);
}

void readPatientFile(const char* filePathStr)
{
    FILE* fPtr;

    if((fPtr = fopen(filePathStr, "r")) == NULL)
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
        time_t dischargeTime;

        char patientData[NUM_PATIENT_FIELDS][DIAGNOSIS_MAX_CHAR];
        char buffer[BUFFER_SIZE];

        while(fgets(buffer, sizeof(buffer), fPtr) != NULL)
        {
            int patientDataIndex;
            patientDataIndex = 0;
            char* tokenPtr = strtok(buffer, " ");
            while(tokenPtr != NULL)
            {
                strcpy(patientData[patientDataIndex], tokenPtr);
                tokenPtr = strtok(NULL, " ");
                patientDataIndex++;
            }

            id = atoi(patientData[ID_INDEX]);
            if(isUniquePatientId(id))
            {
                sanitizeStr(patientData[NAME_INDEX], '#', ' ');
                strcpy(name, patientData[NAME_INDEX]);

                age = atoi(patientData[AGE_INDEX]);

                sanitizeStr(patientData[DIAGNOSIS_INDEX], '#', ' ');
                strcpy(diagnosis, patientData[DIAGNOSIS_INDEX]);

                roomNumber = atoi(patientData[ROOM_NUMBER_INDEX]);

                admissionTime = strToTime(patientData[ADMIT_TIME_INDEX]);

                dischargeTime = strToTime(patientData[DISCHARGE_TIME_INDEX]);


                if(filePathStr == PATIENT_RECORD_FILE_PATH)
                {
                    createNewPatientEntry(id,
                                      name,
                                      age,
                                      diagnosis,
                                      roomNumber,
                                      admissionTime);
                }
                else if(filePathStr == DISCHARGED_PATIENT_FILE_PATH)
                {
                    createNewDischargedPatientEntry(id,
                                      name,
                                      age,
                                      diagnosis,
                                      roomNumber,
                                      admissionTime,
                                      dischargeTime);
                }
                else
                {
                    printf("Invalid file path");
                }

            }

            if(feof(fPtr))
            {
                printf("\nEnd of file reached.\n");
            }
            else if(ferror(fPtr))
            {
                printf("\nAn error occurred.\n");
            }

        }
    }
    fclose(fPtr);
}

void writePatientRecord(const patient* p, const char* filePathStr)
{
    FILE* fPtr;

    if((fPtr = fopen(filePathStr, "a")) == NULL)
    {
        puts("\nFile could not be opened.");
    }
    else
    {
        puts("\nPreparing file...");
        int error;
        char pStr[400] = {0};
        char pIDStr[25] = {0};
        char pNameStr[FULL_NAME_MAX_CHAR] = {0};
        char pAgeStr[3] = {0};
        char pDiagnosisStr[DIAGNOSIS_MAX_CHAR] = {0};
        char pRoomNumStr[3] = {0};
        char admissTime[DATE_MAX_CHARS] = {0};
        char dischargeTime[DATE_MAX_CHARS] = {0};

        puts("Preparing values...");
        snprintf(pIDStr, sizeof(pIDStr), "%d", p->patientID);
        snprintf(pAgeStr, sizeof(pAgeStr), "%d", p->age);
        snprintf(pRoomNumStr, sizeof(pRoomNumStr), "%d", p->roomNumber);
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
        error = fprintf(fPtr, "%s", pStr);
        // puts(pStr);
        if(error < 1)
        {
            puts("Error writing to file.");
        }
        else
        {
            puts("Patient successfully saved.");
        }
    }
    fclose(fPtr);
}

void savePatientRecordToFile(const Node* startOfLinkedList, const char* filePathStr)
{
    if(remove(filePathStr) != 0)
    {
        fopen(filePathStr, "w");
        printf("File created: %s\n", filePathStr);
    }

    for(Node* node = startOfLinkedList; node != NULL; node = node->next)
    {
        patient* patient;
        patient = node->record;
        writePatientRecord(patient, filePathStr);
    }
}

void freePatientMemory()
{
    while(patientRecordsStart != NULL)
    {
        Node* temp = patientRecordsStart;
        patientRecordsStart = patientRecordsStart->next;

        free(temp->record);
        free(temp);
    }

    while(dischargedPatientsStart != NULL)
    {
        Node* temp = dischargedPatientsStart;
        dischargedPatientsStart = dischargedPatientsStart->next;

        free(temp->record);
        free(temp);
    }
}


/*********Private Functions End************/
