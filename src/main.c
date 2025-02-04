
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

struct patient patientRecords[MAX_PATIENTS];
int totalPatients = 0;

int main(void)
{
    addNewPatientRecord();

    printf("PatientID: %d\n", patientRecords[0].patientID);
    printf("Patient Name: %s\n", patientRecords[0].name);
    printf("Patient Age: %d\n", patientRecords[0].age);
    printf("Patient Diagnisis: %s\n", patientRecords[0].diagnosis);
    printf("Patient Room #: %d\n", patientRecords[0].roomNumber);
    return 0;
}



/**
 * Searches for a patientID in the array and retunrs it's index if found;
 * otherwise, it returns -1.
 * @author Ayesha Anzer
 *
 * @param arr Array of Patient Structs
 * @param size The number of patient records in the array as an int
 * @param id The ID we want to check for existance
 * @return id index if found, otherwise -1
 */
int idExists(struct patient arr[], int size, int id)
{
    for(int i = 0; i  < size; i++)
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

    printf("Enter the ID of the patient (positive number): ");
    scanf("%d", &id);
    getchar();

    if(id < ID_MIN_VALUE || idExists(patientRecords, totalPatients, id) != ID_NOT_FOUND)
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
    name[strcspn(diagnosis, "\n")] = TERMINAL_CHAR;

    do
    {
        printf("Enter patient room number: ");
        scanf("%d", &roomNumber);
    }
    while(roomNumber < ROOM_NUMBER_MIN);

    patientRecords[totalPatients].patientID = id;
    strcpy(patientRecords[totalPatients].name, name);
    patientRecords[totalPatients].age = age;
    strcpy(patientRecords[totalPatients].diagnosis, diagnosis);
    patientRecords[totalPatients].roomNumber = roomNumber;

    printf("Patient added successfully!\n");
}
