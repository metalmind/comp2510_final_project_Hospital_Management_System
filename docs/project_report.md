# Project Report

| Name       | Student # |
|------------|-----------|
| Owen Wou   | A00989377 |
| Alison Kim | A01434656 |

*A comprehensive report, 2-5 pages long, covering the following headings.*

## 1. Project Objectives and Scope

*Outline the goals and scope of the project.*

The objective of this project is to design and implement a Hospital Management
System in the C programming language. The system will allow for management of patient
records, doctor records, and hospital shift scheduling.

Phase 1 implements foundational programming concepts that we have learned, in a
modular fashion to implement the basic functionality of the system. This includes
handling of user input as well as validation checks for data integrity and type
compliance.

## 2. Design and Implementation Details

*Describe the design approach and implementation steps*.

Our design approach relies heavily on every section being as modular as possible
and maintaining strong coding standards.

### 2. Features Implemented

![top_level_diagram.svg](top_level_diagram.svg)


#### 2.1 Patient Records Management

Each patient record was implemented as a struct, with the information and
limitations from Table 2.1. The implementation for the validation of these inputs are discussed further in section
[2.4 Input Validation](#24-input-validation).
These structs are then held in a patient array with a max size of 50, as per the
requirements of the project.

Table 2.1 Patient Data Structure

| Description | Datatype | Not Null | Not Blank | Unique | Min Value | Max Value |
|-------------|:--------:|:--------:|:---------:|:------:|:---------:|:---------:|
| Patient ID  |   int    |   N/A    |    N/A    |   Y    |     1     |    50     |
| Name        |  String  |    Y     |     Y     |   N    |    N/A    |    N/A    |
| Age         |   int    |   N/A    |    N/A    |   N    |     0     |    100    |
| Diagnosis   |  String  |    Y     |     Y     |   N    |    N/A    |    N/A    |
| Room Number |   int    |   N/A    |    N/A    |   Y    |     1     |    200    |

#### 2.2 Basic Operations on Patient Records

#### 2.2.2 Add a new patient record: void addNewPatientRecord(void)
- Add a new patient to the patientRecord array, ensuring each entry has a unique ID

#### 2.2.3 Search for patient record: searchForPatientRecord(void)
- Search for patient records matching the specified criteria
- Menu options to search by ID and or by name, leveraging idExists() and strcmp
- Print matching record(s)

#### 2.2.4 Print patient record: printPatientRecord(patientRecord)
- Print the specified patient record to the screen

#### 2.2.5 View all patient records: void viewAllPatientRecords(void)
- Print out all patient records in the patient array

#### 2.2.6 Discharge Patient: dischargePatient(void)
- Remove patient record from patient array
- Resulting gap in the array is addressed by shifting each element one place to the left

#### 2.3 Doctor Management

| Description | Datatype | Not Null | Not Blank | Unique | Min Value | Max Value |
|-------------|:--------:|:--------:|:---------:|:------:|:---------:|:---------:|
| Doctor ID   |   int    |   N/A    |    N/A    |   Y    |     1     |    10     |
| First Name  |  String  |    Y     |     Y     |   N    |    N/A    |    N/A    |
| Last Name   |  String  |    Y     |     Y     |   N    |    N/A    |    N/A    |
| Specialty   |  String  |    N     |     N     |   N    |    N/A    |    N/A    |

#### 2.4 Shift Management

#### 2.5 Input Validation

#### 2.6 Menu Driven Interface

## 3. Challenges and Solutions

*Discuss any challenges faced during the project and how they were overcome.*

Some of the challenges we faced are as follows:

### 3.1 Separating out Struct in patient.h and patient.c, took a while to figure out struct should be in .h file

### 3.2 Learning where to decompose functions and implement reuse

### 3.3 Issues assigning Strings to schedules after they have been initially assigned

When initially prototyping the schedule module, we were putting the doctors' 
names to indicate that a doctor was assigned a schedule. This lead to an 
issue of reassigning the shifts in the char array because once they are 
initialized they become a string literal which are immutable.

To solve this we make each doctor a struct with a unique ID which acts as a 
primary key. This then allows us to make the schedule array an array of ints 
instead of char* and lets us change the shift assignments much more easily. 
The tradeoff of this being that displaying the schedule requires more 
overhead before the doctor's name can be displayed, however this is a small 
tradeoff in comparison.

## 4. Testing Procedures and Results

*Explain the testing methods used and present the results.*

## 5. Conclusion

*Summarize the project outcomes.*

This is a test for the linter
