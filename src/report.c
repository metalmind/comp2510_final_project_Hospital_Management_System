#include "../inc/report.h"

#include <ctype.h>

#include "../inc/schedule.h"

#include <stdio.h>
#include <string.h>
#include <limits.h>

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

void printDischargedPatientsReport()
{
    char report[MAX_REPORT_LEN]  = {0};
    char dateStr[DATE_MAX_CHARS] = {0};
    int  year                    = 0;
    int  month                   = 0;
    int  day                     = 0;

    if(getDateInput(dateStr, &year, &month, &day) != READ_SUCCESS)
    {
        printf("Invalid date!");
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
    printf("\nReport saved!\n");
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

void generateAdmittedPatientsReport()
{
}

void generateDischargedPatientsReport(const char* const dateStr,
                                      char* const       report)
{
    char dateStrCopy[DATE_MAX_CHARS] = {0};
    time_t date;
    int    length;
    int dischargedCount;

    strcpy(dateStrCopy, dateStr);
    date   = strToTime(dateStrCopy);
    length = 0;
    dischargedCount = 0;

    length += generateHeader(report,
                             MAX_REPORT_LEN,
                             "DISCHARGED PATIENTS REPORT");

    for(Node* node = dischargedPatientsStart; node != NULL; node = node->next)
    {
        patient* patientRecord;
        patientRecord = node->record;

        if(patientRecord->dischargeDate == date)
        {
            printPatientRecord(patientRecord);
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

void printReportMenu()
{
    printf("\n%d. Return to Menu\n", RETURN_TO_MAIN_MENU);
    printf("%d. Patients Admitted per Period\n", ADMITTED_PATIENTS_REPORT);
    printf("%d. List of Discharged Patients\n", DISCHARGED_PATIENTS_REPORT);
    printf("%d. Doctor Utilization Report\n", DOCTOR_UTILIZATION_REPORT);
    printf("%d. Room Usage Report\n", ROOM_USAGE_REPORT);
}

/*********Private Functions End************/
