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
#include "../inc/tools.h"

/*********Public Functions Begin************/
void menu(void)
{
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

/*********Public Functions End**************/

/*********Private Functions Begin************/
void printMenu(void)
{
    printf("\nHospital Management System\n");
    printf("%d. Exit\n", EXIT);
    printf("%d. Add Patient Record\n", ADD_PATIENT_RECORDS);
    printf("%d. View All Patients\n", VIEW_ALL_PATIENTS);
    printf("%d. Search Patient\n", SEARCH_PATIENT);
    printf("%d. Discharge Patient\n", DISCHARGE_PATIENT);
    printf("%d. Manage Doctors\n", DOCTOR_MENU);
    printf("%d. Save All Patient Records\n", SAVE_ALL_PATIENT_RECORDS);
    printf("%d. Load Patient Records\n", LOAD_PATIENT_RECORDS);
    printf("%d. Manage Schedule\n", SCHEDULE_MENU);
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
        case ADD_PATIENT_RECORDS:
            addNewPatientRecord();
            break;
        case VIEW_ALL_PATIENTS:
            viewAllPatientRecords();
            break;
        case SEARCH_PATIENT:
            searchForPatientRecord();
            break;
        case DISCHARGE_PATIENT:
            dischargePatient();
            break;
        case DOCTOR_MENU:
            doctorMenu();
            break;
        case SAVE_ALL_PATIENT_RECORDS:
            saveAllPatientRecord();
            break;
        case LOAD_PATIENT_RECORDS:
            readPatientRecords();
            break;
        case SCHEDULE_MENU:
            scheduleMenu();
            break;
        case EXIT:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice! Try again.\n");
    }
}

/*********Private Functions End**************/
