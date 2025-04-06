#include "../inc/doctor.h"
#include "../inc/schedule.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/patient.h"
#include "../inc/tools.h"

Node* doctorRecordsStart = NULL;
int totalDoctors = 0;

/*********Public Functions Begin************/
void doctorMenu()
{
    int sel;

    do
    {
        sel = INVALID_INPUT;

        printDoctorMenu();
        getInput("Enter your selection: ",
                 &sel);
        routeDoctorMenu(sel);
    }
    while(sel != RETURN_TO_MAIN_MENU);
}

void addNewDoctorRecord(void)
{
    // if(totalDoctors >= MAX_DOCTORS)
    // {
    //     printf("No open positions for new doctors! Cannot add any more doctors.\n");
    //     return;
    // }

    int id;
    char firstName[NAME_MAX_CHAR];
    char lastName[NAME_MAX_CHAR];
    char specialty[SPECIALTY_MAX_CHAR];

    id = getUniqueDoctorID();

    getDoctorName("Enter doctor first name: ",
                  firstName);

    getDoctorName("Enter doctor last name: ",
                  lastName);

    getStringInput("Enter doctor specialty: ",
                   specialty,
                   SPECIALTY_MAX_CHAR);

    createNewDoctorEntry(id,
                          firstName,
                          lastName,
                          specialty);
}

void createNewDoctorEntry(const int id,
                          const char firstName[NAME_MAX_CHAR],
                          const char lastName[NAME_MAX_CHAR],
                          const char specialty[SPECIALTY_MAX_CHAR])
{
    doctor* newDoctor;
    newDoctor = (doctor*)malloc(sizeof(doctor));

    if(newDoctor == NULL)
    {
        printf("Could not add new doctor - not enough memory!\n");
        return;
    }

    newDoctor->doctorID = id;
    strcpy(newDoctor->firstName,
           firstName);
    strcpy(newDoctor->lastName,
           lastName);
    strcpy(newDoctor->specialty,
           specialty);

    addDoctorToList(newDoctor);
}

void fireDoctor()
{
    int id;
    doctor* doctorRecord;

    id = getDoctorID();
    doctorRecord = getDoctor(id);

    if(doctorRecord != NULL)
    {
        removeDoctorRecord(doctorRecord);
        clearDoctorShifts(id);
    }
    else
    {
        printf("Doctor record not found.\n");
    }
}

void viewAllDoctorRecords()
{
    printf("\nDoctors\n");
    if(totalDoctors == 0)
    {
        printf("No doctor records on file.\n");
        return;
    }

    printDoctorRecordsHeader();

    for(Node* node = doctorRecordsStart; node != NULL; node = node->next)
    {
        doctor* doctorRecord;
        doctorRecord = node->record;
        printDoctorRecord(doctorRecord);
    }

    printDoctorRecordDivider();
}

int getTotalDoctors()
{
    return totalDoctors;
}

/*********Public Functions End**************/

/*********Private Functions Begin************/
void addDoctorToList(const doctor* const newDoctor)
{
    int id;
    Node* newNode;

    id = newDoctor->doctorID;
    newNode = (Node*)malloc(sizeof(Node));

    if(newNode == NULL)
    {
        printf("Could not add doctor - not enough memory!\n");
        return;
    }

    newNode->record = newDoctor; // assign patient pointer to node
    newNode->next = NULL;

    Node* previous;
    Node* current;

    findDoctorSortedPosition(id,
                             &previous,
                             &current);

    // insert new node at beginning of list
    if(previous == NULL)
    {
        newNode->next = doctorRecordsStart;
        doctorRecordsStart = newNode;
    }
    // insert new node between previous and current
    else
    {
        previous->next = newNode;
        newNode->next = current;
    }

    totalDoctors++;
    printf("Doctor added successfully!\n");
}

void findDoctorSortedPosition(int id,
                              Node** previous,
                              Node** current)
{
    *previous = NULL;
    *current = doctorRecordsStart;

    // loop to find sorted position in list
    while(*current != NULL)
    {
        doctor* thisDoctor;
        thisDoctor = (*current)->record;

        // if id is larger than current node, keep traversing the list
        if(id > thisDoctor->doctorID)
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

doctor* getDoctor(const int id)
{
    for(Node* node = doctorRecordsStart; node != NULL; node = node->next)
    {
        doctor* doctorRecord;
        doctorRecord = node->record;

        if(doctorRecord->doctorID == id)
        {
            return doctorRecord;
        }
    }

    return NULL;
}

int isUniqueDoctorId(const int id)
{
    if(getDoctor(id) == NULL)
    {
        return TRUE;
    }

    return FALSE;
}

void removeDoctorRecord(const doctor* const doctorRecord)
{
    Node* previous;
    previous = NULL;

    for(Node* node = doctorRecordsStart; node != NULL; node = node->next)
    {
        doctor* thisDoctor;
        thisDoctor = node->record;

        if(doctorRecord == thisDoctor)
        {
            if(previous == NULL)
            {
                // if the record to remove is the head, point head to next element
                doctorRecordsStart = doctorRecordsStart->next;
            }
            else
            {
                // set the previous record's next node reference to the node
                // following this node
                previous->next = node->next;
            }

            free(node);
            totalDoctors--;

            printf("Doctor successfully removed.\n");

            return;
        }

        previous = node;
    }
}

int getUniqueDoctorID()
{
    int id;

    char prompt[PROMPT_MAX_CHAR];

    sprintf(prompt, "Enter doctor ID (next available is %d): ",
            getNextAvailDocID());

    id = promptForUniqueInput(prompt,
                              "Invalid doctor ID! Please enter a positive integer.\n",
                              "Duplicate doctor ID! Please enter a unique ID.\n",
                              &isUniqueDoctorId,
                              DOC_ID_MIN_VALUE,
                              DOC_ID_MAX_VALUE);

    return id;
}

int getDoctorID()
{
    int id;

    id = promptForInput("Enter doctor ID: ",
                        "Invalid doctor ID! Please enter a positive integer.\n",
                        DOC_ID_MIN_VALUE,
                        DOC_ID_MAX_VALUE);

    return id;
}

doctor* getDoctorByID()
{
    int id;
    doctor* doctorRecord;

    id = getDoctorID();
    doctorRecord = getDoctor(id);

    return doctorRecord;
}

int getNextAvailDocID()
{
    for(int i = DOC_ID_MIN_VALUE; i <= DOC_ID_MAX_VALUE; i++)
    {
        if(getDoctor(i) == NULL)
        {
            return i;
        }
    }

    return DOC_ID_NOT_FOUND;
}

void getDoctorName(const char* prompt,
                   char* const name)
{
    promptForNameStr(prompt,
                     name,
                     NAME_MAX_CHAR);
}

void printDoctorRecord(doctor* doctor)
{
    printf("%-2s%-8d%-2s%-16s%-2s%-16s%-2s%-28s%c\n",
           "|",
           doctor->doctorID,
           "|",
           doctor->firstName,
           "|",
           doctor->lastName,
           "|",
           doctor->specialty,
           '|');
}

void printDoctorRecordsHeader()
{
    printDoctorRecordDivider();

    printf("%-2s%-8s%-2s%-16s%-2s%-16s%-2s%-28s%c\n",
           "|",
           "ID",
           "|",
           "First Name",
           "|",
           "Last Name",
           "|",
           "Specialty",
           '|');

    printDoctorRecordDivider();
}

void printDoctorRecordDivider()
{
    printf("+");
    printDashes(INT_FIELD_SPACING);
    printf("+");
    printDashes(NAME_FIELD_SPACING);
    printf("+");
    printDashes(NAME_FIELD_SPACING);
    printf("+");
    printDashes(STRING_FIELD_SPACING);
    printf("+");
    printf("\n");
}


void printDoctorMenu()
{
    printf("\nDoctor Menu\n");
    printf("%d. Return to Main Menu\n", RETURN_TO_MAIN_MENU);
    printf("%d. Add New Doctor\n", ADD_NEW_DOCTOR);
    printf("%d. Fire Doctor\n", FIRE_DOCTOR);
    printf("%d. View All Doctor Records\n", VIEW_ALL_DOCTOR_RECORDS);
}

void routeDoctorMenu(const int sel)
{
    switch(sel)
    {
    case ADD_NEW_DOCTOR:
        addNewDoctorRecord();
        break;
    case FIRE_DOCTOR:
        fireDoctor();
        break;
    case VIEW_ALL_DOCTOR_RECORDS:
        viewAllDoctorRecords();
        break;
    case RETURN_TO_MAIN_MENU:
        printf("Returning to menu...\n");
        break;
    default:
        printf("Invalid input! Try again.\n");
    }
}

void freeDoctorMemory()
{
    while(doctorRecordsStart != NULL)
    {
        Node* temp = doctorRecordsStart;
        doctorRecordsStart = doctorRecordsStart->next;

        free(temp->record);
        free(temp);
    }
}

void saveDoctorRecordToFile(const Node* startOfLinkedList,
                            const char* filePathStr)
{
    if(remove(filePathStr) != 0)
    {
        fopen(filePathStr, "w");
        printf("File created: %s\n", filePathStr);
    }

    for(Node* node = startOfLinkedList; node != NULL; node = node->next)
    {
        doctor* doctor;
        doctor = node->record;
        writeDoctorRecord(doctor, filePathStr);
    }
}

void writeDoctorRecord(const doctor* d,
                       const char* filePathStr)
{
    FILE* fPtr;

    if((fPtr = fopen(filePathStr, "a")) == NULL)
    {
        printf("File could not be opened %s\n", filePathStr);
    }
    else
    {
        puts("\nPreparing file...");
        int error;
        char dStr[400] = {0};
        char dIDStr[25] = {0};
        char dFirstNameStr[NAME_MAX_CHAR] = {0};
        char dLastNameStr[NAME_MAX_CHAR] = {0};
        char dSpecialtyStr[SPECIALTY_MAX_CHAR] = {0};

        puts("Preparing values...");
        snprintf(dIDStr, sizeof(dIDStr), "%d", d->doctorID);
        strcpy(dFirstNameStr, d->firstName);
        strcpy(dLastNameStr, d->lastName);
        strcpy(dSpecialtyStr, d->specialty);

        sanitizeStr(dFirstNameStr, ' ', '#');
        sanitizeStr(dLastNameStr, ' ', '#');
        sanitizeStr(dSpecialtyStr, ' ', '#');

        puts("Creating string...");
        strcat(dStr, dIDStr);
        strcat(dStr, " ");
        strcat(dStr, dFirstNameStr);
        strcat(dStr, " ");
        strcat(dStr, dLastNameStr);
        strcat(dStr, " ");
        strcat(dStr, dSpecialtyStr);
        strcat(dStr, "\n");
        error = fprintf(fPtr, "%s", dStr);
        if(error < 1)
        {
            puts("Error writing to file.");
        }
        else
        {
            puts("Doctor successfully saved.");
        }
    }
    fclose(fPtr);
}

void saveAllDoctorRecord()
{
    saveDoctorRecordToFile(doctorRecordsStart, DOCTOR_RECORD_FILE_PATH);
}

void readDoctorRecords()
{
    readDoctorFile(DOCTOR_RECORD_FILE_PATH);
}

void readDoctorFile(const char* filePathStr)
{
    FILE* fPtr;

    if((fPtr = fopen(filePathStr, "r")) == NULL)
    {
        printf("File could not be opened %s\n", filePathStr);
    }
    else
    {
        int id;
        char firstName[FULL_NAME_MAX_CHAR] = {0};
        char lastName[FULL_NAME_MAX_CHAR] = {0};
        char specialty[DIAGNOSIS_MAX_CHAR] = {0};
        char specialtyClean[DIAGNOSIS_MAX_CHAR] = {0};


        char doctorData[NUM_DOCTOR_FIELDS][DIAGNOSIS_MAX_CHAR];
        char buffer[BUFFER_SIZE];

        while(fgets(buffer, sizeof(buffer), fPtr) != NULL)
        {
            int doctorDataIndex;
            doctorDataIndex = 0;
            char* tokenPtr = strtok(buffer, " ");
            while(tokenPtr != NULL)
            {
                strcpy(doctorData[doctorDataIndex], tokenPtr);
                tokenPtr = strtok(NULL, " ");
                doctorDataIndex++;
            }

            id = atoi(doctorData[ID_INDEX]);
            if(isUniquePatientId(id))
            {
                int length;
                sanitizeStr(doctorData[FIRST_NAME_INDEX], '#', ' ');
                strcpy(firstName, doctorData[FIRST_NAME_INDEX]);

                sanitizeStr(doctorData[LAST_NAME_INDEX], '#', ' ');
                strcpy(lastName, doctorData[LAST_NAME_INDEX]);

                sanitizeStr(doctorData[DIAGNOSIS_INDEX], '#', ' ');

                strcpy(specialty, doctorData[DIAGNOSIS_INDEX]);
                length = strlen(specialty);
                strncpy(specialtyClean, specialty, length - 1);

                if(filePathStr == DOCTOR_RECORD_FILE_PATH)
                {
                    createNewDoctorEntry(id,
                          firstName,
                          lastName,
                          specialtyClean);
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

/*********Private Functions End**************/
