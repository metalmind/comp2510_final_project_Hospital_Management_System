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

#define ASSIGN_DOC_TO_SHIFT 1
#define CLEAR_SHIFT 2
#define VIEW_WEEK_SCHEDULE 3

#define MENU_NUMBERING_OFFSET 1

#define SCHEDULE_RECORD_FILE_PATH "../res/scheduleRecords.txt"

enum daysInWeek { SUN, MON, TUE, WED, THU, FRI, SAT };

enum shift { MORNING, AFTERNOON, EVENING };
/*********Public Functions Begin************/
/**
 * The main entry point into the schedule menu.
 */
void scheduleMenu();

/**
 * Prompts for a shift and a doctor, and assigns the specified doctor
 * to the shift.
 */
void assignShift();

/**
 * Prompts for a shift to clear, and clears the specified shift.
 */
void clearShift();

/**
 * Print the schedule of the doctors for the daysInWeek.
 */
void printDocWeekSchedule();

/**
 * Saves the entire schedule to an external file at SCHEDULE_RECORD_FILE_PATH.
 */
void saveAllScheduleRecord();

/**
 * Reads a schedule from the external file at SCHEDULE_RECORD_FILE_PATH and loads it into memory.
 */
void readScheduleRecords();
/*********Public Functions End**************/

/*********Private Functions Begin************/
/**
 * Takes in the enum daysInWeek and sets dayOfWeekName to the string version.
 *
 * @param dayOfWeek enum daysInWeek
 * @param dayOfWeekName The String to populate.
 */
void getDayOfWeekNameStr(enum daysInWeek dayOfWeek,
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
 * Adds a doctor to the schedule.
 *
 * @param doctor Name of the doctor to add.
 * @param dayOfWeek The day to schedule the doctor on.
 * @param shiftToFill The shift you want to fill.
 */
void addDoctorToSchedule(const doctor* doctor,
                   enum daysInWeek dayOfWeek,
                   enum shift shiftToFill);

/**
 * Helper function to print the day of the week header to the screen.
 */
void printDayOfWeekHeader();

/**
 * Helper function to that prints the crossbar for the schedule to the screen.
 */
void printScheduleDivider();

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

/**
 * Helper function which prints the menu options to the screen.
 */
void printScheduleMenu();

/**
 * Helper function which prints the day of week options to the screen.
 */
void printDayOfWeekMenu();

/**
 * Helper function which prints the shift options to the screen.
 */
void printShiftMenu();

/**
 * Returns a copy of the schedule.
 * @param scheduleCopy schedule copy
 */
void getSchedule(int scheduleCopy[DAYS_IN_WEEK][NUM_SHIFTS]);

/**
 * Helper function to call the selected function from the menu.
 * @param sel The input from the user.
 */
void routeScheduleMenu(const int sel);

/**
 * Writes a specific day to the file at the given path as a single line entry.
 * @param shift
 * @param filePathStr
 */
void writeScheduleRecord(const int shift[],
                         const char* filePathStr);

/**
 * Reads the schedule from the external file.
 * @param filePathStr
 */
void readScheduleFile(const char* filePathStr);


/*********Private Functions End**************/

#endif //SCHEDULE_H
