/* ---------------------------------------------- 	*
 *	File: J_Skeleton.cpp
 *	--------------------
 *	My personal implementation of nite::Skeleton
 *
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
#include <cmath>
#include <float.h>

/*--- NiTE ---*/
#include "NiTE.h"

/*--- cpp_json ---*/
#include "cpp_json/json.h"

/*--- My Files ---*/
#include "J_Skeleton.h"

/*--- Namespaces ---*/
using namespace std;




/*########################################################################################################################*/
/*###############################[--- Constructor/Destructors ---]########################################################*/
/*########################################################################################################################*/

/* Function: initialize_joints
 * ---------------------------
 * initializes joints (without a value) 
 */
void J_Skeleton::initialize () {

	/*### Step 1: initialize timestamp, pop, is_valid ###*/
	is_valid		= false;
	timestamp 		= -1;
				
	/*### Step 2: initialize joints to minimum float value ###*/
	float f = FLT_MIN;
	for (int i=0;i<JSKEL_NUM_OF_JOINTS;i++) {
		J_Joint * joint = new J_Joint (nite::Point3f (f, f, f), nite::Point3f(f, f, f), nite::Quaternion (f, f, f, f));
		joints[i] = joint;
	}

}

/* Constructor: 
 * -----------------------------------------------
 * initializes via a map from nite::JoinType to J_Joints
 */
J_Skeleton::J_Skeleton () {

	/*### Step 1: initialize joints ###*/
	initialize ();

}


/* Constructor: nite::Skeleton*, nite::UserTracker*
 * ---------------------------------
 * initializes via a reference to an nite::Skeleton
 * users the UserTracker so that it can get absolute coordinates.
 */
J_Skeleton::J_Skeleton (nite::Skeleton *skeleton, nite::UserTracker *user_tracker) {

	/*### Step 1: initialize skeleton ###*/
	initialize ();
	is_valid = true;

	/*### Step 2: set joint positions/orientations ###*/
	for (unsigned int i=0; i<JSKEL_NUM_OF_JOINTS;i++) {
		
		/*--- initialize fields ---*/
		nite::Point3f position;
		nite::Point3f position_absolute 	= nite::Point3f (0, 0, 0);
		nite::Quaternion orientation;

		/*--- fill them ---*/
		nite::SkeletonJoint current_joint = skeleton->getJoint ((nite::JointType) i);
		position = current_joint.getPosition ();
		user_tracker->convertJointCoordinatesToDepth (position.x, position.y, position.z, &position_absolute.x, &position_absolute.y);
		position_absolute.z = position.z; //note: z stays the same in 'projective' system
		orientation = current_joint.getOrientation ();

		/*--- set the joint ---*/
		joints[i]->set (position, position_absolute, orientation);

	}

	return;
}

/* Constructor: J_Skeleton *skeleton
 * ---------------------------------
 * initializes via a reference to a J_Skeleton (essentially a copy constructor)
 * if the skeleton passed in is null, this skeleton is set as not valid.
 */
J_Skeleton::J_Skeleton (J_Skeleton *skeleton) {

	/*### Step 1: initialize joints ###*/
	initialize ();

	if (skeleton == NULL) {
		is_valid = false;
		return;
	}
	else {

		/*### Step 1: initialize joints ###*/
		initialize ();
		is_valid = true;		

		/*### Step 2: set joint positions/orientations ###*/
		for (unsigned int i=0; i<JSKEL_NUM_OF_JOINTS;i++) {
			J_Joint *current_joint = skeleton->getJoint ((nite::JointType) i);
			joints[i]->set (current_joint);
		}
		return;
	}
}


/* Function: Destructor
 * --------------------
 * deletes joints
 */
J_Skeleton::~J_Skeleton () {

	/*### Step 1: delete all memory allocated to the joints ###*/
	for (int i = 0;i<JSKEL_NUM_OF_JOINTS;i++) {
		delete joints[i];
	}
}



/*########################################################################################################################*/
/*###############################[--- JSON Representation ---]############################################################*/
/*########################################################################################################################*/

/* Function: get_joint_label
 * -------------------------
 * given an index, this returns a c string that can serve
 * as a label for it
 */
const char * get_joint_label (int joint_index) {
	stringstream joint_label;
	joint_label << JOINT_KEY_BASE << joint_index;
	return joint_label.str().c_str ();
}


/* Function: get_json_representation
 * ---------------------------------
 * returns a string representation of this skeleton in json
 */
json::object J_Skeleton::get_json_representation () {

	json::object json_rep;
	for (int joint_index=0;joint_index<JSKEL_NUM_OF_JOINTS;joint_index++) {

		json::object 	joint_json_rep 	= joints[joint_index]->get_json_representation ();
		const char * 	joint_label 	= get_joint_label (joint_index);

		json_rep.insert (joint_label, joint_json_rep);

	}
	return json_rep;
}




/*########################################################################################################################*/
/*###############################[--- Setters/Getters ---]################################################################*/
/*########################################################################################################################*/
/* Setter/Getter: validity
 * -----------------------
 * sets this skeleton as valid or otherwise
 */
void J_Skeleton::setValid (bool value) {
	is_valid = value;
}
bool J_Skeleton::isValid () {
	return is_valid;
}


/* Setter/Getter: get/set index
 * ----------------------------
 * gets/sets the timestamp
 */
 int J_Skeleton::getTimestamp () {
 	return timestamp;
 }
 void J_Skeleton::setTimestamp (int new_timestamp) {
 	timestamp = new_timestamp;
 }	


/* Setter/Getter: get/setJoint
 * ---------------------------
 * gets/sets a particular joint
 */
J_Joint * J_Skeleton::getJoint (nite::JointType joint_type) {
	return joints [(int) joint_type];
}
void J_Skeleton::setJoint (nite::JointType joint_type, nite::Point3f position, nite::Point3f position_absolute, nite::Quaternion orientation) {
	joints [(int) joint_type]->set (position, position_absolute, orientation);
}














