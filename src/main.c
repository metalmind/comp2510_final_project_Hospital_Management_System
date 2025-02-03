
#include <stdio.h>
#include "menu.h"

#define NAME_MAX_CHAR 50
#define DIAGNOSIS_MAX_CHAR 75

struct patient
{
    int patientID;
    char name[NAME_MAX_CHAR];
    int age;
    char diagnosis[DIAGNOSIS_MAX_CHAR];
    int roomNumber;
};


int main(void)
{
    struct patient patient0 = {0, "John", 29, "Concussion", 5};

    printf("PatientID: %d\n", patient0.patientID);
    printf("Patient Name: %s\n", patient0.name);
    printf("Patient Age: %d\n", patient0.age);
    printf("Patient Diagnisis: %s\n", patient0.diagnosis);
    printf("Patient Room #: %d\n", patient0.roomNumber);
    return 0;
}

