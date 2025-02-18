#include "../inc/doctor.h"
#include "../inc/schedule.h"
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

    getDoctorName("Enter doctor first name: ",
                  firstName);

    getDoctorName("Enter doctor last name: ",
                  lastName);

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
        clearDoctorShifts(id);
    }
    else
    {
        printf("Doctor record not found.\n");
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

    id = promptForUniqueInput("Enter doctor ID: ",
                              "Invalid doctor ID! Please enter a positive integer.\n",
                              "Duplicate doctor ID! Please enter a unique ID.\n",
                              &doctorIDExists,
                              DOC_ID_MIN_VALUE,
                              DOC_ID_MAX_VALUE);

    return id;
}

int getDoctorID()
{
    int id;

    id = promptForInput("Enter doctor ID: ",
                        "Invalid doctor ID! Please enter a positive integer.\n",
                        DOC_ID_MIN_VALUE,
                        DOC_ID_MAX_VALUE);

    return id;
}

doctor* getDoctorByID()
{
    int id;
    int index;

    id    = getDoctorID();
    index = doctorIDExists(id);

    return getDoctor(index);
}

void getDoctorName(const char* prompt,
                   char* const name)
{
    promptForNameStr(prompt,
                     name,
                     NAME_MAX_CHAR);
}

void printDoctorRecord(const int index)
{
    printf("%-2s%-8d%-2s%-16s%-2s%-16s%-2s%-28s%c\n",
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

    printDoctorRecordsHeader();

    for(int i = 0; i < totalDoctors; i++)
    {
        printDoctorRecord(i);
    }

    printDoctorRecordDivider();
}

void printDoctorRecordsHeader()
{
    printDoctorRecordDivider();

    printf("%-2s%-8s%-2s%-16s%-2s%-16s%-2s%-28s%c\n",
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

void doctorMenu()
{
    int sel;

    do
    {
        printDoctorMenu();

        getInput("Enter your selection: ",
                 &sel);
        routeDoctorMenu(sel);
    }
    while(sel != RETURN_TO_MAIN_MENU);
}

void printDoctorMenu()
{
    printf("%d. Return to Main Menu\n", RETURN_TO_MAIN_MENU);
    printf("%d. Add New Doctor\n", ADD_NEW_DOCTOR);
    printf("%d. Fire Doctor\n", FIRE_DOCTOR);
    printf("%d. View All Doctor Records\n", VIEW_ALL_DOCTOR_RECORDS);
}

void routeDoctorMenu(const int sel)
{
    switch(sel)
    {
        case ADD_NEW_DOCTOR:
            addNewDoctorRecord();
            break;
        case FIRE_DOCTOR:
            fireDoctor();
            break;
        case VIEW_ALL_DOCTOR_RECORDS:
            viewAllDoctorRecords();
            break;
        case RETURN_TO_MAIN_MENU:
            printf("Returning to menu...\n");
            break;
        default:
            printf("Invalid input! Try again.\n");
    }
}
