/**
* Menu handles all the functionality regarding the printing the menu to screen
 * and routing the selection to the correct function.
 *
 * @author Owen Wou
 * @version February 2025
 */
#include <stdio.h>
#include "../inc/menu.h"
#include "../inc/patient.h"
#include "../inc/schedule.h"
#include "../inc/doctor.h"
#include "../inc/report.h"
#include "../inc/tools.h"

/*********Public Functions Begin************/
void menu(void)
{
    readAll();
    viewAll();

    int sel;

    do
    {
        sel = INVALID_INPUT;

        printMenu();
        getInput("Enter your selection: ",
                 &sel);
        routeSelection(sel);
    }
    while(sel != EXIT);
}

void saveMenu(void)
{
    int sel;

    do
    {
        sel = INVALID_INPUT;

        printSaveMenu();
        getInput("Enter your selection: ",
                 &sel);
        routeSaveSelection(sel);
    }
    while(sel != RETURN_TO_MAIN_MENU);
}

void patientMenu(void)
{
    int sel;

    do
    {
        sel = INVALID_INPUT;

        printPatientMenu();
        getInput("Enter your selection: ",
                 &sel);
        routePatientMenuSelection(sel);
    }
    while(sel != RETURN_TO_MAIN_MENU);
}

/*********Public Functions End**************/

/*********Private Functions Begin************/
void printMenu(void)
{
    printf("\nHospital Management System\n");
    printf("%d. Exit\n", EXIT);
    printf("%d. Patients\n", PATIENT_MENU);
    printf("%d. Doctors\n", DOCTOR_MENU);
    printf("%d. Schedule\n", SCHEDULE_MENU);
    printf("%d. Reports\n", GENERATE_REPORT);
    printf("%d. Save / Load\n", SAVE_LOAD_DATA);
    printf("%d. View All\n", VIEW_ALL);
}

void printPatientMenu()
{
    printf("\nPatient Menu\n");
    printf("%d. Return to Main Menu\n", RETURN_TO_MAIN_MENU);
    printf("%d. Add Patient Record\n", ADD_PATIENT_RECORDS);
    printf("%d. Discharge Patient\n", DISCHARGE_PATIENT);
    printf("%d. View All Patients\n", VIEW_ALL_PATIENTS);
    printf("%d. Search For Patient\n", SEARCH_PATIENT);
}

void printSaveMenu(void)
{
    printf("\nSave Menu\n");
    printf("%d. Return to Main Menu\n", RETURN_TO_MAIN_MENU);
    printf("%d. Save All Patient Records\n", SAVE_ALL_PATIENT_RECORDS);
    printf("%d. Load Patient Records\n", LOAD_PATIENT_RECORDS);
    printf("%d. Save Doctor Records\n", SAVE_ALL_DOCTOR_RECORDS);
    printf("%d. Load Doctor Records\n", LOAD_ALL_DOCTOR_RECORDS);
    printf("%d. Save Schedule Records\n", SAVE_ALL_SCHEDULE_RECORDS);
    printf("%d. Load Schedule Records\n", LOAD_ALL_SCHEDULE_RECORDS);
    printf("%d. Save All\n", SAVE_ALL);
    printf("%d. Load All\n", LOAD_ALL);
}

int getSelection(void)
{
    int sel;

    printf("Enter your selection: ");
    scanf("%d",
          &sel);
    getchar();

    return sel;
}

void routeSelection(const int sel)
{
    switch(sel)
    {
    case PATIENT_MENU:
        patientMenu();
        break;
    case DOCTOR_MENU:
        doctorMenu();
        break;
    case SCHEDULE_MENU:
        scheduleMenu();
        break;
    case GENERATE_REPORT:
        generateReport();
        break;
    case SAVE_LOAD_DATA:
        saveMenu();
    case VIEW_ALL:
        viewAll();
        break;
    case EXIT:
        saveAll();
        freePatientMemory();
        freeDoctorMemory();
        printf("Exiting...\n");
        break;
    default:
        printf("Invalid choice! Try again.\n");
    }
}

void routePatientMenuSelection(const int sel)
{
    switch(sel)
    {
    case ADD_PATIENT_RECORDS:
        addNewPatientRecord();
        break;
    case DISCHARGE_PATIENT:
        dischargePatient();
        break;
    case VIEW_ALL_PATIENTS:
        viewAllPatientRecords();
        viewAllDischargedPatientRecords();
        break;
    case SEARCH_PATIENT:
        searchForPatientRecord();
        break;
    case RETURN_TO_MAIN_MENU:
        printf("Returning to menu...\n");
        break;
    default:
        puts("Invalid choice! Try again.");
    }
}

void routeSaveSelection(const int sel)
{
    switch(sel)
    {
    case SAVE_ALL_PATIENT_RECORDS:
        saveAllPatientRecord();
        saveAllDischargedPatientRecord();
        break;
    case LOAD_PATIENT_RECORDS:
        readPatientRecords();
        readDischargedPatientRecords();
        break;
    case SAVE_ALL_DOCTOR_RECORDS:
        saveAllDoctorRecord();
        break;
    case LOAD_ALL_DOCTOR_RECORDS:
        readDoctorRecords();
        break;
    case SAVE_ALL_SCHEDULE_RECORDS:
        saveAllScheduleRecord();
        break;
    case LOAD_ALL_SCHEDULE_RECORDS:
        readScheduleRecords();
        break;
    case SAVE_ALL:
        saveAll();
        break;
    case LOAD_ALL:
        readAll();
    default:
        puts("Invalid choice! Try again.");
    }
}

void readAll()
{
    readPatientRecords();
    readDischargedPatientRecords();
    readDoctorRecords();
    readScheduleRecords();
}

void viewAll()
{
    viewAllPatientRecords();
    viewAllDischargedPatientRecords();
    viewAllDoctorRecords();
    printDocWeekSchedule();
}

void saveAll()
{
    saveAllPatientRecord();
    saveAllDischargedPatientRecord();
    saveAllDoctorRecord();
    saveAllScheduleRecord();
}

/*********Private Functions End**************/
