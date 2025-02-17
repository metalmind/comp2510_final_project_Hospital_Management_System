//
// Created by Owen on 10/02/2025.
//


#include <stdio.h>
#include <string.h>
#include "../inc/patient.h"
#include "../inc/tools.h"

patient patientRecords[MAX_PATIENTS] = {};
int totalPatients                    = 0;

int idExists(patient arr[],
             int size,
             int id)
{
    for(int i = 0; i < size; i++)
    {
        if(arr[i].patientID == id)
        {
            return i;
        }
    }
    return ID_NOT_FOUND;
}

void addNewPatientRecord(void)
{
    if(totalPatients >= MAX_PATIENTS)
    {
        printf("The hospital is full! Cannot take any more patients.\n");
        return;
    }

    int id;
    char name[NAME_MAX_CHAR];
    int age;
    char diagnosis[DIAGNOSIS_MAX_CHAR];
    int roomNumber;

    id = getUniquePatientID();

    getStringInput("Enter patient name: ",
                   name,
                   NAME_MAX_CHAR);

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
    index = idExists(patientRecords,
                     totalPatients,
                     id);

    if(index != ID_NOT_FOUND)
    {
        removePatientRecord(index);
    }
    else
    {
        printf("Patient record not found.");
    }
}

void removePatientRecord(const int index)
{
    for(int i = index; i < totalPatients - ENTRY_REMOVAL_OFFSET; i++)
    {
        patientRecords[i] = patientRecords[i + NEXT_ENTRY_OFFSET];
    }

    printf("Patient successfully discharged - record removed.");
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
        unique = idExists(patientRecords,
                          totalPatients,
                          id) == ID_NOT_FOUND;

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
    while(sel != RETURN_TO_MENU);
}

void printPatientMenu()
{
    printf("Search By:\n");
    printf("1. Patient ID\n");
    printf("2. Patient Name\n");
    printf("3. Return to Menu\n");
}

void searchCriteriaSelection(int sel)
{
    switch(sel)
    {
        case SEARCH_BY_ID:
            searchPatientByID();
            break;
        case SEARCH_BY_NAME:
            searchPatientByName();
            break;
        case RETURN_TO_MENU:
            printf("Returning to menu...\n");
            break;
        default:
            printf("Invalid input! Try again.\n");
    }
}

void handlePatientSearchResult(int index)
{
    if(index != INVALID_INPUT)
    {
        printf("%-8s%-20s%-8s%-20s%-8s\n",
               "ID",
               "Name",
               "Age",
               "Diagnosis",
               "Room Number");
        printPatientRecord(index);
    }
    else
    {
        printf("Patient record not found.\n");
    }
}

void handleMultiplePatientSearchResults(int* indexes,
                                        int numRecordsFound)
{
    if(numRecordsFound != NO_RECORDS)
    {
        printf("%-8s%-20s%-8s%-20s%-8s\n",
               "ID",
               "Name",
               "Age",
               "Diagnosis",
               "Room Number");
        for(int i = 0; i < numRecordsFound; i++)
        {
            printPatientRecord(indexes[i]);
        }
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
    index = idExists(patientRecords,
                     totalPatients,
                     id);

    handlePatientSearchResult(index);
}

void searchPatientByName()
{
    int indexes[MAX_PATIENTS];
    int numRecordsFound;

    numRecordsFound = NO_RECORDS;

    char name[NAME_MAX_CHAR];

    getStringInput("Enter patient name: ",
                   name,
                   NAME_MAX_CHAR);

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

void printPatientRecord(int index)
{
    printf("%-8d%-20s%-8d%-20s%-8d\n",
           patientRecords[index].patientID,
           patientRecords[index].name,
           patientRecords[index].age,
           patientRecords[index].diagnosis,
           patientRecords[index].roomNumber);
}

void viewAllPatientRecords()
{
    if(totalPatients == 0)
    {
        printf("No patient records on file.\n");
        return;
    }

    printf("\nPatient Records:\n");
    printf("%-8s%-20s%-8s%-20s%-8s\n",
           "ID",
           "Name",
           "Age",
           "Diagnosis",
           "Room Number");

    for(int i = 0; i < totalPatients; i++)
    {
        printPatientRecord(i);
    }
}
