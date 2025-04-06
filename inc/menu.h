/**
 * Menu handles all the functionality regarding the printing the menu to screen
 * and routing the selection to the correct function.
 *
 * @author Owen Wou
 * @version February 2025
 */
#ifndef MENU_H
#define MENU_H

// Main menu Constants
#define EXIT 0
#define PATIENT_MENU 1
#define DOCTOR_MENU 2
#define SCHEDULE_MENU 3
#define GENERATE_REPORT 4
#define SAVE_LOAD_DATA 5
#define VIEW_ALL 6

// Patient menu
#define ADD_PATIENT_RECORDS 1
#define DISCHARGE_PATIENT 2
#define VIEW_ALL_PATIENTS 3
#define SEARCH_PATIENT 4

// Save/Load Constants
#define SAVE_ALL_PATIENT_RECORDS 1
#define LOAD_PATIENT_RECORDS 2
#define SAVE_ALL_DOCTOR_RECORDS 3
#define LOAD_ALL_DOCTOR_RECORDS 4
#define SAVE_ALL_SCHEDULE_RECORDS 5
#define LOAD_ALL_SCHEDULE_RECORDS 6
#define SAVE_ALL 7
#define LOAD_ALL 8


/*********Public Functions Begin************/
/**
 * A text-based menu to guide user interaction.
 *
 * Example menu:
 *    1. Add Patient Record
 *    2. View All Patients
 *    3. Search Patient by ID
 *    4. Discharge Patient
 *    5. Manage Doctor Schedule
 *    6. Exit
 */
void menu(void);
/*********Public Functions End**************/

/*********Private Functions Begin************/
/**
 * Helper function to print the menu options to the screen.
 */
void printMenu(void);

/**
 * Routes to the selected save menu item.
 */
void routeSaveMenu(void);

/**
 * Helper function to print the save / load options to the screen.
 */
void printSaveMenu(void);

/**
 * Prompts the user to input a selection and returns the integer.
 *
 * @return sel an int
 */
int getSelection(void);

/**
 * Routes to the selected menu item by calling the functon associated with the
 * selection. If the selection is not available, tells the user to try again.
 *
 * @param sel an int
 */
void routeSelection(int sel);

/**
 * Routes to the selected save / load function.
 *
 * @param sel an int
 */
void routeSaveSelection(int sel);

/**
 * The engine for the patient menu.
 */
void patientMenu(void);

/**
 * Routes the selected Patient menu function.
 * @param sel
 */
void routePatientMenuSelection(const int sel);

/**
 * Prints the patient menu to the screen.
 */
void printPatientMenu();

/**
 * Reads the save files for patients, discharged patients, doctor and schedule and saves them to the memory.
 */
void readAll();

/**
 * Save patients, discharged patients, doctor and schedule lists to the external files.
 */
void saveAll();

/**
 * Prints the patients, discharged patients, doctor and schedule lists
 */
void viewAll();

/*********Private Functions End**************/

#endif //MENU_H
