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
#define SCHEDULE_MENU 6

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

/**
 * Helper function to print the menu options to the screen.
 */
void printMenu(void);

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

#endif //MENU_H
