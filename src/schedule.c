//
// Created by Owen on 15/02/2025.
//

#include "../inc/schedule.h"
#include <stdio.h>
#include <string.h>

char* schedule[DAYS_IN_WEEK][NUM_SHIFTS] = {};

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
                      char* doctor)
{
    if(NULL == schedule[dayOfWeek][shift])
    {
        strcpy(doctor,
               " ");
    }
    else
    {
        strcpy(doctor,
               schedule[dayOfWeek][shift]);
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

void addToSchedule(char* doctorName,
                   const enum daysInWeek dayOfWeek,
                   const enum shift shiftToFill)
{
    schedule[dayOfWeek][shiftToFill] = doctorName;
}
