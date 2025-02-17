#include "../inc/doctor.h"
#include <stdio.h>
#include <string.h>
#include "../inc/tools.h"

doctor doctorRecords[MAX_DOCTORS] = {};
int totalDoctors                  = 0;

int doctorIDExists(const int id)
{
    for(int i = 0; i < totalDoctors; i++)
    {
        if(doctorRecords[i].doctorID == id)
        {
            return i;
        }
    }
    return DOC_ID_NOT_FOUND;
}

doctor* getDoctor(const int index)
{
    if(index != DOC_ID_NOT_FOUND)
    {
        return &doctorRecords[index];
    }

    return NULL;
}

void addNewDoctorRecord(void)
{
    if(totalDoctors >= MAX_DOCTORS)
    {
        printf("No open positions for new doctors! Cannot add any more doctors.\n");
        return;
    }

    int id;
    char firstName[NAME_MAX_CHAR];
    char lastName[NAME_MAX_CHAR];
    char specialty[SPECIALTY_MAX_CHAR];

    id = getUniqueDoctorID();

    getStringInput("Enter doctor first name: ",
                   firstName,
                   NAME_MAX_CHAR);

    getStringInput("Enter doctor last name: ",
                   lastName,
                   NAME_MAX_CHAR);

    getStringInput("Enter doctor specialty: ",
                   specialty,
                   SPECIALTY_MAX_CHAR);

    doctorRecords[totalDoctors].doctorID = id;
    strcpy(doctorRecords[totalDoctors].firstName,
           firstName);
    strcpy(doctorRecords[totalDoctors].lastName,
           lastName);
    strcpy(doctorRecords[totalDoctors].specialty,
           specialty);
    totalDoctors++;

    printf("Doctor added successfully!\n");
}

void fireDoctor()
{
    int index;
    int id;

    id    = getDoctorID();
    index = doctorIDExists(id);

    if(index != DOC_ID_NOT_FOUND)
    {
        removeDoctorRecord(index);
    }
    else
    {
        printf("Doctor record not found.");
    }
}

void removeDoctorRecord(const int index)
{
    for(int i = index; i < totalDoctors - ENTRY_REMOVAL_OFFSET; i++)
    {
        doctorRecords[i] = doctorRecords[i + NEXT_ENTRY_OFFSET];
    }

    printf("Doctor successfully removed.\n");
    totalDoctors--;
}

int getUniqueDoctorID()
{
    int id;
    int valid;
    int unique;

    valid  = FALSE;
    unique = FALSE;

    do
    {
        id = DOC_ID_NOT_FOUND;

        int numItemsRead;

        numItemsRead = getInput("Enter doctor ID: ",
                                &id);
        unique = doctorIDExists(id) == DOC_ID_NOT_FOUND;

        valid = validateData(numItemsRead,
                             id,
                             DOC_ID_MIN_VALUE,
                             DOC_ID_MAX_VALUE,
                             "Invalid doctor ID! Please enter a positive integer.\n");

        if(valid && !unique)
        {
            printf("Duplicate doctor ID! Please enter a unique ID.\n");
        }
    }
    while(!(valid && unique));

    return id;
}

int getDoctorID()
{
    int id;
    int valid;

    id    = DOC_ID_NOT_FOUND;
    valid = FALSE;

    do
    {
        int numItemsRead;

        numItemsRead = getInput("Enter doctor ID: ",
                                &id);

        valid = validateData(numItemsRead,
                             id,
                             DOC_ID_MIN_VALUE,
                             DOC_ID_MAX_VALUE,
                             "Invalid doctor ID! Please enter a positive integer.\n");
    }
    while(!valid);

    return id;
}

void printDoctorRecord(const int index)
{
    printf("%-2s%-8d%-2s%-16s%-2s%-16s%-2s%-20s%c\n",
           "|",
           doctorRecords[index].doctorID,
           "|",
           doctorRecords[index].firstName,
           "|",
           doctorRecords[index].lastName,
           "|",
           doctorRecords[index].specialty,
           '|');
}

void viewAllDoctorRecords()
{
    if(totalDoctors == 0)
    {
        printf("No doctor records on file.\n");
        return;
    }

    prinDoctorRecordsHeader();

    for(int i = 0; i < totalDoctors; i++)
    {
        printDoctorRecord(i);
    }

    printDoctorRecordDivider();
}

void prinDoctorRecordsHeader()
{
    printDoctorRecordDivider();

    printf("%-2s%-8s%-2s%-16s%-2s%-16s%-2s%-20s%c\n",
       "|",
       "ID",
       "|",
       "First Name",
       "|",
       "Last Name",
       "|",
       "Specialty",
       '|');

    printDoctorRecordDivider();
}

void printDoctorRecordDivider()
{
    printf("+");
    printDashes(INT_FIELD_SPACING);
    printf("+");
    printDashes(NAME_FIELD_SPACING);
    printf("+");
    printDashes(NAME_FIELD_SPACING);
    printf("+");
    printDashes(STRING_FIELD_SPACING);
    printf("+");
    printf("\n");
}

void printDashes(const int numDashes)
{
    for(int i = 0; i < numDashes; i++)
    {
        printf("%c", '-');
    }
}
