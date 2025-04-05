#ifndef REPORT_H
#define REPORT_H

#include "../inc/patient.h"
#include "../inc/doctor.h"
#include "../inc/schedule.h"

#define RETURN_TO_MAIN_MENU 0
#define ADMITTED_PATIENTS_REPORT 1
#define DISCHARGED_PATIENTS_REPORT 2
#define DOCTOR_UTILIZATION_REPORT 3
#define ROOM_USAGE_REPORT 4

#define MAX_REPORT_LEN 1000
#define INDEX_OFFSET 1

/*********Public Functions Begin************/

void generateReport();

/**
 * Prints the doctor utilization report.
 */
void printDoctorUtilReport();

/**
 * Prints the room usage report.
 */
void printRoomUsageReport();

/*********Public Functions End**************/

/*********Private Functions Begin**********/

/**
 * Asks the user whether they would like to save a copy of the generated report.
 * @param report report to save
 */
void promptSaveReport(char*       report,
                      const char* fileName);

/**
 * Writes the report to a file.
 * @param report report to save
 */
void writeReportToFile(char* report,
                       const char* fileName);

/**
 * Generates a report header.
 * @param report report string
 * @param reportLength max length of report
 * @param reportTitle report title
 */
int generateHeader(char* report,
                   int   reportLength,
                   char* reportTitle);

/**
 * Generates the doctor utilization report.
 * @param schedule schedule array
 * @param report report string
 */
void generateDoctorUtilReport(const int schedule[DAYS_IN_WEEK][NUM_SHIFTS],
                              char*     report);

/**
 * Generates the room usage report.
 * @param report report string
 */
void generateRoomUsageReport(char* report);

/**
 * Generates the report for the option selected.
 * @param sel selected report option
 */
void routeReportMenu(int sel);

/**
 * Prints the generate report menu.
 */
void printReportMenu();

/*********Private Functions End************/
#endif //REPORT_H
