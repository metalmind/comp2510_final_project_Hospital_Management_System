
#include <stdio.h>
#include <string.h>
#include "menu.h"

#define NAME_MAX_CHAR 50
#define DIAGNOSIS_MAX_CHAR 100

#define MAX_PATIENTS 50

#define MIN_AGE_YEARS 0

#define TERMINAL_CHAR 0
#define ID_MIN_VALUE 0
#define ID_NOT_FOUND (-1)

#define INVALID_INPUT (-1)
#define READ_SUCCESS 1

#define ROOM_NUMBER_MIN 1

#define SEARCH_BY_ID 1
#define SEARCH_BY_NAME 2
#define RETURN_TO_MENU 3

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
int getPatientID(void);
int getPatientAge(void);
int getPatientRoomNumber(void);
void searchForPatientRecord(void);
int searchPatientByID(void);
int searchPatientByName(void);
void printPatientRecord(int id);
void viewAllPatientRecords(void);
void clearInputBuffer(void);

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

    id = getPatientID();

    printf("Enter patient name: ");
    fgets(name, NAME_MAX_CHAR, stdin);
    name[strcspn(name, "\n")] = TERMINAL_CHAR;

    age = getPatientAge();

    printf("Enter patient diagnosis: ");
    fgets(diagnosis, DIAGNOSIS_MAX_CHAR, stdin);
    diagnosis[strcspn(diagnosis, "\n")] = TERMINAL_CHAR;

    roomNumber = getPatientRoomNumber();

    patientRecords[totalPatients].patientID = id;
    strcpy(patientRecords[totalPatients].name, name);
    patientRecords[totalPatients].age = age;
    strcpy(patientRecords[totalPatients].diagnosis, diagnosis);
    patientRecords[totalPatients].roomNumber = roomNumber;
    totalPatients++;

    printf("Patient added successfully!\n");
}

/**
 * Prompts user for patient ID, with checks to ensure patient ID is valid
 * according to the following criteria:
 * 1) Patient ID is a positive integer (greater than or equal to ID_MIN_VALUE)
 * 2) Patient with the specified ID does not already exist
 *
 * @return patient ID
 */
int getPatientID()
{
    int id;

    id = ID_NOT_FOUND;

    do
    {
        printf("Enter patient ID: ");

        // scanf returns number of items successfully assigned
        int input = scanf("%d", &id);

        if(input != READ_SUCCESS ||
            id < ID_MIN_VALUE ||
            (idExists(patientRecords, totalPatients, id) != ID_NOT_FOUND))
        {
            printf("Invalid or duplicate patient ID! Please enter a positive integer.\n");
        }

        clearInputBuffer();
    }
    while(id < ID_MIN_VALUE);

    return id;
}

/**
 * Prompts user for patient age, with checks to ensure patient age is valid
 * according to the following criteria:
 * 1) Patient age is a positive integer (greater than or equal to MIN_AGE_YEARS)
 *
 * @return patient age
 */
int getPatientAge()
{
    int age;

    age = INVALID_INPUT;

    do
    {
        printf("Enter patient age: ");

        int input = scanf("%d", &age);

        if(input != READ_SUCCESS ||
            age < MIN_AGE_YEARS)
        {
            printf("Invalid age! Please enter a positive integer.\n");
        }

        clearInputBuffer();
    }
    while(age < MIN_AGE_YEARS);

    return age;
}

/**
 * Prompts user for patient room number, with checks to ensure room number is valid
 * according to the following criteria:
 * 1) Patient ID is a positive integer (greater than or equal to ROOM_NUMBER_MIN)
 *
 * @return patient room number
 */
int getPatientRoomNumber()
{
    int roomNumber;

    roomNumber = INVALID_INPUT;

    do
    {
        printf("Enter patient room number: ");

        int input = scanf("%d", &roomNumber);

        if(input != READ_SUCCESS ||
            roomNumber < ROOM_NUMBER_MIN)
        {
            printf("Invalid room number! Please enter a positive integer.\n");
        }

        clearInputBuffer();
    }
    while(roomNumber < ROOM_NUMBER_MIN);

    return roomNumber;
}

/**
 * Prompts the user to choose between two different search criteria:
 * 1) Search by patient ID
 * 2) Search by patient name.
 * Then, checks if patient exists in the database and prints the requested record.
 */
void searchForPatientRecord()
{
    int sel;
    int index;

    do
    {
        index = INVALID_INPUT;

        printf("Search By:\n");
        printf("1. Patient ID\n");
        printf("2. Patient Name\n");
        printf("3. Return to Menu\n");

        sel = getSelection();

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
        else if(sel == SEARCH_BY_ID ||
                sel == SEARCH_BY_NAME)
        {
            printf("Patient not found.\n");
        }
    }
    while (sel != RETURN_TO_MENU);
}

/**
 * Helper method to search the patientRecord array for the patient record corresponding
 * to the specified ID.
 *
 * @return index of patient record corresponding to the specified ID
 */
int searchPatientByID()
{
    int index;
    int id;

    id = getPatientID();
    index = idExists(patientRecords, totalPatients, id);

    return index;
}

/**
 * Helper method to search the patientRecord array for the patient record corresponding
 * to the specified name.
 *
 * @return index of patient record corresponding to the specified name
 */
int searchPatientByName()
{
    char name[NAME_MAX_CHAR];
    int index;

    index = INVALID_INPUT;

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

    return index;
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

/**
 * Helper method to flush the input buffer in the case of invalid inputs.
 */
void clearInputBuffer()
{
    while(getchar() != '\n');
}