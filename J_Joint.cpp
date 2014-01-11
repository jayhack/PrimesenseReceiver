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
#include "json_utils.h"
#include "J_Joint.h"




/*########################################################################################################################*/
/*###############################[--- Constructor/Destructors ---]########################################################*/
/*########################################################################################################################*/

/* Constructor: J_Joint (copy constructor) or nite::Point3f/float[3]/nite::Quaternion
 * ----------------------------------------------------------------------------------
 * creates/initializes a J_Joint from an nite::SkeletonJoint
 * or, one or both of the position and orientation
 * default values for joint are FLT_MIN (from <cfloat>)
 */
J_Joint::J_Joint () {
	float f = nan ("");
	setRWPosition 	(nite::Point3f(f, f, f));
	setPPosition	(nite::Point3f(f, f, f));
	setOrientation 	(nite::Quaternion (f, f, f, f));
}
J_Joint::J_Joint (J_Joint *joint) {
	set(joint);
}
J_Joint::J_Joint (nite::Point3f _rw_position, nite::Point3f _p_position, nite::Quaternion _orientation) {
	set(_rw_position, _p_position, _orientation);
}













/*########################################################################################################################*/
/*###############################[--- JSON ---]###########################################################################*/
/*########################################################################################################################*/


/* Function: get_json_representation
 * ---------------------------------
 * returns a json object representing this joint
 */
json::object J_Joint::get_json_representation () {

	json::object json_rw_position;
	put_in_json (json_rw_position, "x", rw_position.x);
	put_in_json (json_rw_position, "y", rw_position.y);
	put_in_json (json_rw_position, "z", rw_position.z);		

	json::object json_p_position;
	put_in_json (json_p_position, "x", p_position.x);
	put_in_json (json_p_position, "y", p_position.y);
	put_in_json (json_p_position, "z", p_position.z);

	json::object json_orientation;
	put_in_json (json_orientation, "w", orientation.x);	
	put_in_json (json_orientation, "x", orientation.x);
	put_in_json (json_orientation, "y", orientation.y);
	put_in_json (json_orientation, "z", orientation.z);

	json::object json_representation;
	json_representation.insert	(REAL_WORLD_POSITION_KEY, json_rw_position);
	json_representation.insert 	(PROJECTIVE_POSITION_KEY, json_p_position);
	json_representation.insert 	(ORIENTATION_KEY, json_orientation);

	return json_representation;
}

















/*########################################################################################################################*/
/*###############################[--- Setters/Getters ---]################################################################*/
/*########################################################################################################################*/

/* Getters
 * -------
 * getters for (rw|p)_position, orientation
 */
nite::Point3f J_Joint::getRWPosition () {
	return rw_position;
}
nite::Point3f J_Joint::getPPosition () {
	return p_position;
}
nite::Quaternion J_Joint::getOrientation () {
	return orientation;
}


/* Setters
 * -------
 * setters for joints
 */
void J_Joint::set (J_Joint *joint) {
	setRWPosition 		(joint->getRWPosition ());
	setPPosition		(joint->getPPosition());
	setOrientation 		(joint->getOrientation());
}
void J_Joint::set (nite::Point3f _rw_position, nite::Point3f _p_position, nite::Quaternion _orientation) {
	setRWPosition 			(_rw_position);
	setPPosition			(_p_position);
	setOrientation 			(_orientation);
}
void J_Joint::setRWPosition (nite::Point3f _rw_position) {
	rw_position = _rw_position;
}
void J_Joint::setPPosition (nite::Point3f _p_position) {
	p_position = _p_position;
}
void J_Joint::setOrientation (nite::Quaternion _orientation) {
	orientation = _orientation;
}


/* Function: getPositionConfidence
 * -------------------------------
 * Baseline implementation; feigns full confidence in joint
 * location.
 */
int J_Joint::getPositionConfidence () {
	return 1;
}


















