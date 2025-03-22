#ifndef DOCTOR_H
#define DOCTOR_H

#define NAME_MAX_CHAR 12
#define SPECIALTY_MAX_CHAR 25

#define MAX_DOCTORS 10

#define DOC_ID_MIN_VALUE 1
#define DOC_ID_MAX_VALUE 10
#define DOC_ID_NOT_FOUND (-1)

#define INT_FIELD_SPACING 9
#define NAME_FIELD_SPACING 17
#define STRING_FIELD_SPACING 29

#define RETURN_TO_MAIN_MENU 0
#define ADD_NEW_DOCTOR 1
#define FIRE_DOCTOR 2
#define VIEW_ALL_DOCTOR_RECORDS 3


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


/*********Public Functions End**************/

/*********Private Functions Begin************/

/**
 * Searches for a doctorID in the array and returns its index if found;
 * otherwise, it returns ID_NOT_FOUND.
 *
 * @param id The ID we want to check for existence
 * @return id index if found, otherwise ID_NOT_FOUND
 *
 * @author Ayesha Anzer
 * @author Owen Wou
 */
int doctorIDExists(int id);

/**
 * Returns the doctor record corresponding to the specified index
 * of the doctorRecords array.
 * @param index index of doctor record to retrieve
 * @return doctor record
 */
doctor* getDoctor(int index);

/**
 * Removes the specified doctor record from the doctorRecord array,
 * shifting remaining doctor records by NEXT_ENTRY_OFFSET to fill the
 * gap.
 * @param index index of doctor record to be removed
 */
void removeDoctorRecord(int index);

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
 * Helper method to search the doctorRecord array for the doctor record corresponding
 * to the specified ID.
 *
 * @return doctor record corresponding to the specified ID
 */
doctor* getDoctorByID();

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
 * Prints the doctor record corresponding to the specified index of the
 * doctor record array.
 * @param index index of doctor record
 */
void printDoctorRecord(int index);

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
void routeDoctorMenu(const int sel);

/*********Private Functions End**************/

#endif //DOCTOR_H
