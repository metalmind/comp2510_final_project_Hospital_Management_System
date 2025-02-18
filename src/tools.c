//
// Created by Owen on 13/02/2025.
//

#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include "../inc/tools.h"

int promptForInput(const char* const prompt,
                   const char* const errorMessage,
                   const int lowerBound,
                   const int upperBound)
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

int getInput(const char* const prompt,
             int* const input)
{
    int numItemsRead;

    printf("%s",
           prompt);
    numItemsRead = scanf("%d",
                         input);
    clearInputBuffer();

    return numItemsRead;
}

int validateData(const int numItemsRead,
                 const int input,
                 const int lowerBound,
                 const int upperBound,
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

    for (size_t i = 0; i < nameLength; i++)
    {
        if (!(isalpha(name[i]) || name[i] == ' '))
        {
            return FALSE;
        }
    }

    return TRUE;
}

void getStringInput(const char* const prompt,
                    char* const input,
                    const int maxChar)
{
    size_t length;

    printf("%s", prompt);
    fgets(input,
          maxChar,
          stdin);
    length = strcspn(input,
                     "\n");

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