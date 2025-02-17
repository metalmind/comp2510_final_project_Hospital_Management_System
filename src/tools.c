//
// Created by Owen on 13/02/2025.
//

#include<stdio.h>
#include<string.h>
#include "../inc/tools.h"

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

void clearInputBuffer()
{
    while(getchar() != '\n');
}