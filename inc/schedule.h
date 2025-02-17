/**
 * The schedule handles all tasks related to doctors being added and viewing the
 * schedule.
 *
 * @author Owen Wou
 * @version February 2025
 */
#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "../inc/doctor.h"

#define DAYS_IN_WEEK 7
#define NUM_SHIFTS 3
#define MAX_CHAR_SHIFT 15
#define SPACE_PER_COL 13

#define UNASSIGNED_SHIFT 0

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
 * @param shiftName The name of the shift (Morning, Afternoon, Evening)
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
 * @param doctor Name of the doctor to add.
 * @param dayOfWeek The day to schedule the doctor on.
 * @param shiftToFill The shift you want to fill.
 */
void addToSchedule(const doctor* const doctor,
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
 * @param doctorName The return value that will have the name of the doctor on shift.
 */
void getDoctorOnShift(enum daysInWeek dayOfWeek,
                      enum shift shift,
                      char* doctorName);

/**
 * Clears the shifts that the specified doctor is scheduled in for.
 * @param id id of doctor whose shifts to clear
 */
void clearDoctorShifts(int id);

#endif //SCHEDULE_H
