/* ---------------------------------------------- 	*
 *	File: J_Frame.h
 *	-----------------
 *	Class that contains everything for dealing with 
 * 	a single "frame" from a video, including a J_Skeleton
 *	and a VideoFrameRef
 *
 *	----------------------------------------------	*/
#ifndef _J_FRAME_H
#define _J_FRAME_H 

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
#include "J_VideoFrameRef.h"


class J_Frame {
private:

	/*--- Data ---*/
	J_Skeleton			* skeleton;
	J_VideoFrameRef 	* depth_frame;
	J_VideoFrameRef		* color_frame;

	/*--- State ---*/
	bool is_valid;

public:

	/*--- Constructors ---*/
	J_Frame ();
	J_Frame (J_Skeleton *new_skeleton, J_VideoFrameRef *new_depth_frame, J_VideoFrameRef *new_color_frame);

	/*--- Getters ---*/
	J_Skeleton 			*get_skeleton 		();
	J_VideoFrameRef 	*get_depth_frame 	();
	J_VideoFrameRef		*get_color_frame	();

	/*--- Misc ---*/
	bool isValid ();

	/*--- Debugging ---*/
	void print_data ();

};

















#endif //_J_FRAME_H