
#include <stdio.h>
#include <string.h>
#include "menu.h"

#define NAME_MAX_CHAR 50
#define DIAGNOSIS_MAX_CHAR 100

#define MAX_PATIENTS 50

#define MIN_AGE_YEARS 0

#define TERMINAL_CHAR 0
#define ID_NOT_FOUND -1
#define ID_MIN_VALUE 0
#define ROOM_NUMBER_MIN 1

#define SEARCH_BY_ID 1
#define SEARCH_BY_NAME 2
#define RECORD_FOUND 0

struct patient
{
    int patientID;
    char name[NAME_MAX_CHAR];
    int age;
    char diagnosis[DIAGNOSIS_MAX_CHAR];
    int roomNumber;
};

void addNewPatientRecord(void);
int idExists(struct patient arr[], int size, int id);
void searchForPatientRecord(void);
void printPatientRecord(int id);
void viewAllPatientRecords(void);

struct patient patientRecords[MAX_PATIENTS];
int totalPatients = 0;

int main(void)
{
    addNewPatientRecord();

    printf("PatientID: %d\n", patientRecords[0].patientID);
    printf("Patient Name: %s\n", patientRecords[0].name);
    printf("Patient Age: %d\n", patientRecords[0].age);
    printf("Patient Diagnosis: %s\n", patientRecords[0].diagnosis);
    printf("Patient Room #: %d\n", patientRecords[0].roomNumber);

    viewAllPatientRecords();

    searchForPatientRecord();

    return 0;
}

/**
 * Searches for a patientID in the array and returns its index if found;
 * otherwise, it returns ID_NOT_FOUND.
 *
 * @param arr Array of Patient Structs
 * @param size The number of patient records in the array as an int
 * @param id The ID we want to check for existence
 * @return id index if found, otherwise ID_NOT_FOUND
 *
 * @author Ayesha Anzer
 * @author Owen Wou
 */
int idExists(struct patient arr[], int size, int id)
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

/**
 * Adds a new patient to the patientRecord array.
 * @author Ayesha Anzer
 * @author Owen Wou
 */
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

    printf("Enter the ID of the patient (positive integer): ");
    scanf("%d", &id);
    getchar();

    if(id < ID_MIN_VALUE ||
        idExists(patientRecords, totalPatients, id) != ID_NOT_FOUND)
    {
        printf("Invalid or duplicate patient ID!\n");
        return;
    }

    printf("Enter patient name: ");
    fgets(name, NAME_MAX_CHAR, stdin);
    name[strcspn(name, "\n")] = TERMINAL_CHAR;

    do
    {
        printf("Enter patient age: ");
        scanf("%d", &age);
        getchar();
    }
    while(age < MIN_AGE_YEARS);

    printf("Enter patient diagnosis: ");
    fgets(diagnosis, DIAGNOSIS_MAX_CHAR, stdin);
    diagnosis[strcspn(diagnosis, "\n")] = TERMINAL_CHAR;

    do
    {
        printf("Enter patient room number: ");
        scanf("%d", &roomNumber);
        getchar();
    }
    while(roomNumber < ROOM_NUMBER_MIN);

    patientRecords[totalPatients].patientID = id;
    strcpy(patientRecords[totalPatients].name, name);
    patientRecords[totalPatients].age = age;
    strcpy(patientRecords[totalPatients].diagnosis, diagnosis);
    patientRecords[totalPatients].roomNumber = roomNumber;
    totalPatients++;

    printf("Patient added successfully!\n");
}

/**
 * Prompts the user to choose between two different search criteria:
 * 1) search by patient ID and 2) search by patient name. Then, checks if
 * patient exists in the database and printing the requested record.
 */
void searchForPatientRecord()
{
    int choice;
    int id;
    int index;
    char name[NAME_MAX_CHAR];

    index = ID_NOT_FOUND;

    printf("Search By:\n");
    printf("1. Patient ID\n");
    printf("2. Patient Name\n");
    scanf("%d", &choice);
    getchar();

    if(choice == SEARCH_BY_ID)
    {
        printf("Enter Patient ID: ");
        scanf("%d", &id);
        getchar();
        index = idExists(patientRecords, totalPatients, id);
    }
    else if(choice == SEARCH_BY_NAME)
    {
        printf("Enter Patient Name: ");
        fgets(name, NAME_MAX_CHAR, stdin);
        name[strcspn(name, "\n")] = TERMINAL_CHAR;

        for(int i = 0; i < totalPatients; i++)
        {
            if (strcmp(patientRecords[i].name, name) == RECORD_FOUND)
            {
                index = i;
                break;
            }
        }
    }

    if (index != ID_NOT_FOUND)
    {
        printf("%-5s%-20s%-5s%-20s%-5s\n",
               "ID",
               "Name",
               "Age",
               "Diagnosis",
               "Room Number");
        printPatientRecord(index);
    }
    else
    {
        printf("Patient not found.\n");
    }
}

/**
 * Prints the patient record corresponding to the specified patient ID.
 * @param id patient id
 */
void printPatientRecord(int id)
{
    printf("%-5d%-20s%-5d%-20s%-5d\n",
           patientRecords[id].patientID,
           patientRecords[id].name,
           patientRecords[id].age,
           patientRecords[id].diagnosis,
           patientRecords[id].roomNumber);
}

/**
 * Prints all patient records in the patientRecord array.
 */
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