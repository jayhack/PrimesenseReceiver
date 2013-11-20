/* ---------------------------------------------- 	*
 *	File: J_Joint.cpp
 *	--------------------
 *	My personal implementation of nite::SkeletonJoint
 *
 *
 *	----------------------------------------------	*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

/*--- NiTE ---*/
#include "NiTE.h"

/*--- cpp_json ---*/
#include "cpp_json/json.h"

/*--- My Files ---*/
#include "J_Joint.h"



/*########################################################################################################################*/
/*###############################[--- Constructor/Destructors ---]########################################################*/
/*########################################################################################################################*/

/* Constructor: J_Joint (copy constructor) or nite::Point3f/float[3]/nite::Quaternion
 * -----------------------------------------------------------------------------------------
 * creates/initializes a J_Joint from an nite::SkeletonJoint
 * or, one or both of the position and orientation
 */
J_Joint::J_Joint () {
	setPosition 		(nite::Point3f(0, 0, 0));
	setPositionAbsolute (nite::Point3f(0, 0, 0));
	setOrientation 		(nite::Quaternion (0, 0, 0, 0));
}
J_Joint::J_Joint (J_Joint *joint) {
	set(joint);
}
J_Joint::J_Joint (nite::Point3f new_position, nite::Point3f new_position_absolute, nite::Quaternion new_orientation) {
	set(new_position, new_position_absolute, new_orientation);
}











/*########################################################################################################################*/
/*###############################[--- JSON Represenation ---]#############################################################*/
/*########################################################################################################################*/
void put_in_json_joint (json::object &object, const char *key, float value) {
	if (std::isnan(value)) value = 10000;
	object.insert(key, value);
}

/* Function: get_json_representation
 * ---------------------------------
 * returns a json object representing this joint
 */
json::object J_Joint::get_json_representation () {

	json::object json_position;
	put_in_json_joint (json_position, "x", position.x);
	put_in_json_joint (json_position, "y", position.y);
	put_in_json_joint (json_position, "z", position.z);		

	json::object json_position_absolute;
	put_in_json_joint (json_position_absolute, "x", position_absolute.x);
	put_in_json_joint (json_position_absolute, "y", position_absolute.y);
	put_in_json_joint (json_position_absolute, "z", position_absolute.z);

	json::object json_orientation;
	put_in_json_joint (json_orientation, "w", orientation.x);	
	put_in_json_joint (json_orientation, "x", orientation.x);
	put_in_json_joint (json_orientation, "y", orientation.y);
	put_in_json_joint (json_orientation, "z", orientation.z);

	json::object json_representation;
	json_representation.insert	("position", json_position);
	json_representation.insert 	("position_absolute", json_position_absolute);
	json_representation.insert 	("orientation", json_orientation);

	return json_representation;
}

















/*########################################################################################################################*/
/*###############################[--- Setters/Getters ---]################################################################*/
/*########################################################################################################################*/
/* Getter: getPositionConfidence
 * -----------------------------
 * not really implemented yet, just returns 1
 */
int J_Joint::getPositionConfidence () {

	return 1;
}


/* Position/Orientation getters
 * ---------------------------
 * gets/sets a particular joint's properties given either a nite::SkeletonJoint
 * or nite::Point3f and/or nite::Quaternion for position/orientation, respectively
 */
nite::Point3f J_Joint::getPosition () {
	return position;
}
nite::Point3f J_Joint::getPositionAbsolute () {
	return position_absolute;
}
nite::Quaternion J_Joint::getOrientation () {
	return orientation;
}


/* Setters
 * -------
 * takes in either a J_Joint, nite::Joint or nite::Point3f new_position and 
 * nite::Quaternion new_orientation
 */
void J_Joint::set (J_Joint *joint) {
	setPosition 		(joint->getPosition ());
	setPositionAbsolute (joint->getPositionAbsolute());
	setOrientation 		(joint->getOrientation());
}
void J_Joint::set (nite::Point3f new_position, nite::Point3f new_position_absolute, nite::Quaternion new_orientation) {
	setPosition 			(new_position);
	setPositionAbsolute		(new_position_absolute);
	setOrientation 			(new_orientation);
}
void J_Joint::set (json::value json_joint) {

	/*### position ###*/
	json::value json_position = json_joint["position"];
	position.x	= json::to_number (json_position["x"]);
	position.y	= json::to_number (json_position["y"]);
	position.z	= json::to_number (json_position["z"]);		

	/*### position absolute ###*/
	json::value json_position_absolute = json_joint["position_absolute"];
	position_absolute.x	= json::to_number (json_position_absolute["x"]);
	position_absolute.y	= json::to_number (json_position_absolute["y"]);
	position_absolute.z	= json::to_number (json_position_absolute["z"]);	

	/*### orientation ###*/
	json::value json_orientation = json_joint["orientation"];
	orientation.w	= json::to_number (json_orientation["w"]);	
	orientation.x	= json::to_number (json_orientation["x"]);
	orientation.y	= json::to_number (json_orientation["y"]);
	orientation.z	= json::to_number (json_orientation["z"]);

}
void J_Joint::setPosition (nite::Point3f new_position) {
	position = new_position;
}
void J_Joint::setPositionAbsolute (nite::Point3f new_position_absolute) {
	position_absolute = new_position_absolute;		
}
void J_Joint::setOrientation (nite::Quaternion new_orientation) {
	orientation = new_orientation;
}



















