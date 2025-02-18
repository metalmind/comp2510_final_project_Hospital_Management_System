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

    addNewDoctorRecord();

    doctor* shepard = getDoctor(0);

    addToSchedule (shepard,
                  SUN,
                  MORNING);

    addToSchedule (shepard,
                  TUE,
                  EVENING);

    printDocWeekSchedule();

    addNewDoctorRecord();
    addNewDoctorRecord();
    viewAllDoctorRecords();
    fireDoctor();
    viewAllDoctorRecords();

    printDocWeekSchedule();

    addNewPatientRecord();
    addNewPatientRecord();
    viewAllPatientRecords();
    searchForPatientRecord();
    dischargePatient();
    viewAllPatientRecords();

    return 0;
}
