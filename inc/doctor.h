#ifndef DOCTOR_H
#define DOCTOR_H

#define NAME_MAX_CHAR 12
#define SPECIALTY_MAX_CHAR 25
#define DOCTOR_TITLE_CHARS 4

#define MAX_DOCTORS 10

#define DOC_ID_MIN_VALUE 1
#define DOC_ID_MAX_VALUE 50
#define DOC_ID_NOT_FOUND (-1)

#define INT_FIELD_SPACING 9
#define NAME_FIELD_SPACING 17
#define STRING_FIELD_SPACING 29

#define RETURN_TO_MAIN_MENU 0
#define ADD_NEW_DOCTOR 1
#define FIRE_DOCTOR 2
#define VIEW_ALL_DOCTOR_RECORDS 3
#include "tools.h"


typedef struct doctor doctor;

struct doctor
{
    int doctorID;
    char firstName[NAME_MAX_CHAR];
    char lastName[NAME_MAX_CHAR];
    char specialty[SPECIALTY_MAX_CHAR];
};

/*********Public Functions Begin************/

/**
 * Main entry point for selecting doctor related functions.
 */
void doctorMenu();

/**
 * Adds a new doctor to the doctorRecord array.
 */
void addNewDoctorRecord(void);

/**
 * Fires a doctor from the hospital.
 */
void fireDoctor(void);

/**
 * Prints all doctor records in the doctorRecord array.
 */
void viewAllDoctorRecords(void);

/**
 * Returns the total number of doctors in the hospital.
 * @return total doctors
 */
int getTotalDoctors();

/*********Public Functions End**************/

/*********Private Functions Begin************/
/**
 * Stores the doctor record in the list in sorted order.
 * @param newDoctor doctor to add to list
 */
void addDoctorToList(const doctor* newDoctor);


/**
 * Finds the insertion point for the doctor record in the sorted list.
 * @param id doctor id
 * @param previous previous record
 * @param current current record
 */
void findDoctorSortedPosition(int    id,
                              Node** previous,
                              Node** current);

/**
 * Returns the doctor record corresponding to the specified doctor ID.
 * @param id id of doctor record to retrieve
 * @return doctor record
 */
doctor* getDoctor(int id);

/**
 * Returns whether a doctor with the specified ID already exists in the system.
 * @param id id to check if unique
 * @return true if doctor ID is unique, otherwise false
 */
int isDoctorPatientId(int id);

/**
 * Removes the specified doctor record from the doctorRecord linked list.
 * @param doctorRecord doctor record to be removed
 */
void removeDoctorRecord(const doctor* doctorRecord);

/**
 * Prompts user for doctor ID, with checks to ensure doctor ID is valid
 * according to the following criteria:
 * 1) Doctor ID is a positive integer
 * 2) Doctor ID is within valid range - i.e., greater than or equal to ID_MIN_VALUE
 *    and less than or equal to ID_MAX_VALUE
 * 3) Doctor with the specified ID does not already exist
 *
 * @return doctor ID
 */
int getUniqueDoctorID(void);

/**
 * Prompts user for doctor ID, with checks to ensure doctor ID is valid
 * according to the following criteria:
 * 1) Doctor ID is a positive integer
 * 2) Doctor ID is within valid range - i.e., greater than or equal to ID_MIN_VALUE
 *    and less than or equal to ID_MAX_VALUE
 *
 * @return doctor ID
 */
int getDoctorID(void);

/**
 * Helper method to search the doctorRecord list for the doctor record corresponding
 * to the specified ID.
 *
 * @return doctor record corresponding to the specified ID
 */
doctor* getDoctorByID();

/**
 * Returns the next available doctor ID.
 * @return next available doctor ID
 */
int getNextAvailDocID();

/**
 * Prompts user for doctor name, with checks to ensure doctor name is valid
 * according to the following criteria:
 * 1) Doctor name contains only alphabetic characters and spaces
 *
 * @param prompt prompt message
 * @param name char array to assign name
 */
void getDoctorName(const char* prompt,
                   char* name);

/**
 * Prints the doctor record.
 * @param doctor doctor record to print
 */
void printDoctorRecord(doctor* doctor);

/**
 * Helper function to print the doctor record header, including top and
 * bottom dividers.
 */
void printDoctorRecordsHeader(void);

/**
 * Helper function that prints the crossbar for the doctor records.
 */
void printDoctorRecordDivider(void);

/**
 * Prints the related doctor menu items to the screen.
 */
void printDoctorMenu();

/**
 * Routes to the function selected.
 * @param sel The number of the selected doctor item.
 */
void routeDoctorMenu(int sel);

/**
 * Free all memory associated with doctor records.
 */
void freeDoctorMemory();

/*********Private Functions End**************/

#endif //DOCTOR_H
