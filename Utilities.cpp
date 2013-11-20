#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "Utilities.h"

using namespace std; 


/* Function: print_error
 * ---------------------
 * takes in two strings and prints them to output in an error message, 
 * then stop program operation by asserting false.
 */
void print_error (const char* top_string, const char* bottom_string) {
	
	cout << "	Error: " << top_string << endl << "	--------------------" << endl << "	" << bottom_string << endl;
}


/* Function: print_status
 * ----------------------
 * prints out a status line
 */
void print_status (const char* stage_name, const char* status_message) {
	cout << "	-----> " << stage_name << ": " << status_message << endl;
	return;
}

