//
// Created by Owen on 10/02/2025.
//

#include "patient.h"
#include <stdio.h>
#include <string.h>


patient patientRecords[MAX_PATIENTS] = {};
int totalPatients                    = 0;


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

/**
 * Prompts user for patient ID, with checks to ensure patient ID is valid
 * according to the following criteria:
 * 1) Patient ID is a positive integer
 * 2) Patient ID is within valid range - i.e., greater than or equal to ID_MIN_VALUE
 *    and less than or equal to ID_MAX_VALUE
 *
 * @return patient ID
 */
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

/**
 * Prompts user for patient age, with checks to ensure patient age is valid
 * according to the following criteria:
 * 1) Patient age is a positive integer
 * 2) Patient age is within valid range - i.e., greater than or equal to MIN_AGE_YEARS
 *    and less than or equal to MAX_AGE_YEARS
 *
 * @return patient age
 */
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

/**
 * Prompts user for patient room number, with checks to ensure room number is valid
 * according to the following criteria:
 * 1) Room number is a positive integer
 * 2) Room number is within valid range - i.e., greater than or equal to ROOM_NUMBER_MIN
 *    and less than or equal to ROOM_NUMBER_MAX
 *
 * @return patient room number
 */
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

/**
 * Wrapper function for scanf() which takes a prompt message to print and
 * a value to which to assign the input. Clears the input buffer in case of invalid
 * input.
 *
 * @param prompt prompt message
 * @param input value to assign input
 * @return number of items successfully read
 */
int getInput(char* prompt,
             int* input)
{
    int numItemsRead;

    printf("%s",
           prompt);
    numItemsRead = scanf("%d",
                         input);
    clearInputBuffer();

    return numItemsRead;
}

/**
 * Validates whether input value is of valid type (i.e., has been successfully read
 * and assigned) and within range.
 *
 * @param numItemsRead number of items successfully read
 * @param input data value to validate
 * @param lowerBound lower bound of valid range
 * @param upperBound upper bound of valid range
 * @param errorMessage error message to print should data be invalid
 * @return 1 is data value is valid, otherwise 0
 */
int validateData(int numItemsRead,
                 int input,
                 int lowerBound,
                 int upperBound,
                 char* errorMessage)
{
    int valid = FALSE;

    valid = validateInputType(numItemsRead) && validateNum(input,
                     lowerBound,
                     upperBound);

    if(!valid)
    {
        printf("%s",
               errorMessage);
    }

    return valid;
}

/**
 * Validates whether input read was successful - checks that numItemsRead
 * is equal to READ_SUCCESS, indicating that an integer value was successfully
 * extracted and assigned.
 *
 * @param numItemsRead number of items successfully read
 * @return 1 if input type is valid, otherwise 0
 */
int validateInputType(const int numItemsRead)
{
    int valid;

    valid = FALSE;

    if(numItemsRead == READ_SUCCESS)
    {
        valid = TRUE;
    }

    return valid;
}

/**
 * Validates whether number is within valid range.
 *
 * @param num number to validate
 * @param lowerBound lower bound of valid range
 * @param upperBound upper bound of valid range
 * @return 1 if number is within valid range, otherwise 0
 */
int validateNum(const int num,
                const int lowerBound,
                const int upperBound)
{
    int valid;

    valid = FALSE;

    if(num >= lowerBound && num <= upperBound)
    {
        valid = TRUE;
    }

    return valid;
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
        printPatientMenu();

        getInput("Enter your selection: ",
                 &sel);
        index = searchCriteriaSelection(sel);
        handlePatientSearchResult(index,
                                  sel);
    }
    while(sel != RETURN_TO_MENU);
}

/**
 * Prints the patient menu.
 */
void printPatientMenu()
{
    printf("Search By:\n");
    printf("1. Patient ID\n");
    printf("2. Patient Name\n");
    printf("3. Return to Menu\n");
}

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

/**
 * If requested patient record is found, prints its details. Otherwise,
 * if user menu selection was either SEARCH_BY_ID or SEARCH_BY_NAME
 * (i.e., was not an invalid selection), prints that record was not found.
 *
 * @param index index of requested patient record in the patientRecord array
 * @param sel user menu selection
 */
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

    id    = getPatientID();
    index = idExists(patientRecords,
                     totalPatients,
                     id);

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
