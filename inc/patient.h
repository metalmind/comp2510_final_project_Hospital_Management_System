//
// Created by Owen on 10/02/2025.
//

#ifndef PATIENT_H
#define PATIENT_H

#include <time.h>

#include "patient.h"
#include "tools.h"

#define FULL_NAME_MAX_CHAR 25
#define DIAGNOSIS_MAX_CHAR 25

#define MAX_PATIENTS 50

#define MIN_AGE_YEARS 0
#define MAX_AGE_YEARS 150

#define ID_MIN_VALUE 1
#define ID_MAX_VALUE 100
#define ID_NOT_FOUND (-1)

#define ROOM_NUMBER_MIN 1
#define ROOM_NUMBER_MAX 100

#define RETURN_TO_MAIN_MENU 0
#define SEARCH_BY_PATIENT_ID 1
#define SEARCH_BY_PATIENT_NAME 2

#define NO_RECORDS 0
#define RECORD_FOUND 0

#define INT_FIELD_SPACING 9
#define STRING_FIELD_SPACING 29
#define DATE_FIELD_SPACING 21

#define ID_INDEX 0
#define NAME_INDEX 1
#define AGE_INDEX 2
#define DIAGNOSIS_INDEX 3
#define ROOM_NUMBER_INDEX 4
#define ADMIT_TIME_INDEX 5
#define NUM_PATIENT_FIELDS 7

#define BUFFER_SIZE 400

typedef struct patient patient;

struct patient
{
    int    patientID;
    char   name[FULL_NAME_MAX_CHAR];
    int    age;
    char   diagnosis[DIAGNOSIS_MAX_CHAR];
    int    roomNumber;
    time_t admissionDate;
    time_t dischargeDate;
};

/*********Public Functions Begin************/
/**
 * Adds a new patient to the patientRecord array.
 * @author Ayesha Anzer
 * @author Owen Wou
 */
void addNewPatientRecord(void);

/**
 * Prints all patient records in the patientRecord array.
 */
void viewAllPatientRecords(void);

/**
 * Prompts the user to choose between two different search criteria:
 * 1) Search by patient ID
 * 2) Search by patient name.
 * Then, checks if patient exists in the database and prints the requested record.
 */
void searchForPatientRecord(void);

/**
 * Discharges a patient from the hospital.
 */
void dischargePatient(void);

/**
 * Read the patient record file and load it into memory.
 */
void readPatientRecords();

/**
 * Returns the total number of patients in the hospital.
 * @return total patients
 */
int getTotalPatients();

void saveAllPatientRecord();
/*********Public Functions End**************/

/*********Private Functions Begin************/

/**
 * Stores the patient record in the list in sorted order.
 * @param newPatient patient to add to list
 */
void addPatientToList(const patient* newPatient);


/**
 * Stores the patient record in the discharged patient list.
 * @param dischargedPatient patient to discharge
 */
void addPatientToDischargedList(const patient* dischargedPatient);

/**
 * Finds the insertion point for the patient record in the sorted list.
 * @param id patient id
 * @param previous previous record
 * @param current current record
 */
void findPatientSortedPosition(int    id,
                               Node** previous,
                               Node** current);

/**
 * Returns the patient record corresponding to the specified patient ID.
 * @param id id of patient record to retrieve
 * @return patient record
 */
patient* getPatient(int id);

/**
 * Returns whether a patient with the specified ID already exists in the system.
 * @param id id to check if unique
 * @return true if patient ID is unique, otherwise false
 */
int isUniquePatientId(int id);

/**
 * Removes the specified patient record from the patientRecord linked list.
 * @param patientRecord patient record to be removed
 */
void removePatientRecord(const patient* patientRecord);

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
 * Returns the next available patient ID.
 * @return next available patient ID
 */
int getNextAvailPatientID();

/**
 * Prompts user for patient name, with checks to ensure patient name is valid
 * according to the following criteria:
 * 1) Patient name contains only alphabetic characters and spaces
 *
 * @param prompt prompt message
 * @param name char array to assign name
 */
void getPatientName(const char* prompt,
                    char*       name);

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
 * @param patientRecord the requested patient record
 */
void handlePatientSearchResult(const patient* patientRecord);

/**
 * If the requested patient record is found, prints its details.
 * If multiple matching records are found, prints details of each.
 * Otherwise, prints that record was not found.
 * @param patientsFound patient record matching the provided String input
 * @param numRecordsFound number of matching records found
 */
void handleMultiplePatientSearchResults(const patient** patientsFound,
                                        int             numRecordsFound);

/**
 * Helper method to search the patientRecord array for the patient record corresponding
 * to the specified ID.
 */
void searchPatientByID(void);

/**
 * Helper method to search the patientRecord array for the patient record corresponding
 * to the specified name.
 */
void searchPatientByName(void);

/**
 * Prints the patient record.
 * @param patient patient record to print
 */
void printPatientRecord(patient* patient);

/**
 * Prints the patient menu.
 */
void printPatientMenu();

/**
 * Helper function to print the patient record header, including top and
 * bottom dividers.
 */
void printPatientRecordsHeader();

/**
 * Helper function that prints the crossbar for the patient records.
 */
void printPatientRecordDivider();

/**
 * Helper function that adds a new entry to the linked list.
 * @param id Patient ID
 * @param name Patient Name
 * @param age Patient Age
 * @param diagnosis Patient Diagnosis
 * @param roomNumber Room Number
 */
void createNewPatientEntry(int        id,
                           const char name[25],
                           int        age,
                           const char diagnosis[25],
                           int        roomNumber,
                           time_t     admissionDate);

/**
 * Free all memory associated with patient records.
 */
void freePatientMemory();
/*********Private Functions End**************/

#endif //PATIENT_H
