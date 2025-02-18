//
// Created by Owen on 15/02/2025.
//

#include <stdio.h>
#include <string.h>
#include "../inc/schedule.h"
#include "../inc/doctor.h"
#include "../inc/tools.h"

int schedule[DAYS_IN_WEEK][NUM_SHIFTS] = {};

void getDayOfWeekNameStr(const enum daysInWeek dayOfWeek,
                         char* dayOfWeekName)
{
    switch(dayOfWeek)
    {
        case SUN:
            strcpy(dayOfWeekName,
                   "Sunday");
            break;
        case MON:
            strcpy(dayOfWeekName,
                   "Monday");
            break;
        case TUE:
            strcpy(dayOfWeekName,
                   "Tuesday");
            break;
        case WED:
            strcpy(dayOfWeekName,
                   "Wednesday");
            break;
        case THU:
            strcpy(dayOfWeekName,
                   "Thursday");
            break;
        case FRI:
            strcpy(dayOfWeekName,
                   "Friday");
            break;
        case SAT:
            strcpy(dayOfWeekName,
                   "Saturday");
            break;
        default:
            strcpy(dayOfWeekName,
                   "ERROR invalid day of week");
            break;
    }
}

void getShiftNameStr(const enum shift shift,
                     char* shiftName)
{
    switch(shift)
    {
        case MORNING:
            strcpy(shiftName,
                   "Morning");
            break;
        case AFTERNOON:
            strcpy(shiftName,
                   "Afternoon");
            break;
        case EVENING:
            strcpy(shiftName,
                   "Evening");
            break;
        default:
            strcpy(shiftName,
                   "ERROR printing shift");
            break;
    }
}

void printDocWeekSchedule()
{
    printScheduleDivider();
    printDayOfWeekHeader();
    printScheduleDivider();
    printShiftsForWeek();
    printScheduleDivider();
}

void printShiftsForWeek()
{
    char shiftName[MAX_CHAR_SHIFT];
    char doctorName[MAX_CHAR_SHIFT];

    for(int shift = 0; shift < NUM_SHIFTS; shift++)
    {
        getShiftNameStr(shift,
                        shiftName);
        printf("| ");
        printf("%-12s",
               shiftName);
        printf("|");
        for(int dayOfWeek = 0; dayOfWeek < DAYS_IN_WEEK; dayOfWeek++)
        {
            printf(" ");
            //getShiftNameStr(i, shiftName);
            getDoctorOnShift(dayOfWeek,
                             shift,
                             doctorName);
            printf("%-12s",
                   doctorName);
            printf("|");
        }
        printf("\n");
    }
}

void getDoctorOnShift(enum daysInWeek dayOfWeek,
                      enum shift shift,
                      char* doctorName)
{
    int index;
    doctor* doc;

    index = doctorIDExists(schedule[dayOfWeek][shift]);
    doc   = getDoctor(index);

    if(doc == NULL)
    {
        strcpy(doctorName,
               " ");
    }
    else
    {
        strcpy(doctorName, "Dr. ");
        strcat(doctorName,  doc -> lastName);
    }
}

void printDayOfWeekHeader()
{
    printf("%-14s",
           "|");
    printf("|");
    char dayOfWeekName[MAX_CHAR_SHIFT];
    for(int i = 0; i < DAYS_IN_WEEK; i++)
    {
        printf(" ");
        getDayOfWeekNameStr(i,
                            dayOfWeekName);
        printf("%-12s",
               dayOfWeekName);
        printf("|");
    }
    printf("\n");
}

void printScheduleDivider()
{
    for(int i = 0; i < DAYS_IN_WEEK + 1; i++)
    {
        printf("+");
        for(int j = 0; j < SPACE_PER_COL; j++)
        {
            printf("-");
        }
    }
    printf("+");
    printf("\n");
}

void addDoctorToSchedule(const doctor* const doctor,
                   const enum daysInWeek dayOfWeek,
                   const enum shift shiftToFill)
{
    // schedule[dayOfWeek][shiftToFill] = doctorName;
    schedule[dayOfWeek][shiftToFill] = doctor -> doctorID;
}

void clearDoctorShifts(const int id)
{
    for(int i = 0; i < DAYS_IN_WEEK; i++)
    {
        for(int j = 0; j < NUM_SHIFTS; j++)
        {
            if(schedule[i][j] == id)
            {
                schedule[i][j] = UNASSIGNED_SHIFT;
            }
        }
    }
}

void scheduleMenu()
{
    int sel;

    do
    {
        printScheduleMenu();

        getInput("Enter your selection: ",
                 &sel);
        routeScheduleMenu(sel);
    }
    while(sel != RETURN_TO_MAIN_MENU);
}

void printScheduleMenu()
{
    printf("%d. Return to Main Menu\n", RETURN_TO_MAIN_MENU);
    printf("%d. Add To Schedule\n", ADD_DOCTOR_TO_SCHEDULE);
    printf("%d. View Week Schedule\n", VIEW_WEEK_SCHEDULE);
}

void routeScheduleMenu(const int sel)
{
    switch(sel)
    {
        case ADD_DOCTOR_TO_SCHEDULE:
            //addDoctorToSchedule();
        break;
        case VIEW_WEEK_SCHEDULE:
            printDocWeekSchedule();
        break;
        case RETURN_TO_MAIN_MENU:
            printf("Returning to menu...\n");
        break;
        default:
            printf("Invalid input! Try again.\n");
    }
}