//
// Created by Owen on 13/02/2025.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../inc/tools.h"
#include "../inc/patient.h"

/*********Private Functions Begin************/
int promptForInput(const char* const prompt,
                   const char* const errorMessage,
                   const int         lowerBound,
                   const int         upperBound)
{
    int input;
    int valid;

    input = INVALID_INPUT;
    valid = FALSE;

    do
    {
        int numItemsRead;

        numItemsRead = getInput(prompt,
                                &input);

        valid = validateData(numItemsRead,
                             input,
                             lowerBound,
                             upperBound,
                             errorMessage);
    }
    while(!valid);

    return input;
}

int promptForUniqueInput(const char* const prompt,
                         const char* const errorMessage,
                         const char* const duplicateErrorMessage,
                         int (*            isUniqueInput)(int),
                         const int         lowerBound,
                         const int         upperBound)
{
    int input;
    int valid;
    int unique;

    valid  = FALSE;
    unique = FALSE;

    do
    {
        input = INVALID_INPUT;

        int numItemsRead;

        numItemsRead = getInput(prompt,
                                &input);
        unique = isUniqueInput(input);

        valid = validateData(numItemsRead,
                             input,
                             lowerBound,
                             upperBound,
                             errorMessage);

        if(valid && !unique)
        {
            printf("%s", duplicateErrorMessage);
        }
    }
    while(!(valid && unique));

    return input;
}

void promptForNameStr(const char* const prompt,
                      char* const       input,
                      const int         maxChars)
{
    int valid;

    valid = FALSE;

    do
    {
        getStringInput(prompt,
                       input,
                       maxChars);
        valid = validateName(input);

        if(!valid)
        {
            printf("Invalid name! Only alphabetic characters allowed.\n");
        }
    }
    while(!valid);
}

int getInput(const char* const prompt,
             int* const        input)
{
    int numItemsRead;

    printf("%s",
           prompt);
    numItemsRead = scanf("%d",
                         input);
    clearInputBuffer();

    return numItemsRead;
}

int getDateInput(char* const dateStr,
                 int*        year,
                 int*        month,
                 int*        day)
{
    getStringInput("Enter a date (YYYY-MM-DD): ",
                   dateStr,
                   DATE_MAX_CHARS);

    sscanf(dateStr,
           "%d-%d-%d",
           year,
           month,
           day);

    if(validateDate(*year, *month, *day))
    {
        return TRUE;
    }

    return FALSE;
}

int validateData(const int         numItemsRead,
                 const int         input,
                 const int         lowerBound,
                 const int         upperBound,
                 const char* const errorMessage)
{
    int valid = FALSE;

    valid = validateInputType(numItemsRead) && validateNum(input,
                                                           lowerBound,
                                                           upperBound);

    if(!valid)
    {
        printf("%s",
               errorMessage);
    }

    return valid;
}

int validateInputType(const int numItemsRead)
{
    int valid;

    valid = FALSE;

    if(numItemsRead == READ_SUCCESS)
    {
        valid = TRUE;
    }

    return valid;
}

int validateNum(const int num,
                const int lowerBound,
                const int upperBound)
{
    int valid;

    valid = FALSE;

    if(num >= lowerBound && num <= upperBound)
    {
        valid = TRUE;
    }

    return valid;
}

int validateName(const char* const name)
{
    size_t nameLength;

    nameLength = strlen(name);

    if(name == NULL ||
       isBlank(name))
    {
        return FALSE;
    }

    for(size_t i = 0; i < nameLength; i++)
    {
        if(!(isalpha(name[i]) || name[i] == ' '))
        {
            return FALSE;
        }
    }

    return TRUE;
}

int validateDate(int year,
                 int month,
                 int day)
{
    int numDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int validYear = validateNum(year,
                                1970,
                                2038);

    int validMonth = validateNum(month,
                                 1,
                                 12);

    // check month & year are valid to avoid index out of bounds for day
    if(!(validMonth && validYear))
    {
        return FALSE;
    }

    int leapYear = isLeapYear(year);
    if(leapYear)
    {
        numDays[1] = 29; // set february max day to 29 in lap year
    }

    int validDay = validateNum(day,
                               1,
                               numDays[month - 1]);

    if(!validDay)
    {
        return FALSE;
    }

    return TRUE;
}

int isLeapYear(int year)
{
    if(year % 100 == 0)
    {
        if(year % 400 == 0)
        {
            return TRUE;
        }
        return FALSE;
    }

    if(year % 4 == 0)
    {
        return TRUE;
    }
    return FALSE;
}

void getCharInput(const char* const prompt,
                  char* const       input)
{
    char sel;

    printf("%s", prompt);
    sel = getchar();
    sel = tolower(sel);

    *input = sel;

    clearInputBuffer();
}

void getStringInput(const char* const prompt,
                    char* const       input,
                    const int         maxChar)
{
    size_t length;
    int    exceedMaxChar;

    printf("%s", prompt);
    fgets(input,
          maxChar,
          stdin);

    length = strcspn(input,
                     "\n");
    exceedMaxChar = strchr(input, '\n') == NULL;

    if(exceedMaxChar)
    {
        clearInputBuffer();
    }

    input[length] = TERMINAL_CHAR;
}

int isBlank(const char* const str)
{
    size_t length;

    length = strlen(str);

    if(length == EMPTY_STRING)
    {
        return TRUE;
    }

    for(size_t i = 0; i < length; i++)
    {
        if(!isspace(str[i]))
        {
            return FALSE;
        }
    }

    return TRUE;
}

void clearInputBuffer()
{
    while(getchar() != '\n');
}

void printDashes(const int numDashes)
{
    for(int i = 0; i < numDashes; i++)
    {
        printf("%c", '-');
    }
}

void dateFormat(const time_t date,
                char*        formattedDate)
{
    strftime(formattedDate,
             DATE_MAX_CHARS,
             "%Y-%m-%d",
             localtime(&date));
}

time_t strToTime(char* str)
{
    int    date[MAX_ELEM_Y_M_D];
    int    dateIndex;
    time_t time;

    dateIndex = 0;

    char* tokenPtr = strtok(str, "-");
    while(tokenPtr != NULL)
    {
        date[dateIndex] = atoi(tokenPtr);
        // printf("%d\n", date[dateIndex]);
        tokenPtr = strtok(NULL, "-");
        dateIndex++;
    }

    struct tm timeStruct;

    timeStruct.tm_year  = date[YEAR_INDEX] - TM_YEAR_OFFSET;
    timeStruct.tm_mon   = date[MONTH_INDEX] - TM_MONTH_OFFSET;
    timeStruct.tm_mday  = date[DAY_INDEX];
    timeStruct.tm_hour  = DEFAULT_VALUE_ZERO;
    timeStruct.tm_min   = DEFAULT_VALUE_ZERO;
    timeStruct.tm_sec   = DEFAULT_VALUE_ZERO;
    timeStruct.tm_isdst = DEFAULT_VALUE_ZERO;

    time = mktime(&timeStruct);

    return time;
}

time_t getCurrentDate()
{
    time_t today;

    time_t currentTime = time(NULL);

    struct tm* timeStruct = localtime(&currentTime);

    // zero initialize time
    timeStruct->tm_mon   = 3;
    timeStruct->tm_hour  = DEFAULT_VALUE_ZERO;
    timeStruct->tm_min   = DEFAULT_VALUE_ZERO;
    timeStruct->tm_sec   = DEFAULT_VALUE_ZERO;
    timeStruct->tm_isdst = DEFAULT_VALUE_ZERO;

    today = mktime(timeStruct);

    return today;
}

time_t getMonthStart(time_t date)
{
    time_t monthStart;
    struct tm* timeStruct = localtime(&date);

    timeStruct->tm_mday = 1;
    timeStruct->tm_hour = 0;
    timeStruct->tm_min = 0;
    timeStruct->tm_sec = 0;

    monthStart = mktime(timeStruct);

    return monthStart;
}

time_t getMonthEnd(time_t date)
{
    time_t monthEnd;

    struct tm* timeStruct = localtime(&date);

    timeStruct->tm_mon += 1;
    timeStruct->tm_mday = 1;
    timeStruct->tm_sec = 0;
    timeStruct->tm_min = 0;
    timeStruct->tm_hour = 0;

    // subtract one second to make it the previous day
    monthEnd = mktime(timeStruct) - 1;

    return monthEnd;
}

void sanitizeStr(char* str,
                 char  dirtyChar,
                 char  cleanChar)
{
    int index = 0;
    while(str[index] != '\0')
    {
        if(str[index] == dirtyChar)
        {
            str[index] = cleanChar;
        }
        index++;
    }
}


/*********Private Functions End**************/
