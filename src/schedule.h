/**
 * The schedule handles all tasks related to doctors being added and viewing the
 * schedule.
 *
 * @author Owen Wou
 * @version February 2025
 */
#ifndef SCHEDULE_H
#define SCHEDULE_H

#define DAYS_IN_WEEK 7
#define NUM_SHIFTS 3
#define MAX_CHAR_SHIFT 15
#define SPACE_PER_COL 13

#define MAX_DOCTORS 10

enum daysInWeek { SUN, MON, TUE, WED, THU, FRI, SAT };

enum shift { MORNING, AFTERNOON, EVENING };

/**
 * Takes in the enum daysInWeek and sets dayOfWeekName to the string version.
 *
 * @param dayOfWeek enum daysInWeek
 * @param dayOfWeekName The String to populate.
 */
void getDayOfWeekNameStr(const enum daysInWeek dayOfWeek,
                         char* dayOfWeekName);

/**
 * Takes in the enum shift and sets of the shift name to the string version.
 *
 * @param shift enum shift
 */
void getShiftNameStr(enum shift shift,
                     char* shiftName);

/**
 * Print the schedule of the doctors for the daysInWeek.
 */
void printDocWeekSchedule();

/**
 * Adds a doctor to the schedule.
 *
 * @param doctorName Name of the doctor to add.
 * @param dayOfWeek The day to schedule the doctor on.
 * @param shiftToFill The shift you want to fill.
 */
void addToSchedule(char* doctorName,
                   enum daysInWeek dayOfWeek,
                   enum shift shiftToFill);

/**
 * Helper function to that prints the crossbar for the schedule to the screen.
 */
void printScheduleDivider();

/**
 * Helper function to print the day of the week header to the screen.
 */
void printDayOfWeekHeader();

/**
 * Helper function that prints the shifts for the week to the screen.
 */
void printShiftsForWeek();

/**
 * Gets the name for the doctor on schedule returned through the doctor parameter.
 *
 * @param dayOfWeek The day of the week to check.
 * @param shift The shift you want to check
 * @param doctor The return value that will have the name of the doctor on shift.
 */
void getDoctorOnShift(enum daysInWeek dayOfWeek,
                      enum shift shift,
                      char* doctor);

#endif //SCHEDULE_H
