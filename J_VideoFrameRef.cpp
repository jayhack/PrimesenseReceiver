/* ---------------------------------------------- 	*
 *	File: J_VideoFrameRef.cpp
 *	-------------------------
 *	my own implementation of VideoFrameRef that is mutable
 * 	and that I will be able to write 
 *	----------------------------------------------	*/
/*--- Standard ---*/
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

/*--- NiTE ---*/
#include "NiTE.h"

/*--- My Files ---*/
#include "J_VideoFrameRef.h"

/*--- namespaces ---*/
using namespace std;


/*########################################################################################################################*/
/*###############################[--- Construction/Initialization/Destruction ---] #######################################*/
/*########################################################################################################################*/
/* Function: constructor
 * ---------------------
 * given a pointer to an openni::VideoFrameRef, the constructor will 
 * make a deep copy of it and store all information locally.
 */
J_VideoFrameRef::J_VideoFrameRef () {
	is_valid = false;
	data = NULL;
}
J_VideoFrameRef::J_VideoFrameRef (openni::VideoFrameRef *video_frame_ref) {

	/*### Step 1: get parameters ###*/
	resolution_x		= video_frame_ref->getVideoMode().getResolutionX ();
	resolution_y		= video_frame_ref->getVideoMode().getResolutionY ();	
	crop_origin_x 		= video_frame_ref->getCropOriginX ();
	crop_origin_y 		= video_frame_ref->getCropOriginY ();
	cropping_enabled	= video_frame_ref->getCroppingEnabled ();
	data_size			= video_frame_ref->getDataSize ();
	frame_index			= video_frame_ref->getFrameIndex ();
	height 				= video_frame_ref->getHeight ();
	width				= video_frame_ref->getWidth ();
	stride_in_bytes		= video_frame_ref->getStrideInBytes ();
	timestamp			= video_frame_ref->getTimestamp ();
	is_valid 			= video_frame_ref->isValid ();

	/*### Step 2: make a deep copy of the data itself ###*/
	data = new char [data_size];
	memcpy (data, video_frame_ref->getData (), data_size);
}
/* Function: destructor
 * --------------------
 * all this has to do is free the memory dedicated to storing the original frame
 */
J_VideoFrameRef::~J_VideoFrameRef () {
	delete data;
}


/*########################################################################################################################*/
/*###############################[--- Setting Parameters/Data ---] #######################################################*/
/*########################################################################################################################*/
void 				J_VideoFrameRef::setResolutionX (int value) {resolution_x = value;}
void 				J_VideoFrameRef::setResolutionY (int value) {resolution_y = value;}
void 				J_VideoFrameRef::setCropOriginX (int value) {crop_origin_x = value;}
void 				J_VideoFrameRef::setCropOriginY (int value) {crop_origin_y = value;}
void 				J_VideoFrameRef::setCroppingEnabled (bool value) {cropping_enabled = value; }
void				J_VideoFrameRef::setDataSize (int value) {data_size = value;}
void 				J_VideoFrameRef::setFrameIndex (int value) {frame_index = value;}
void 				J_VideoFrameRef::setHeight (int value) {height = value;}
void 				J_VideoFrameRef::setWidth (int value) {width = value;}
void 				J_VideoFrameRef::setStrideInBytes (int value) {stride_in_bytes = value;}
void				J_VideoFrameRef::setTimestamp (uint64_t value) {timestamp = value;}
void 				J_VideoFrameRef::setValid (bool value) {is_valid = value;}


/* Function: allocate_for_data
 * ---------------------------
 * This function will allocate memory for data
 */
void 				J_VideoFrameRef::allocate_for_data () {

	/*--- Free data if it was previously pointing to something ---*/
	if (data != NULL) {
		delete data;
	}
	data = new char [data_size];
}

/*########################################################################################################################*/
/*###############################[--- Getting Parameters/Data ---] #######################################################*/
/*########################################################################################################################*/
int 				J_VideoFrameRef::getResolutionX () 			{ 	return resolution_x; }
int 				J_VideoFrameRef::getResolutionY () 			{	return resolution_y; }
int 				J_VideoFrameRef::getCropOriginX () 			{ 	return crop_origin_x; }
int 				J_VideoFrameRef::getCropOriginY () 			{	return crop_origin_y; }
bool 				J_VideoFrameRef::getCroppingEnabled () 		{	return cropping_enabled; }
int 				J_VideoFrameRef::getDataSize () 			{ 	return data_size; }
int 				J_VideoFrameRef::getFrameIndex ()			{ 	return frame_index; }
int 				J_VideoFrameRef::getHeight ()				{ 	return height; }
int 				J_VideoFrameRef::getWidth ()				{ 	return width; }
int 				J_VideoFrameRef::getStrideInBytes ()		{ 	return stride_in_bytes; }
uint64_t 			J_VideoFrameRef::getTimestamp ()			{ 	return timestamp; }
bool 				J_VideoFrameRef::isValid ()					{ 	return is_valid; }


const char * 		J_VideoFrameRef::getData 	()				{ return data; }




