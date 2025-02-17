#ifndef DOCTOR_H
#define DOCTOR_H

#define NAME_MAX_CHAR 25

#define MAX_DOCTORS 10

#define ID_NOT_FOUND -1

typedef struct doctor doctor;

struct doctor
{
    int doctorID;
    char lastName[NAME_MAX_CHAR];
    char firstName[NAME_MAX_CHAR];
};

#endif //DOCTOR_H
