/* ---------------------------------------------- 	*
 *	File: J_Skeleton.h
 *	--------------------
 *	My personal implementation of nite::Skeleton
 *
 *
 *	----------------------------------------------	*/
#ifndef _J_SKELETON_H
#define _J_SKELETON_H

/*--- Standard ---*/
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <sstream>

/*--- NiTE ---*/
#include "NiTE.h"

/*--- cpp_json ---*/
#include "cpp_json/json.h"

/*--- My Files ---*/
#include "parameters.h"
#include "J_Joint.h"

/*--- Namespaces ---*/
using namespace std;



/* Class: J_Skeleton
 * -----------------
 * my personal implementation of nite::Skeleton
 */
class J_Skeleton {

private:

	/*--- Timestamp/Name/Validity ---*/
	int 			timestamp; 	//the time at which this skeleton occurred, also
	string 			name;		//string representation of id, for writing/reading
	bool 			is_valid;

	/*--- Joints ---*/
	J_Joint *joints [15];

	/*--- Initialization ---*/
	void initialize ();


public:

	/*--- Constructors/Destructor ---*/
	J_Skeleton ();
	J_Skeleton (J_Joint new_joints[JSKEL_NUM_OF_JOINTS], int new_timestamp);
	J_Skeleton (std::map<nite::JointType, J_Joint> new_joints, int new_timestamp);
	J_Skeleton (nite::Skeleton *skeleton, nite::UserTracker *user_tracker);
	J_Skeleton (J_Skeleton *skeleton);
	~J_Skeleton ();

	/*--- Computing Properties ---*/
	void 				compute_higher_level_properties ();
	nite::BoundingBox 	get_bounding_box ();
	nite::Point3f 		get_center_of_mass ();

	/*--- Json representation ---*/
	json::object get_json_representation ();

	/*--- Setters/Getters ---*/
	bool		isValid 			();
	void 		setValid 			(bool value);
	int 		getTimestamp		();
	void 		setTimestamp 		(int new_timestamp); 
	J_Joint *	getJoint 			(nite::JointType joint_type);
	void 		setJoint 			(nite::JointType joint_type, nite::Point3f new_position, nite::Point3f new_position_absolute, nite::Quaternion new_orientation);
	void 		setJointPosition	(nite::JointType joint_type, nite::Point3f new_position);
	void 		setJointOrientation	(nite::JointType joint_type, nite::Quaternion new_orientation);

};
#endif	//_J_SKELETON_H