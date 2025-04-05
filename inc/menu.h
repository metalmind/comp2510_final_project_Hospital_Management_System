/**
 * Menu handles all the functionality regarding the printing the menu to screen
 * and routing the selection to the correct function.
 *
 * @author Owen Wou
 * @version February 2025
 */
#ifndef MENU_H
#define MENU_H

#define EXIT 0
#define ADD_PATIENT_RECORDS 1
#define VIEW_ALL_PATIENTS 2
#define SEARCH_PATIENT 3
#define DISCHARGE_PATIENT 4
#define DOCTOR_MENU 5
#define SAVE_ALL_PATIENT_RECORDS 6
#define LOAD_PATIENT_RECORDS 7
#define SCHEDULE_MENU 6
#define GENERATE_REPORT 7
#define SAVE_LOAD_DATA 8

#define SAVE_ALL_PATIENT_RECORDS 1
#define LOAD_PATIENT_RECORDS 2

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

void saveMenu(void);
/*********Public Functions End**************/

/*********Private Functions Begin************/
/**
 * Helper function to print the menu options to the screen.
 */
void printMenu(void);

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
 * Selection:
 *    1. Add Patient Record
 *    2. View All Patients
 *    3. Search Patient by ID
 *    4. Discharge Patient
 *    5. Manage Doctor Schedule
 *    6. Exit
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
/*********Private Functions End**************/

#endif //MENU_H
