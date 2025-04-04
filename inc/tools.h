/**
 * Tools handles generic input and validation related functions.
 *
 * @author Alison Kim
 * @author Owen Wou
 * @version February 2025
 */

#ifndef TOOLS_H
#define TOOLS_H

#include<stdlib.h>

#define TRUE 1
#define FALSE 0

#define INVALID_INPUT (-1)

#define READ_SUCCESS 1

#define PROMPT_MAX_CHAR 50
#define DATE_MAX_CHARS 20
#define TERMINAL_CHAR 0

#define EMPTY_STRING 0

#define ENTRY_REMOVAL_OFFSET 1
#define NEXT_ENTRY_OFFSET 1

#define TM_YEAR_OFFSET 1900
#define YEAR_INDEX 0
#define MONTH_INDEX 1
#define DAY_INDEX 2
#define MAX_ELEM_Y_M_D 3
#define DEFAULT_VALUE_ZERO 0

#include <time.h>

typedef struct node Node;

struct node
{
    void* record;
    Node* next;
};

/*********Private Functions Begin************/
/**
 * Wrapper function which prompts for valid input from the user, re-prompting
 * in case of invalid input.
 *
 * @param prompt prompt message
 * @param errorMessage error message
 * @param lowerBound lower bound of valid range
 * @param upperBound upper bound of valid range
 * @return valid input
 */
int promptForInput(const char* prompt,
                   const char* errorMessage,
                   int lowerBound,
                   int upperBound);

/**
 * Wrapper function which prompts for valid and unique input from the user,
 * re-prompting in case of invalid or duplicate input.
 *
 * @param prompt prompt message
 * @param errorMessage error message
 * @param duplicateErrorMessage error message for duplicate input
 * @param isUniqueInput function that returns true if input is unique, otherwise false
 * @param lowerBound lower bound of valid range
 * @param upperBound upper bound of valid range
 * @return valid unique input
 */
int promptForUniqueInput(const char* prompt,
                         const char* errorMessage,
                         const char* duplicateErrorMessage,
                         int(*isUniqueInput)(int),
                         int lowerBound,
                         int upperBound);

/**
 * Wrapper function which prompts for a valid name String from the user,
 * re-prompting in case of invalid input.
 * @param prompt prompt message
 * @param input char array to assign input
 * @param maxChars maximum allowed characters
 */
void promptForNameStr(const char* prompt,
                      char* input,
                      int maxChars);

/**
 * Wrapper function for scanf() which takes a prompt message to print and
 * a value to which to assign the input. Clears the input buffer in case of invalid
 * input.
 *
 * @param prompt prompt message
 * @param input value to assign input
 * @return number of items successfully read
 */
int getInput(const char* prompt,
             int* input);

/**
 * Validates whether input value is of valid type (i.e., has been successfully read
 * and assigned) and within range.
 *
 * @param numItemsRead number of items successfully read
 * @param input data value to validate
 * @param lowerBound lower bound of valid range
 * @param upperBound upper bound of valid range
 * @param errorMessage error message to print should data be invalid
 * @return TRUE is data value is valid, otherwise FALSE
 */
int validateData(int numItemsRead,
                 int input,
                 int lowerBound,
                 int upperBound,
                 const char* errorMessage);

/**
 * Validates whether input read was successful - checks that numItemsRead
 * is equal to READ_SUCCESS, indicating that an integer value was successfully
 * extracted and assigned.
 *
 * @param numItemsRead number of items successfully read
 * @return TRUE if input type is valid, otherwise FALSE
 */
int validateInputType(int numItemsRead);

/**
 * Validates whether number is within valid range.
 *
 * @param num number to validate
 * @param lowerBound lower bound of valid range
 * @param upperBound upper bound of valid range
 * @return TRUE if number is within valid range, otherwise FALSE
 */
int validateNum(int num,
                int lowerBound,
                int upperBound);

/**
 * Validates whether the name is valid (i.e., is not null or blank, does not
 * start or end with a space, and does not contain numbers or special characters).
 *
 * @param name name to validate
 * @return TRUE if name is valid, otherwise FALSE
 */
int validateName(const char* name);

/**
 * Wrapper function for fgets() which takes a prompt message to print and
 * a char array to which to assign the input.
 *
 * @param prompt prompt message
 * @param input char array to assign input
 * @param maxChar maximum characters allowed
 * @return
 */
void getStringInput(const char* prompt,
                    char* input,
                    int maxChar);

/**
 * Checks whether a given string is blank - i.e., is empty or consists
 * of only spaces.
 * @param str string to check if blank
 * @return TRUE if string is blank, otherwise FALSE
 */
int isBlank(const char* str);

/**
 * Helper method to flush the input buffer in the case of invalid inputs.
 */
void clearInputBuffer(void);

/**
 * Helper function that prints the specified number of dashes to the screen.
 * @param numDashes number of dashes to print
 */
void printDashes(int numDashes);

/**
 * Returns the date formatted as YYYY-MM-DD HH:MM:SS.
 * @param date date to format
 * @param formattedDate formatted date
 */
void dateFormat(time_t date,
                char* formattedDate);

/**
 * Helper function to convert string to time.
 * @param str
 * @return
 */
time_t strToTime(char*
    str);

/**
 * Swaps characters out of the string.
 * @param str String to clean.
 * @param dirtyChar 'Bad' character remove.
 * @param cleanChar 'Clean' character to insert.
 */
void sanitizeStr(char * str,  char dirtyChar, char cleanChar);
/*********Private Functions End**************/


#endif //TOOLS_H
