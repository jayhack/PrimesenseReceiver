/* ---------------------------------------------- 	*
 *	File: J_Joint.h
 *	--------------------
 *	My personal implementation of nite::SkeletonJoint
 *	includes position (relative), orientation and position (absolute)
 * 	
 *
 *	----------------------------------------------	*/
#ifndef _J_JOINT_H
#define _J_JOINT_H

/*--- Standard ---*/
 #include <stdlib.h>
 #include <stdio.h>
 #include <vector>

/*--- NiTE ---*/
#include "NiTE.h"

/*--- cpp_json ---*/
#include "cpp_json/json.h"


/* class: J_Joint
 * --------------
 * my personal implementation of nite::SkeletonJoint
 */
class J_Joint {
private:

	/*--- Position/orientation ---*/
	nite::Point3f 		position;	
	nite::Point3f		position_absolute;
	nite::Quaternion 	orientation;

public:

	/*--- Constructors/Initialization/Destructor ---*/
	J_Joint ();
	J_Joint (J_Joint *joint);
	J_Joint (nite::Point3f new_position, nite::Point3f new_position_absolute, nite::Quaternion new_orientation);

	/*--- Getting json ---*/
	json::object get_json_representation ();


	/*--- Getters/Setters ---*/
	nite::Point3f 		getPosition 			();
	nite::Point3f		getPositionAbsolute 	();
	nite::Quaternion  	getOrientation 			();
	void				set 					(J_Joint *joint);
	void 				set 					(nite::SkeletonJoint joint, nite::UserTracker *user_tracker);
	void 				set 					(nite::Point3f new_position, nite::Point3f new_position_absolute, nite::Quaternion new_orientation);
	void 				set 					(json::value json_joint);
	void 				setPosition 			(nite::Point3f new_position);
	void 				setPositionAbsolute 	(nite::Point3f new_position_absolute);
	void 				setOrientation			(nite::Quaternion new_orientation);


	int 				getPositionConfidence ();	


};



#endif //_J_JOINT_H