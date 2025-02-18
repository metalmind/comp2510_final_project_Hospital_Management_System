//
// Created by Owen on 10/02/2025.
//

#include <stdio.h>
#include <string.h>
#include "../inc/patient.h"
#include "../inc/tools.h"

patient patientRecords[MAX_PATIENTS] = {};
int totalPatients                    = 0;

int idExists(const int id)
{
    for(int i = 0; i < totalPatients; i++)
    {
        if(patientRecords[i].patientID == id)
        {
            return i;
        }
    }
    return ID_NOT_FOUND;
}

patient* getPatient(int index)
{
    if(index != ID_NOT_FOUND)
    {
        return &patientRecords[index];
    }

    return NULL;
}

void addNewPatientRecord(void)
{
    if(totalPatients >= MAX_PATIENTS)
    {
        printf("The hospital is full! Cannot take any more patients.\n");
        return;
    }

    int id;
    char name[FULL_NAME_MAX_CHAR];
    int age;
    char diagnosis[DIAGNOSIS_MAX_CHAR];
    int roomNumber;

    id = getUniquePatientID();

    getPatientName(name);

    age = getPatientAge();

    getStringInput("Enter patient diagnosis: ",
                   diagnosis,
                   DIAGNOSIS_MAX_CHAR);

    roomNumber = getPatientRoomNumber();

    patientRecords[totalPatients].patientID = id;
    strcpy(patientRecords[totalPatients].name,
           name);
    patientRecords[totalPatients].age = age;
    strcpy(patientRecords[totalPatients].diagnosis,
           diagnosis);
    patientRecords[totalPatients].roomNumber = roomNumber;
    totalPatients++;

    printf("Patient added successfully!\n");
}

void dischargePatient()
{
    int index;
    int id;

    id    = getPatientID();
    index = idExists(id);

    if(index != ID_NOT_FOUND)
    {
        removePatientRecord(index);
    }
    else
    {
        printf("Patient record not found.\n");
    }
}

void removePatientRecord(const int index)
{
    for(int i = index; i < totalPatients - ENTRY_REMOVAL_OFFSET; i++)
    {
        patientRecords[i] = patientRecords[i + NEXT_ENTRY_OFFSET];
    }

    printf("Patient successfully discharged - record removed.\n");
    totalPatients--;
}

int getUniquePatientID()
{
    int id;
    int valid;
    int unique;

    valid  = FALSE;
    unique = FALSE;

    do
    {
        id = ID_NOT_FOUND;

        int numItemsRead;

        numItemsRead = getInput("Enter patient ID: ",
                                &id);
        unique = idExists(id) == ID_NOT_FOUND;

        valid = validateData(numItemsRead,
                             id,
                             ID_MIN_VALUE,
                             ID_MAX_VALUE,
                             "Invalid patient ID! Please enter a positive integer.\n");

        if(valid && !unique)
        {
            printf("Duplicate patient ID! Please enter a unique ID.\n");
        }
    }
    while(!(valid && unique));

    return id;
}

int getPatientID()
{
    int id;
    int valid;

    id    = ID_NOT_FOUND;
    valid = FALSE;

    do
    {
        int numItemsRead;

        numItemsRead = getInput("Enter patient ID: ",
                                &id);

        valid = validateData(numItemsRead,
                             id,
                             ID_MIN_VALUE,
                             ID_MAX_VALUE,
                             "Invalid patient ID! Please enter a positive integer.\n");
    }
    while(!valid);

    return id;
}

void getPatientName(char* const name)
{
    int valid;

    valid = FALSE;

    do
    {
        getStringInput("Enter patient name: ",
               name,
               FULL_NAME_MAX_CHAR);
        valid = validateName(name);

        if(!valid)
        {
            printf("Invalid name! Only alphabetic characters allowed.\n");
        }
    }
    while(!valid);
}

int getPatientAge()
{
    int age;
    int valid;

    age   = INVALID_INPUT;
    valid = FALSE;

    do
    {
        int numItemsRead;

        numItemsRead = getInput("Enter patient age: ",
                                &age);

        valid = validateData(numItemsRead,
                             age,
                             MIN_AGE_YEARS,
                             MAX_AGE_YEARS,
                             "Invalid age! Please enter a positive integer.\n");
    }
    while(!valid);

    return age;
}

int getPatientRoomNumber()
{
    int roomNumber;
    int valid;

    roomNumber = INVALID_INPUT;
    valid      = FALSE;

    do
    {
        int numItemsRead;

        numItemsRead = getInput("Enter patient room number: ",
                                &roomNumber);

        valid = validateData(numItemsRead,
                             roomNumber,
                             ROOM_NUMBER_MIN,
                             ROOM_NUMBER_MAX,
                             "Invalid room number! Please enter a positive integer.\n");
    }
    while(!valid);

    return roomNumber;
}

void searchForPatientRecord()
{
    int sel;

    do
    {
        printPatientMenu();

        getInput("Enter your selection: ",
                 &sel);
        searchCriteriaSelection(sel);
    }
    while(sel != RETURN_TO_MAIN_MENU);
}

void printPatientMenu()
{
    printf("%d. Return to Menu\n", RETURN_TO_MAIN_MENU);
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

void handlePatientSearchResult(const int index)
{
    if(index != INVALID_INPUT)
    {
        printPatientRecordsHeader();
        printPatientRecord(index);
        printPatientRecordDivider();
    }
    else
    {
        printf("Patient record not found.\n");
    }
}

void handleMultiplePatientSearchResults(const int* const indexes,
                                        const int numRecordsFound)
{
    if(numRecordsFound != NO_RECORDS)
    {
        printPatientRecordsHeader();

        for(int i = 0; i < numRecordsFound; i++)
        {
            printPatientRecord(indexes[i]);
        }

        printPatientRecordDivider();
    }
    else
    {
        printf("Patient record not found.\n");
    }
}

void searchPatientByID()
{
    int index;
    int id;

    id    = getPatientID();
    index = idExists(id);

    handlePatientSearchResult(index);
}

void searchPatientByName()
{
    int indexes[MAX_PATIENTS];
    int numRecordsFound;

    numRecordsFound = NO_RECORDS;

    char name[FULL_NAME_MAX_CHAR];

    getStringInput("Enter patient name: ",
                   name,
                   FULL_NAME_MAX_CHAR);

    for(int i = 0; i < totalPatients; i++)
    {
        if(strcmp(patientRecords[i].name,
                  name) == RECORD_FOUND)
        {
            indexes[numRecordsFound] = i;
            numRecordsFound++;
        }
    }

    handleMultiplePatientSearchResults(indexes, numRecordsFound);
}

void printPatientRecord(const int index)
{
    printf("%-2s%-8d%-2s%-20s%-2s%-8d%-2s%-20s%-2s%-16d%c\n",
           "|",
           patientRecords[index].patientID,
           "|",
           patientRecords[index].name,
           "|",
           patientRecords[index].age,
           "|",
           patientRecords[index].diagnosis,
           "|",
           patientRecords[index].roomNumber,
           '|');
}

void viewAllPatientRecords()
{
    if(totalPatients == 0)
    {
        printf("No patient records on file.\n");
        return;
    }

    printPatientRecordsHeader();

    for(int i = 0; i < totalPatients; i++)
    {
        printPatientRecord(i);
    }

    printPatientRecordDivider();
}

void printPatientRecordsHeader()
{
    printPatientRecordDivider();

    printf("%-2s%-8s%-2s%-20s%-2s%-8s%-2s%-20s%-2s%-16s%c\n",
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
    printf("\n");
}
