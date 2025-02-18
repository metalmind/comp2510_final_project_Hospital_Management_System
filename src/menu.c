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




void menu(void)
{
    int sel;
    do
    {
        printMenu();
        sel = getSelection();
        routeSelection(sel);
    }
    while(sel != EXIT);
}

void printMenu(void)
{
    printf("\nHospital Management System\n");
    printf("%d. Exit\n", EXIT);
    printf("%d. Add Patient Record\n", ADD_PATIENT_RECORDS);
    printf("%d. View ALl Patients\n", VIEW_ALL_PATIENTS);
    printf("%d. Search Patient by ID\n", SEARCH_PATIENT_BY_ID);
    printf("%d. Discharge Patient\n", DISCHARGE_PATIENT);
    printf("%d. Manage Doctors\n", DOCTOR_MENU);
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
            //addNewPatientRecords();
            printf("1. Add Patient Record\n");
            break;
        case VIEW_ALL_PATIENTS:
            //viewAllPatients();
            printf("2. View ALl Patients\n");
            break;
        case SEARCH_PATIENT_BY_ID:
            //searchPatientByID();
            printf("3. Search Patient by ID\n");
            break;
        case DISCHARGE_PATIENT:
            //dischargePatient();
            printf("4. Discharge Patient\n");
            break;
        case MANAGE_DOCTOR_SCHEDULE:
            //manageDoctorSchedule();
            printf("5. Manage Doctor Schedule\n");
            break;
        case EXIT:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice! Try again.\n");
    }
}
