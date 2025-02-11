//
// Created by Owen on 10/02/2025.
//

#ifndef PATIENT_H
#define PATIENT_H

#define NAME_MAX_CHAR 50
#define DIAGNOSIS_MAX_CHAR 100

#define MAX_PATIENTS 50

#define TRUE 1
#define FALSE 0

#define MIN_AGE_YEARS 0
#define MAX_AGE_YEARS 150

#define TERMINAL_CHAR 0
#define ID_MIN_VALUE 0
#define ID_MAX_VALUE 50
#define ID_NOT_FOUND (-1)

#define INVALID_INPUT (-1)
#define READ_SUCCESS 1

#define ROOM_NUMBER_MIN 1
#define ROOM_NUMBER_MAX 100

#define SEARCH_BY_ID 1
#define SEARCH_BY_NAME 2
#define RETURN_TO_MENU 3

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

void addNewPatientRecord(void);

int idExists(patient arr[],
             int size,
             int id);

int getUniquePatientID(void);

int getPatientID(void);

int getPatientAge(void);

int getPatientRoomNumber(void);

void searchForPatientRecord(void);

int searchCriteriaSelection(int sel);

void handlePatientSearchResult(int index,
                               int sel);

int searchPatientByID(void);

int searchPatientByName(void);

void printPatientRecord(int id);

void viewAllPatientRecords(void);

// TOOLS?
int getInput(char *prompt,
             int *input);
//TOOLS
int validateData(int numItemsRead,
                 int input,
                 int lowerBound,
                 int upperBound,
                 char *errorMessage);
//TOOLS
int validateInputType(int numItemsRead);
//TOOLS
int validateNum(int num,
                int lowerBound,
                int upperBound);
// TOOLS
void clearInputBuffer(void);




#endif //PATIENT_H
