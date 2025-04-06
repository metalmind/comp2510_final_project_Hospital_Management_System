#include "../inc/report.h"

#include <ctype.h>

#include "../inc/schedule.h"

#include <stdio.h>
#include <string.h>

/*********Public Functions Begin************/

void generateReport()
{
    int sel;

    do
    {
        sel = INVALID_INPUT;
        printReportMenu();
        getInput("Enter your selection: ",
                 &sel);
        routeReportMenu(sel);
    }
    while(sel != RETURN_TO_MAIN_MENU);
}

void selectReportPeriod()
{
    int sel;

    do
    {
        sel = INVALID_INPUT;
        printPeriodSelectionMenu();
        getInput("Enter your selection: ",
                 &sel);
        routePeriodSelection(sel);
    }
    while(sel != RETURN_TO_MAIN_MENU);
}

void printPatientsAdmittedReport(const int period)
{
    char report[MAX_REPORT_LEN]  = {0};
    char dateStr[DATE_MAX_CHARS] = {0};

    int year  = 0;
    int month = 0;
    int day   = 0;

    if(getDateInput(dateStr, &year, &month, &day) != READ_SUCCESS)
    {
        printf("Invalid date!\n");
        return;
    }

    generateAdmittedPatientsReport(dateStr,
                                   period,
                                   report);

    printf("%s",
           report);

    promptSaveReport(report,
                     "../res/patientsAdmittedReport.txt");
}

void printDischargedPatientsReport()
{
    char report[MAX_REPORT_LEN]  = {0};
    char dateStr[DATE_MAX_CHARS] = {0};
    int  year                    = 0;
    int  month                   = 0;
    int  day                     = 0;

    if(getDateInput(dateStr, &year, &month, &day) != READ_SUCCESS)
    {
        printf("Invalid date!\n");
        return;
    }

    generateDischargedPatientsReport(dateStr,
                                     report);

    printf("%s",
           report);

    promptSaveReport(report,
                     "../res/dischargeReport.txt");
}

void printDoctorUtilReport()
{
    char report[MAX_REPORT_LEN] = {0};
    int  schedule[DAYS_IN_WEEK][NUM_SHIFTS];

    getSchedule(schedule);
    generateDoctorUtilReport(schedule,
                             report);

    printf("%s",
           report);

    promptSaveReport(report,
                     "../res/doctorUtilReport.txt");
}

void printRoomUsageReport()
{
    char report[MAX_REPORT_LEN] = {0};

    generateRoomUsageReport(report);

    printf("%s",
           report);

    promptSaveReport(report,
                     "../res/roomUsageReport.txt");
}

/*********Public Functions End**************/

/*********Private Functions Begin**********/

void promptSaveReport(char* const       report,
                      const char* const fileName)
{
    while(TRUE)
    {
        char sel;
        getCharInput("\nWould you like to save a copy of this report? (y/n): ",
                     &sel);

        switch(sel)
        {
            case 'y':
                writeReportToFile(report,
                                  fileName);
                return;
            case 'n':
                return;
            default:
                puts("Invalid selection! Please try again.");
        }
    }
}

void writeReportToFile(char* const       report,
                       const char* const fileName)
{
    FILE* fPtr;
    int   error;

    if((fPtr = fopen(fileName, "w")) == NULL)
    {
        puts("\nSave could not be created.");
        return;
    }

    error = fprintf(fPtr,
                    "%s",
                    report);

    if(error < 1)
    {
        puts("Error writing to file.");
    }
    else
    {
        printf("\nReport saved!\n");
    }

    fclose(fPtr);
}

int generateHeader(char* report,
                   int   reportLength,
                   char* reportTitle)
{
    int   length;
    char* dateGenerated[DATE_MAX_CHARS];

    length = 0;
    dateFormat(time(NULL),
               dateGenerated);

    length += snprintf(report,
                       reportLength,
                       "%s\n%s\n%s\n",
                       "\n====================================",
                       reportTitle,
                       "====================================");
    length += snprintf(report + length,
                       reportLength - length,
                       "%s%s\n\n",
                       "Generated on: ",
                       dateGenerated);

    return length;
}

void generateAdmittedPatientsReport(const char* const dateStr,
                                    const int         period,
                                    char* const       report)
{
    time_t dateStart                   = {0};
    time_t dateEnd                     = {0};
    char   dateStartStr[DATE_MAX_CHARS]  = {0};
    char   dateEndStr[DATE_MAX_CHARS]  = {0};
    char   dateStrCopy[DATE_MAX_CHARS] = {0}; // for strtok operations

    int    length;
    int    admittedCount;

    strcpy(dateStartStr, dateStr);
    strcpy(dateStrCopy, dateStr);
    dateStart     = strToTime(dateStrCopy);
    length        = 0;
    admittedCount = 0;

    if(period == ADMITTED_REPORT_DAY)
    {
        dateEnd = dateStart;
    }
    else if(period == ADMITTED_REPORT_WEEK)
    {
        dateEnd = dateStart + 7 * 24 * 60 * 60;
    }
    else if(period == ADMITTED_REPORT_MONTH)
    {
        dateStart = getMonthStart(dateStart);
        dateFormat(dateStart, dateStartStr);
        dateEnd = getMonthEnd(dateStart);
    }

    dateFormat(dateEnd, dateEndStr);

    length += generateHeader(report,
                             MAX_REPORT_LEN,
                             "ADMITTED PATIENTS REPORT");

    length += snprintf(report + length,
                       MAX_REPORT_LEN - length,
                       "%-5s%-2s%-18s%-2s%-6s%-2s%-28s%-2s%s\n%s\n",
                       "ID",
                       "|",
                       "Name",
                       "|",
                       "Age",
                       "|",
                       "Diagnosis",
                       "|",
                       "Admission Date",
                       "-------------------------------------------------------------------------------------");

    admittedCount += processPatientRecords(patientRecordsStart,
                                           dateStart,
                                           dateEnd,
                                           report,
                                           &length,
                                           MAX_REPORT_LEN);
    admittedCount += processPatientRecords(dischargedPatientsStart,
                                           dateStart,
                                           dateEnd,
                                           report,
                                           &length,
                                           MAX_REPORT_LEN);

    if(admittedCount == 0)
    {
        if(period == ADMITTED_REPORT_DAY)
        {
            length += snprintf(report + length,
                               MAX_REPORT_LEN - length,
                               "There were no patients admitted on %s.\n",
                               dateStr);
        }
        else if(period == ADMITTED_REPORT_WEEK || period == ADMITTED_REPORT_MONTH)
        {
            length += snprintf(report + length,
                               MAX_REPORT_LEN - length,
                               "There were no patients admitted between %s and %s.\n",
                               dateStartStr,
                               dateEndStr);
        }
    }
    else
    {
        length += snprintf(report + length,
                           MAX_REPORT_LEN - length,
                           "\nTOTAL PATIENTS ADMITTED: %d\n",
                           admittedCount);
    }
}

int processPatientRecords(const Node* const head,
                          const time_t      dateStart,
                          const time_t      dateEnd,
                          char* const       report,
                          int* const        length,
                          const int         reportLength)
{
    int admittedCount;
    admittedCount = 0;

    for(Node* node = head; node != NULL; node = node->next)
    {
        patient* patientRecord;
        patientRecord = node->record;

        if(patientRecord->admissionDate >= dateStart &&
           patientRecord->admissionDate <= dateEnd)
        {
            char admitDate[DATE_MAX_CHARS] = {0};
            dateFormat(patientRecord->admissionDate,
                       admitDate);

            *length += snprintf(report + *length,
                                reportLength - *length,
                                "%-5d%-2s%-18s%-2s%-6d%-2s%-28s%-2s%s\n",
                                patientRecord->patientID,
                                "|",
                                patientRecord->name,
                                "|",
                                patientRecord->age,
                                "|",
                                patientRecord->diagnosis,
                                "|",
                                admitDate);

            admittedCount++;
        }
    }

    return admittedCount;
}

void generateDischargedPatientsReport(const char* const dateStr,
                                      char* const       report)
{
    char   dateStrCopy[DATE_MAX_CHARS] = {0};
    time_t date;
    int    length;
    int    dischargedCount;

    strcpy(dateStrCopy, dateStr);
    date            = strToTime(dateStrCopy);
    length          = 0;
    dischargedCount = 0;

    length += generateHeader(report,
                             MAX_REPORT_LEN,
                             "DISCHARGED PATIENTS REPORT");

    length += snprintf(report + length,
                       MAX_REPORT_LEN - length,
                       "%-5s%-2s%-18s%-2s%-6s%-2s%-28s%-2s%s\n%s\n",
                       "ID",
                       "|",
                       "Name",
                       "|",
                       "Age",
                       "|",
                       "Diagnosis",
                       "|",
                       "Discharge Date",
                       "-------------------------------------------------------------------------------------");

    for(Node* node = dischargedPatientsStart; node != NULL; node = node->next)
    {
        patient* patientRecord;
        patientRecord = node->record;

        if(patientRecord->dischargeDate == date)
        {
            length += snprintf(report + length,
                               MAX_REPORT_LEN - length,
                               "%-5d%-2s%-18s%-2s%-6d%-2s%-28s%-2s%s\n",
                               patientRecord->patientID,
                               "|",
                               patientRecord->name,
                               "|",
                               patientRecord->age,
                               "|",
                               patientRecord->diagnosis,
                               "|",
                               dateStr);
            dischargedCount++;
        }
    }

    if(dischargedCount == 0)
    {
        length += snprintf(report + length,
                           MAX_REPORT_LEN - length,
                           "There were no patients discharged on %s.\n",
                           dateStr);
    }
}

void generateDoctorUtilReport(const int   schedule[DAYS_IN_WEEK][NUM_SHIFTS],
                              char* const report)
{
    int length;
    length = 0;

    length += generateHeader(report,
                             MAX_REPORT_LEN,
                             "DOCTOR UTILIZATION REPORT");

    length += snprintf(report + length,
                       MAX_REPORT_LEN - length,
                       "%s\n%s\n",
                       "SHIFTS COVERED",
                       "------------------------------------");

    int doctorReferences[DOC_ID_MAX_VALUE] = {0};

    for(int i = 0; i < DAYS_IN_WEEK; i++)
    {
        for(int j = 0; j < NUM_SHIFTS; j++)
        {
            int shiftKey = schedule[i][j];

            if(shiftKey != UNASSIGNED_SHIFT)
            {
                doctorReferences[shiftKey - INDEX_OFFSET]++;
            }
        }
    }

    for(Node* node = doctorRecordsStart; node != NULL; node = node->next)
    {
        char    doctorName[DOCTOR_TITLE_CHARS + FULL_NAME_MAX_CHAR];
        doctor* doc;
        doc = node->record;

        strcpy(doctorName, "Dr. ");
        strcat(doctorName, doc -> firstName);
        strcat(doctorName, " ");
        strcat(doctorName, doc -> lastName);

        length += snprintf(report + length,
                           MAX_REPORT_LEN - length,
                           "%s: %d shifts\n",
                           doctorName,
                           doctorReferences[doc->doctorID - INDEX_OFFSET]);
    }

    if(getTotalDoctors() == 0)
    {
        length += snprintf(report + length,
                           MAX_REPORT_LEN - length,
                           "There are no doctors at this hospital.\n");
    }
}

void generateRoomUsageReport(char* const report)
{
    int roomReferences[ROOM_NUMBER_MAX] = {0};
    int length;

    length = 0;

    length += generateHeader(report,
                             MAX_REPORT_LEN,
                             "ROOM USAGE REPORT");

    length += snprintf(report + length,
                       MAX_REPORT_LEN - length,
                       "%-8s%-2s%s\n%s\n",
                       "ROOM #",
                       "|",
                       "Number of Occupants",
                       "------------------------------------");

    for(Node* node = patientRecordsStart; node != NULL; node = node->next)
    {
        patient* patientRecord;
        patientRecord = node->record;

        roomReferences[patientRecord->roomNumber - INDEX_OFFSET]++;
    }

    for(int i = 0; i < ROOM_NUMBER_MAX; i++)
    {
        length += snprintf(report + length,
                           MAX_REPORT_LEN - length,
                           "%-8d%-2s%d\n",
                           i + INDEX_OFFSET,
                           "|",
                           roomReferences[i]);
    }
}

void routeReportMenu(const int sel)
{
    switch(sel)
    {
        case ADMITTED_PATIENTS_REPORT:
            selectReportPeriod();
            break;
        case DISCHARGED_PATIENTS_REPORT:
            printDischargedPatientsReport();
            break;
        case DOCTOR_UTILIZATION_REPORT:
            printDoctorUtilReport();
            break;
        case ROOM_USAGE_REPORT:
            printRoomUsageReport();
            break;
        case RETURN_TO_MAIN_MENU:
            printf("Returning to menu...\n");
            break;
        default:
            printf("Invalid input! Try again.\n");
    }
}

void routePeriodSelection(const int sel)
{
    switch(sel)
    {
        case ADMITTED_REPORT_DAY:
            printPatientsAdmittedReport(ADMITTED_REPORT_DAY);
            break;
        case ADMITTED_REPORT_WEEK:
            printPatientsAdmittedReport(ADMITTED_REPORT_WEEK);
            break;
        case ADMITTED_REPORT_MONTH:
            printPatientsAdmittedReport(ADMITTED_REPORT_MONTH);
            break;
        case RETURN_TO_MAIN_MENU:
            printf("Returning to menu...\n");
            break;
        default:
            printf("Invalid input! Try again.\n");
    }
}

void printReportMenu()
{
    printf("\nReport Menu\n");
    printf("%d. Return to Menu\n", RETURN_TO_MAIN_MENU);
    printf("%d. Patients Admitted per Period\n", ADMITTED_PATIENTS_REPORT);
    printf("%d. List of Discharged Patients\n", DISCHARGED_PATIENTS_REPORT);
    printf("%d. Doctor Utilization Report\n", DOCTOR_UTILIZATION_REPORT);
    printf("%d. Room Usage Report\n", ROOM_USAGE_REPORT);
}

void printPeriodSelectionMenu()
{
    printf("\nSelect Report Period\n");
    printf("%d. Return to Menu\n", RETURN_TO_MAIN_MENU);
    printf("%d. By Day\n", ADMITTED_REPORT_DAY);
    printf("%d. By Week\n", ADMITTED_REPORT_WEEK);
    printf("%d. By Month\n", ADMITTED_REPORT_MONTH);
}

/*********Private Functions End************/
