//
// Created by Owen on 13/02/2025.
//

#include<stdio.h>
#include<string.h>
#include "../inc/tools.h"

int getInput(char* prompt,
             int* input)
{
    int numItemsRead;

    printf("%s",
           prompt);
    numItemsRead = scanf("%d",
                         input);
    clearInputBuffer();

    return numItemsRead;
}

int validateData(int numItemsRead,
                 int input,
                 int lowerBound,
                 int upperBound,
                 char* errorMessage)
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


void getStringInput(char* prompt,
                    char* input,
                    int maxChar)
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