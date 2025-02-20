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

void assignShift()
{
    doctor* doc;
    int dayOfWeek;
    int shiftToFill;

    doc       = getDoctorByID();

    if(doc == NULL)
    {
        printf("Requested doctor not found in the system.\n");
        return;
    }

    printDayOfWeekMenu();
    dayOfWeek = promptForInput("Enter day of week: ",
                               "Invalid day of week! Try again.\n",
                               SUN + MENU_NUMBERING_OFFSET,
                               SAT + MENU_NUMBERING_OFFSET);
    dayOfWeek -= MENU_NUMBERING_OFFSET;

    printShiftMenu();
    shiftToFill = promptForInput("Enter shift to fill: ",
                                 "Invalid shift! Try again.\n",
                                 MORNING + MENU_NUMBERING_OFFSET,
                                 EVENING + MENU_NUMBERING_OFFSET);
    shiftToFill -= MENU_NUMBERING_OFFSET;

    addDoctorToSchedule(doc,
                        dayOfWeek,
                        shiftToFill);
}

void addDoctorToSchedule(const doctor* const doctor,
                         const enum daysInWeek dayOfWeek,
                         const enum shift shiftToFill)
{
    schedule[dayOfWeek][shiftToFill] = doctor -> doctorID;
    const char dayOfWeekStr[MAX_CHAR_SHIFT];
    const char shiftNameStr[MAX_CHAR_SHIFT];

    getDayOfWeekNameStr(dayOfWeek, dayOfWeekStr);
    getShiftNameStr(shiftToFill, shiftNameStr);

    printf("Successfully assigned Dr. %s to the %s %s shift!\n",
           doctor -> lastName,
           dayOfWeekStr,
           shiftNameStr);
}

void clearShift()
{
    int dayOfWeek;
    int shiftToClear;

    printDayOfWeekMenu();
    dayOfWeek = promptForInput("Enter day of week: ",
                               "Invalid day of week! Try again.\n",
                               SUN + MENU_NUMBERING_OFFSET,
                               SAT + MENU_NUMBERING_OFFSET);
    dayOfWeek -= MENU_NUMBERING_OFFSET;

    printShiftMenu();
    shiftToClear = promptForInput("Enter shift to clear: ",
                                 "Invalid shift! Try again.\n",
                                 MORNING + MENU_NUMBERING_OFFSET,
                                 EVENING + MENU_NUMBERING_OFFSET);
    shiftToClear -= MENU_NUMBERING_OFFSET;

    if(schedule[dayOfWeek][shiftToClear] != UNASSIGNED_SHIFT)
    {
        schedule[dayOfWeek][shiftToClear] = UNASSIGNED_SHIFT;
        printf("Shift successfully cleared!\n");
    }
    else
    {
        printf("Shift not cleared - no doctor assigned to shift.\n");
    }
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
    printf("%d. Assign Doctor to Shift\n", ASSIGN_DOC_TO_SHIFT);
    printf("%d. Clear Shift\n", CLEAR_SHIFT);
    printf("%d. View Week Schedule\n", VIEW_WEEK_SCHEDULE);
}

void printDayOfWeekMenu()
{
    printf("%d. Sunday\n",
           SUN + MENU_NUMBERING_OFFSET);
    printf("%d. Monday\n",
           MON + MENU_NUMBERING_OFFSET);
    printf("%d. Tuesday\n",
           TUE + MENU_NUMBERING_OFFSET);
    printf("%d. Wednesday\n",
           WED + MENU_NUMBERING_OFFSET);
    printf("%d. Thursday\n",
           THU + MENU_NUMBERING_OFFSET);
    printf("%d. Friday\n",
           FRI + MENU_NUMBERING_OFFSET);
    printf("%d. Saturday\n",
           SAT + MENU_NUMBERING_OFFSET);
}

void printShiftMenu()
{
    printf("%d. Morning\n",
           MORNING + MENU_NUMBERING_OFFSET);
    printf("%d. Afternoon\n",
           AFTERNOON + MENU_NUMBERING_OFFSET);
    printf("%d. Evening\n",
           EVENING + MENU_NUMBERING_OFFSET);
}

void routeScheduleMenu(const int sel)
{
    switch(sel)
    {
        case ASSIGN_DOC_TO_SHIFT:
            assignShift();
            break;
        case CLEAR_SHIFT:
            clearShift();
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