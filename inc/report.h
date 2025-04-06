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

#define ADMITTED_REPORT_DAY 1
#define ADMITTED_REPORT_WEEK 2
#define ADMITTED_REPORT_MONTH 3

#define MAX_REPORT_LEN 5000
#define INDEX_OFFSET 1

/*********Public Functions Begin************/

/**
 * Prompts the user to select the report type to generate.
 */
void generateReport();

/**
 * Prompts the user to select a report period.
 */
void selectReportPeriod();

/**
 * Prints the admitted patients report for the specified period.
 */
void printPatientsAdmittedReport(int period);

/**
 * Prints the discharged patients report.
 */
void printDischargedPatientsReport();

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
 * Generates the admitted patients report for a specified period.
 * @param dateStr date as a string
 * @param period time period for report
 * @param report report string
 */
void generateAdmittedPatientsReport(const char* dateStr,
                                    int period,
                                    char* report);

/**
 * Processes a linked list of patient records and writes records
 * that meet the specified criteria to the report.
 *
 * @param head starting node
 * @param dateStart start date of time period
 * @param dateEnd end date of time period
 * @param report report string
 * @param length current report length
 * @param reportLength max length of report
 * @return number of patient records processed
 */
int processPatientRecords(const Node* head,
                          time_t      dateStart,
                          time_t      dateEnd,
                          char*       report,
                          int*        length,
                          int         reportLength);

/**
 * Generates the discharged patients report for a given date.
 * @param dateStr date as a string
 * @param report report string
 */
void generateDischargedPatientsReport(const char* dateStr,
                                      char* report);

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
 * Generates the report for the period selected.
 * @param sel the selected period
 */
void routePeriodSelection(int sel);

/**
 * Prints the generate report menu.
 */
void printReportMenu();

/**
 * Prints a list of options for the report period to span.
 */
void printPeriodSelectionMenu();

/*********Private Functions End************/
#endif //REPORT_H
