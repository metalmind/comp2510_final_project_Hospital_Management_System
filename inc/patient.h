//
// Created by Owen on 10/02/2025.
//

#ifndef PATIENT_H
#define PATIENT_H

#include <stdio.h>
#include <string.h>
#include "patient.h"
#include "tools.h"

#define NAME_MAX_CHAR 50
#define DIAGNOSIS_MAX_CHAR 100

#define MAX_PATIENTS 50

#define MIN_AGE_YEARS 0
#define MAX_AGE_YEARS 150

#define ID_MIN_VALUE 0
#define ID_MAX_VALUE 50
#define ID_NOT_FOUND (-1)

#define INVALID_INPUT (-1)

#define ROOM_NUMBER_MIN 1
#define ROOM_NUMBER_MAX 100

#define SEARCH_BY_ID 1
#define SEARCH_BY_NAME 2
#define RETURN_TO_MENU 3

#define NO_RECORDS 0
#define RECORD_FOUND 0

typedef struct patient patient;

struct patient
{
    int patientID;
    char name[NAME_MAX_CHAR];
    int age;
    char diagnosis[DIAGNOSIS_MAX_CHAR];
    int roomNumber;
};

/**
 * Adds a new patient to the patientRecord array.
 * @author Ayesha Anzer
 * @author Owen Wou
 */
void addNewPatientRecord(void);

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
int idExists(patient arr[],
             int size,
             int id);

/**
 * Prompts user for patient ID, with checks to ensure patient ID is valid
 * according to the following criteria:
 * 1) Patient ID is a positive integer
 * 2) Patient ID is within valid range - i.e., greater than or equal to ID_MIN_VALUE
 *    and less than or equal to ID_MAX_VALUE
 * 3) Patient with the specified ID does not already exist
 *
 * @return patient ID
 */
int getUniquePatientID(void);

/**
 * Prompts user for patient ID, with checks to ensure patient ID is valid
 * according to the following criteria:
 * 1) Patient ID is a positive integer
 * 2) Patient ID is within valid range - i.e., greater than or equal to ID_MIN_VALUE
 *    and less than or equal to ID_MAX_VALUE
 *
 * @return patient ID
 */
int getPatientID(void);

/**
 * Prompts user for patient age, with checks to ensure patient age is valid
 * according to the following criteria:
 * 1) Patient age is a positive integer
 * 2) Patient age is within valid range - i.e., greater than or equal to MIN_AGE_YEARS
 *    and less than or equal to MAX_AGE_YEARS
 *
 * @return patient age
 */
int getPatientAge(void);

/**
 * Prompts user for patient room number, with checks to ensure room number is valid
 * according to the following criteria:
 * 1) Room number is a positive integer
 * 2) Room number is within valid range - i.e., greater than or equal to ROOM_NUMBER_MIN
 *    and less than or equal to ROOM_NUMBER_MAX
 *
 * @return patient room number
 */
int getPatientRoomNumber(void);

/**
 * Prompts the user to choose between two different search criteria:
 * 1) Search by patient ID
 * 2) Search by patient name.
 * Then, checks if patient exists in the database and prints the requested record.
 */
void searchForPatientRecord(void);

/**
 * Routes to the search method associated with the selection.
 * If the selection is not available, prompts the user to try again.
 *
 * Search By:
 *    1. Patient ID
 *    2. Patient Name
 *    3. Return to Menu
 *
 * @param sel selected menu item
 */
void searchCriteriaSelection(int sel);

/**
 * If requested patient record is found, prints its details. Otherwise,
 * prints that record was not found.
 *
 * @param index index of requested patient record in the patientRecord array
 */
void handlePatientSearchResult(int index);

/**
 * If the requested patient record is found, prints its details.
 * If multiple matching records are found, prints details of each.
 * Otherwise, prints that record was not found.
 * @param indexes indexes of records matching the provided String input
 * @param numRecordsFound number of matching records found
 */
void handleMultiplePatientSearchResults(int* indexes,
                                       int numRecordsFound);

/**
 * Helper method to search the patientRecord array for the patient record corresponding
 * to the specified ID.
 *
 * @return index of patient record corresponding to the specified ID
 */
void searchPatientByID(void);

/**
 * Helper method to search the patientRecord array for the patient record corresponding
 * to the specified name.
 *
 * @return index of patient record corresponding to the specified name
 */
void searchPatientByName(void);

/**
 * Prints the patient record corresponding to the specified index of the
 * patient record array.
 * @param index corresponding index of patient record array
 */
void printPatientRecord(int index);

/**
 * Prints all patient records in the patientRecord array.
 */
void viewAllPatientRecords(void);

/**
 * Prints the patient menu.
 */
void printPatientMenu();

#endif //PATIENT_H
