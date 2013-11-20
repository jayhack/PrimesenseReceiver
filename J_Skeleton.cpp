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
	beat 			= false;
	pop 			= false;
	is_valid		= false;
	timestamp 		= -1;
				
	/*### Step 2: initialize joints ###*/
	for (int i=0;i<JSKEL_NUM_OF_JOINTS;i++) {
		J_Joint * joint = new J_Joint (nite::Point3f (0, 0, 0), nite::Point3f(0, 0, 0), nite::Quaternion (0, 0, 0, 0));
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
		
		/*--- get position, position_absolute and orientation  ---*/
		nite::SkeletonJoint current_joint = skeleton->getJoint ((nite::JointType) i);
		nite::Point3f position = current_joint.getPosition ();
		nite::Point3f position_absolute = nite::Point3f (0, 0, 0);
		user_tracker->convertJointCoordinatesToDepth (position.x, position.y, position.z, &position_absolute.x, &position_absolute.y);
		nite::Quaternion orientation = current_joint.getOrientation ();

		/*--- set the joint's properties ---*/
		joints[i]->set (position, position_absolute, orientation);

	}

	/*### Step 3: compute higher-level properties ###*/
	compute_higher_level_properties ();
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
		
		/*### Step 3: compute higher-level properties ###*/
		compute_higher_level_properties ();

		return;
	}
}
	
/* Constructor: json::value
 * ------------------------
 * creates a skeleton from a json::value
 */
J_Skeleton::J_Skeleton (json::value json_representation) {

	/*### Step 1: initialize joints ###*/
	initialize ();
	is_valid = true;		

	/*### Step 2: joint objects ###*/
	json::value json_joints = json_representation["joints"];
	for (int i=0;i<JSKEL_NUM_OF_JOINTS;i++) {
		stringstream index;
		index << i;

		json::value json_current_joint = json_joints[index.str().c_str()];
		joints[i]->set (json_current_joint);
	}

	/*### Step 3: higher-level properties ###*/
	json::value json_beat = json_representation["beat"];
	setBeat(json::to_number(json_beat) == 1);
	json::value json_pop = json_representation["pop"];
	setPop(json::to_number(json_pop) == 1);

	/*### Step 3: compute higher-level properties ###*/
	compute_higher_level_properties ();
}


/* Function: destructor
 * --------------------
 * only has to delete the joints, so far
 */
J_Skeleton::~J_Skeleton () {

	/*### Step 1: delete all memory allocated to the joints ###*/
	for (int i = 0;i<JSKEL_NUM_OF_JOINTS;i++) {
		delete joints[i];
	}
}




/*########################################################################################################################*/
/*###############################[--- Computing Higher-Level Properties ---]##############################################*/
/*########################################################################################################################*/
/* Function: compute_higher_level_properties
 * -----------------------------------------
 * computes the following properties:
 * - bounding box
 * - center of mass 
 */
void J_Skeleton::compute_higher_level_properties () {

	get_bounding_box ();
	get_center_of_mass ();
}


/* Function: get_bounding_box
 * --------------------------
 * returns the convex hull (bounding box) of the current skeleton
 */
nite::BoundingBox J_Skeleton::get_bounding_box () {

	nite::Point3f top_left, bottom_right;

	top_left.x 		= 1000000;
	top_left.y 		= 1000000;
	bottom_right.x 	= 0;
	bottom_right.y	= 0;

	for (int i=0;i<JSKEL_NUM_OF_JOINTS;i++) {

		nite::Point3f position_absolute = joints[i]->getPositionAbsolute ();

		if (position_absolute.x < top_left.x) 		top_left.x = position_absolute.x;
		if (position_absolute.y < top_left.y) 		top_left.y = position_absolute.y;
		if (position_absolute.x > bottom_right.x) 	bottom_right.x = position_absolute.x;
		if (position_absolute.y > bottom_right.y) 	bottom_right.y = position_absolute.y;			

	}
	return nite::BoundingBox (top_left, bottom_right);
}



/* Function: get_center_of_mass 
 * ----------------------------
 * computes the center of mass, stores it in the instance variable center_of_mass,
 * then returns it. (this is in relative coordinates, all that we really need)
 */
nite::Point3f J_Skeleton::get_center_of_mass () {

	float x_total = 0;
	float y_total = 0;
	float z_total = 0;
	for (int i=0;i<JSKEL_NUM_OF_JOINTS;i++) {
		nite::Point3f position =  joints[i]->getPosition ();
		x_total += position.x;
		y_total += position.y;
		z_total += position.z;
	}
	float x_avg = x_total / float(JSKEL_NUM_OF_JOINTS);
	float y_avg = y_total / float(JSKEL_NUM_OF_JOINTS);
	float z_avg = z_total / float(JSKEL_NUM_OF_JOINTS);

	center_of_mass = nite::Point3f (x_avg, y_avg, z_avg);
	return center_of_mass;
}




/*########################################################################################################################*/
/*###############################[--- JSON Representation ---]############################################################*/
/*########################################################################################################################*/
void put_in_json (json::object &object, const char *key, float value) {
	if (isnan(value)) value = 10000;
	object.insert(key, value);
}

/* Function: get_json_representation
 * ---------------------------------
 * returns a string representation of this skeleton in json
 */
json::object J_Skeleton::get_json_representation () {

	json::object json_skel;
	stringstream dump_stream;

	/*### Step 1: center of mass ###*/
	json::object json_center_of_mass;
	put_in_json (json_center_of_mass, "x", center_of_mass.x);
	put_in_json (json_center_of_mass, "y", center_of_mass.y);
	put_in_json (json_center_of_mass, "z", center_of_mass.z);		
	json_skel.insert ("center_of_mass", json_center_of_mass);


	/*### Step 2: bounding box ###*/
	json::object json_bounding_box;
	json::object min;
	json::object max;
	put_in_json (min, "x", bounding_box.min.x);
	put_in_json (min, "y", bounding_box.min.y);	
	put_in_json (max, "x", bounding_box.max.x);
	put_in_json (max, "y", bounding_box.max.y);			
	json_bounding_box.insert ("min", min);
	json_bounding_box.insert ("max", max);
	json_skel.insert ("bounding_box", json_bounding_box);


	/*### Step 3: joints ###*/
	json::object json_joints;
	for (int i=0;i<JSKEL_NUM_OF_JOINTS;i++) {

		/*--- get the json rep of the joint ---*/
		J_Joint * current_joint = joints[i];
		json::object json_current_joint = current_joint->get_json_representation ();

		/*--- insert it along with the correct index ---*/
		stringstream index;
		index << i;
		json_joints.insert (index.str().c_str(), json_current_joint); 
	}
	json_skel.insert ("joints", json_joints);

	return json_skel;
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

/* Setter/Getter: beat
 * ----------------------------
 * gets/sets the beat
 */
bool J_Skeleton::getBeat () {
 	return beat;
}
void J_Skeleton::setBeat (bool beat_value) {
 	beat = beat_value;
}	

/* Setter/Getter: pop
 * ------------------
 * gets/sets the beat
 */
bool J_Skeleton::getPop () {
 	return pop;
}
void J_Skeleton::setPop(bool pop_value) {
 	pop = pop_value;
}	


/* Setter/Getter: get/setJoint
 * ---------------------------
 * gets/sets a particular joint
 */
J_Joint *J_Skeleton::getJoint (nite::JointType joint_type) {
	return joints [(int) joint_type];
}
void J_Skeleton::setJoint (nite::JointType joint_type, nite::Point3f position, nite::Point3f position_absolute, nite::Quaternion orientation) {
	joints [(int) joint_type]->set (position, position_absolute, orientation);
}















