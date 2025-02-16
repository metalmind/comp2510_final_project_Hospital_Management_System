//
// Created by Owen on 10/02/2025.
//


#include <stdio.h>
#include <string.h>
#include "patient.h"
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

    printf("Enter patient name: ");
    fgets(name,
          NAME_MAX_CHAR,
          stdin);
    name[strcspn(name,
                 "\n")] = TERMINAL_CHAR;

    age = getPatientAge();

    printf("Enter patient diagnosis: ");
    fgets(diagnosis,
          DIAGNOSIS_MAX_CHAR,
          stdin);
    diagnosis[strcspn(diagnosis,
                      "\n")] = TERMINAL_CHAR;

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
    int index;

    do
    {
        index = INVALID_INPUT;
        printPatientMenu();

        getInput("Enter your selection: ",
                 &sel);
        index = searchCriteriaSelection(sel);
        handlePatientSearchResult(index,
                                  sel);
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

int searchCriteriaSelection(int sel)
{
    int index = INVALID_INPUT;

    switch(sel)
    {
        case SEARCH_BY_ID:
            index = searchPatientByID();
            break;
        case SEARCH_BY_NAME:
            index = searchPatientByName();
            break;
        case RETURN_TO_MENU:
            printf("Returning to menu...\n");
            break;
        default:
            printf("Invalid input! Try again.\n");
    }

    return index;
}

void handlePatientSearchResult(int index,
                               int sel)
{
    if(index != INVALID_INPUT)
    {
        printf("%-5s%-20s%-5s%-20s%-5s\n",
               "ID",
               "Name",
               "Age",
               "Diagnosis",
               "Room Number");
        printPatientRecord(index);
    }
    else if(sel == SEARCH_BY_ID || sel == SEARCH_BY_NAME)
    {
        printf("Patient record not found.\n");
    }
}

int searchPatientByID()
{
    int index;
    int id;

    id    = getPatientID();
    index = idExists(patientRecords,
                     totalPatients,
                     id);

    return index;
}

int searchPatientByName()
{
    char name[NAME_MAX_CHAR];
    int index;

    index = INVALID_INPUT;

    printf("Enter Patient Name: ");
    fgets(name,
          NAME_MAX_CHAR,
          stdin);
    name[strcspn(name,
                 "\n")] = TERMINAL_CHAR;

    for(int i = 0; i < totalPatients; i++)
    {
        if(strcmp(patientRecords[i].name,
                  name) == RECORD_FOUND)
        {
            index = i;
            break;
        }
    }

    return index;
}

void printPatientRecord(int id)
{
    printf("%-5d%-20s%-5d%-20s%-5d\n",
           patientRecords[id].patientID,
           patientRecords[id].name,
           patientRecords[id].age,
           patientRecords[id].diagnosis,
           patientRecords[id].roomNumber);
}

void viewAllPatientRecords()
{
    if(totalPatients == 0)
    {
        printf("No patient records on file.\n");
        return;
    }

    printf("\nPatient Records:\n");
    printf("%-5s%-20s%-5s%-20s%-5s\n",
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
