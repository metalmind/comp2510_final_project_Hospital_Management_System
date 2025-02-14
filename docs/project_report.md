# Project Report

| Name       | Student # |
|------------|-----------|
| Owen Wou   | A00989377 |
| Alison Kim | A01434656 |

*A comprehensive report, 2-5 pages long, covering the following headings.*

## 1. Project Objectives and Scope

*Outline the goals and scope of the project.*

The objective of this project is to design and implement a Hospital Management
System in the C programming language. The system will manage patient records and
doctor scheduling.

Phase 1 implements foundational programming concepts that we learned, in a
modular fashion to implement the basic
functionality of hte system.

## 2. Design and Implementation Details

*Describe the design approach and implementation steps*.

Our design approach relies heavily on every section being as modular as possible
and maintaining strong coding standards.

### 2. Features Implemented

#### 2.1 Patient Records Management

Each patient record was implemented as a struct, with the information and
limitations from Table 2.1. The implementation for the
validation of these inputs are discussed further in section
[2.4 Input Validation](#24-input-validation).
These structs are then held in an array with a max size of 50, as per the
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

#### 2.3 Doctor Schedule Management

#### 2.4 Input Validation

#### 2.5 Menu Driven Interface

## 3. Challenges and Solutions

*Discuss any challenges faced during the project and how they were overcome.*

Some of the challenges we faced are as follows:

- Separating out Struct in patient.h and patient.c, took a while to figure out
  struct should be in .h file
- Learning where to decompose functions and implement reuse


## 4. Testing Procedures and Results

*Explain the testing methods used and present the results.*

## 5. Conclusion

*Summarize the project outcomes.*

This is a test for the linter
