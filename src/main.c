//#include "menu.h"
#include "../inc/patient.h"
#include<stdio.h>
#include<string.h>
//#include "tools.h"
#include "../inc/schedule.h"


int main(void)
{
    printDocWeekSchedule();
    addToSchedule("Dr. Shepard",
                  SUN,
                  MORNING);
    printDocWeekSchedule();

    addNewPatientRecord();
    addNewPatientRecord();
    viewAllPatientRecords();
    searchForPatientRecord();

    return 0;
}
