/**
 * Tools handles generic input and validation related functions.
 *
 * @author Alison Kim
 * @author Owen Wou
 * @version February 2025
 */

#ifndef TOOLS_H
#define TOOLS_H

#define TRUE 1
#define FALSE 0

#define READ_SUCCESS 1

#define TERMINAL_CHAR 0

/**
 * Wrapper function for scanf() which takes a prompt message to print and
 * a value to which to assign the input. Clears the input buffer in case of invalid
 * input.
 *
 * @param prompt prompt message
 * @param input value to assign input
 * @return number of items successfully read
 */
int getInput(const char* const prompt,
             int* const input);

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
                 const char* const errorMessage);

/**
 * Validates whether input read was successful - checks that numItemsRead
 * is equal to READ_SUCCESS, indicating that an integer value was successfully
 * extracted and assigned.
 *
 * @param numItemsRead number of items successfully read
 * @return 1 if input type is valid, otherwise 0
 */
int validateInputType(int numItemsRead);

/**
 * Validates whether number is within valid range.
 *
 * @param num number to validate
 * @param lowerBound lower bound of valid range
 * @param upperBound upper bound of valid range
 * @return 1 if number is within valid range, otherwise 0
 */
int validateNum(int num,
                int lowerBound,
                int upperBound);

/**
 * Wrapper function for fgets() which takes a prompt message to print and
 * a char array to which to assign the input.
 *
 * @param prompt prompt message
 * @param input char array to assign input
 * @param maxChar maximum characters allowed
 * @return
 */
void getStringInput(const char* const prompt,
                    char* const input,
                    int maxChar);

/**
 * Helper method to flush the input buffer in the case of invalid inputs.
 */
void clearInputBuffer(void);

#endif //TOOLS_H
