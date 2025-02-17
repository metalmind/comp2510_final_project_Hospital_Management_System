#ifndef DOCTOR_H
#define DOCTOR_H

#define NAME_MAX_CHAR 25
#define SPECIALTY_MAX_CHAR 50

#define MAX_DOCTORS 10

#define DOC_ID_MIN_VALUE 1
#define DOC_ID_MAX_VALUE 10
#define DOC_ID_NOT_FOUND (-1)

#define INT_FIELD_SPACING 9
#define NAME_FIELD_SPACING 17
#define STRING_FIELD_SPACING 21

typedef struct doctor doctor;

struct doctor
{
    int doctorID;
    char firstName[NAME_MAX_CHAR];
    char lastName[NAME_MAX_CHAR];
    char specialty[SPECIALTY_MAX_CHAR];
};

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
 * Adds a new doctor to the doctorRecord array.
 */
void addNewDoctorRecord(void);

/**
 * Fires a doctor from the hospital.
 */
void fireDoctor(void);

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
 * Prints the doctor record corresponding to the specified index of the
 * doctor record array.
 * @param index corresponding index of doctor record array
 */
void printDoctorRecord(int index);

/**
 * Prints all doctor records in the doctorRecord array.
 */
void viewAllDoctorRecords(void);

/**
 * Helper function to print the doctor record header, including top and
 * bottom dividers.
 */
void prinDoctorRecordsHeader(void);

/**
 * Helper function that prints the crossbar for the doctorrecords.
 */
void printDoctorRecordDivider(void);

#endif //DOCTOR_H
