//#include "menu.h"
#include "../inc/patient.h"
#include<stdio.h>
#include<string.h>
//#include "tools.h"
#include "../inc/doctor.h"
#include "../inc/schedule.h"

int main(void)
{
    printDocWeekSchedule();

    doctor shepard = {1, "Calzone", "Shepard", "Cardiology"};

    addToSchedule (shepard,
                  SUN,
                  MORNING);
    printDocWeekSchedule();

    addNewDoctorRecord();
    addNewDoctorRecord();
    addNewDoctorRecord();
    viewAllDoctorRecords();
    fireDoctor();
    viewAllDoctorRecords();

    addNewPatientRecord();
    addNewPatientRecord();
    viewAllPatientRecords();
    searchForPatientRecord();
    dischargePatient();
    viewAllPatientRecords();

    return 0;
}
