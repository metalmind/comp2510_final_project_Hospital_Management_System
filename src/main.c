//#include "menu.h"
//#include "patient.h"
#include<stdio.h>
#include<String.h>
//#include "tools.h"
#include "schedule.h"


int main(void)
{
    printDocWeekSchedule();
    addToSchedule("Dr. Shepard",
                  SUN,
                  MORNING);
    printDocWeekSchedule();

    // addNewPatientRecord();
    // addNewPatientRecord();
    // viewAllPatientRecords();
    // searchForPatientRecord();

    return 0;
}
