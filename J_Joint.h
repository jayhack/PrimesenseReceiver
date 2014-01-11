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

/*--- my files ---*/
#include "parameters.h"


/* class: J_Joint
 * --------------
 * my personal implementation of nite::SkeletonJoint
 */
class J_Joint {
private:

	/*--- Position/orientation ---*/
	nite::Point3f 		rw_position;	/* "Real-world" position */
	nite::Point3f		p_position;		/* "Projective" position */
	nite::Quaternion 	orientation;	/* */

public:

	/*--- Constructors/Initialization/Destructor ---*/
	J_Joint ();
	J_Joint (J_Joint *joint);
	J_Joint (nite::Point3f _rw_position, nite::Point3f _p_position, nite::Quaternion _orientation);

	/*--- Getting json ---*/
	json::object get_json_representation ();


	/*--- Getters/Setters ---*/
	nite::Point3f 		getRWPosition 			();
	nite::Point3f		getPPosition 			();
	nite::Quaternion  	getOrientation 			();
	void				set 					(J_Joint *joint);
	void 				set 					(nite::SkeletonJoint joint, nite::UserTracker *user_tracker);
	void 				set 					(nite::Point3f _rw_position, nite::Point3f _p_position, nite::Quaternion _orientation);
	void 				setRWPosition 			(nite::Point3f _rw_position);
	void 				setPPosition 			(nite::Point3f _p_position);
	void 				setOrientation			(nite::Quaternion _orientation);
	int 				getPositionConfidence ();	

};



#endif //_J_JOINT_H