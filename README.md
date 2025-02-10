# Phase 1

## 1.1 Patient Record Management
- Store up to 50 patient
- Should be a struct
- Validators for
- Patient needs PRIMARY KEY, makes phase 2 easier
  - Patient ID (Int, unique)
  - Name (String, not null, not blank, not empty, not an number, no special characters)
  - Age (Int, not negative)
  - Diagnosis (String, not null, etc....)
  - Room Number (int, not negative)
  - 
```C
Struc Patient
{
  String patientID;
  String firstName;
  String lastName;
  int age;
  String diagnosis;
  int roomNumber;
}
```

## 1.2 Basic Operations on Patient Records

Add a new Patient record: void addNewPatient(void)
- Calls Patient record management with validators
- Adds to existing patient array

View All patient records: void viewAllPatientRecords(void)
- prints out all the entires in the patient array
- modularize print statements

Search for Patient: searchForPatientRecord()
- Search for duplicates before adding new patient
- Need for both ID and name
- Either overload or parse input to check type
- Or make menu option to either search by ID or name
- Print the record

Print patient record: printPatientRecord(patientID)
- Print the requested record to the screen

View all patient records: viewAllPatientRecords()
- Print all patient records to the screen

Discharge Patient: dischargePatient(patientRecord)
- Remove record from patient array
- Deal with gap in array somehow

## 1.3 Doctor Schedule Management (Isolated Module)
- 2D array (rows=dayOfWeek, col=shift[morning, afternoon, eve] <- should be enum)
- Need placeholder for no doctor shift
- Assume 1 doctor per shift

Add doctor to schedule: addDoctorToSchedule(doctor, dayOfWeek, enum->shift)
- access schedule 2D array

Remove doctor from schedule: clearShift(dayOfweek, shift)
- access to schedule 2D array

Display full weekly schedule: displayFullWeeklySchedule(void)
- print schedule to screen
- Make printDayMethod(dayOfWeek)
- 

Special cases:
- Shift already has assigned doctor while try to put a new one there
- Remove doctor from schedule

## 1.4 Input Validation
- Validators for
  - Patient ID (Int, unique)
  - Name (String, not null, not blank, not empty, not an number, no special characters)
  - Age (Int, not negative)
  - Diagnosis (String, not null, etc....)
  - Room Number (int, not negative)
    
## 1.5 Menu-Driven Interface
- Design text-based menu
Ex.
-------
1. Add Patient Record
2. View All Patients
3. Search Patient by ID
4. Discharge Patient
5. Manage Doctor Schedule
6. Exit
------

# Phase 2

Timescale of 12 months

## 2.1 Dynamic Memory Allocation
- Dynamically allocated memory using malloc and free
- Use points to struct


## 2.2 File Handling for Data Persistence
- Use linked lists to store patientRecords
- Malloc and Free

## 2.3 Advanced Data Strcutures for Efficiency
- Same as 2.2

## 2.4 Reporting and Analytics

Total Num Patient Admitted in day/week/month

- Make date struct using algorithm from Java lab 1

numAdmittedPatient(day)
numAdmittedPatient(week)
numAdmittedPatient(month)

List of patients dischated on specfic day

numDischageOnDay(day, week, month)

Doctor Utilization Report
- Assume we have a list of doctors already
- Need linked list of Docotors

```C
Struc Doctor
{
  String DoctorID;
  String firstName;
  String lastName;
}
```

Room Usage Reports
roomUsageReport()
- Actively being used

```
Struct Room
{
  int roomNumber; #Primary Key
  pointer to linked list of patient in room (Max 6 per room)
}
```

Output report: outputReportToFile()
1. call Number of patients admintted
  - numAdmittedPatient(day)
  - numAdmittedPatient(week)
  - numAdmittedPatient(month)
2. List of patients dischated on specific day
3. Doctor Utilization Report
4. Room usage report

## 2.5 Error Handling
- Handle file-related errors (e.g., missing files, read/write failures).
- Prevent memory leaks by ensuring all dynamically allocated memory is
freed before the program exits
-Implement input sanitization to prevent invalid data from corrupting
records
