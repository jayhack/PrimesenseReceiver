/* ---------------------------------------------- 	*
 *	File: J_Frame.cpp
 *	-----------------
 *	Class that contains everything for dealing with 
 * 	a single "frame" from a video, including a J_Skeleton
 *	and a VideoFrameRef
 *
 *	----------------------------------------------	*/


/*--- Standard ---*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>

/*--- NiTE ---*/
#include "NiTE.h"

/*--- My Files ---*/
#include "Utilities.h"
#include "J_Skeleton.h"
#include "J_Frame.h"

 /*--- Namespaces ---*/
 using namespace std;
 using namespace openni;


/*########################################################################################################################*/
/*###############################[--- Constructor/Initialization/Destructor ---] #########################################*/
/*########################################################################################################################*/
/* Function : Default Constructor 
 * ---------------------
 * initializes the skeleton/frame_ref to null and is_valid to false.
 */
J_Frame::J_Frame () { 
	is_valid = false;
	skeletons = NULL;  //will be a pointer to a vector
	depth_frame = NULL;
	color_frame = NULL;
}

/* Function: Constructor
 * ---------------------
 * given a pointer to a filled-out skeleton and a filled-out frame_ref,
 * this function will make a new J_Frame from it.
 */
J_Frame::J_Frame (std::vector<J_Skeleton *> *new_skeletons, J_VideoFrameRef *new_depth_frame, J_VideoFrameRef *new_color_frame) {
	skeletons = new_skeletons;
	depth_frame = new_depth_frame;
	color_frame = new_color_frame;
	is_valid = true;
}

/* Function: isValid
 * -----------------
 * returns true if this J_Frame contains actual data
 */
bool J_Frame::isValid () {
	return is_valid;
}


/*########################################################################################################################*/
/*###############################[--- Getters ---] #######################################################################*/
/*########################################################################################################################*/
std::vector<J_Skeleton *> * J_Frame::get_skeletons 	() {
	return skeletons;
}

J_VideoFrameRef * J_Frame::get_depth_frame 	() {
	return depth_frame;
}

J_VideoFrameRef * J_Frame::get_color_frame	() {
	return color_frame;
}



/*########################################################################################################################*/
/*###############################[--- INTERFACE ---] #####################################################################*/
/*########################################################################################################################*/

/* Function: print_data
 * --------------------
 * prints out data on the frame
 */
void J_Frame::print_data () {

	cout << "=====[ FRAME: " << " ]=====" << endl;
	if (skeletons->size() > 0) {
		cout << "	NO USERS DETECTED" << endl;
	}
	else {
		cout << "	USER DETECTED " << endl;
	}
}










