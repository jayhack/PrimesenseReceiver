/* ---------------------------------------------- 	*
 *	File: J_VideoFrameRef.h
 *	-------------------------
 *	my own implementation of VideoFrameRef that is mutable
 * 	and that I will be able to write 
 *	----------------------------------------------	*/
#ifndef _J_VID_REF_H_
#define _J_VID_REF_H_

/*--- Standard ---*/
#include <stdlib.h>
#include <stdio.h>

/*--- NiTE ---*/
#include "NiTE.h"


class J_VideoFrameRef {
private:

	/*--- parameters ---*/
	int resolution_x;
	int resolution_y;
	int crop_origin_x;
	int crop_origin_y;
	bool cropping_enabled;
	int data_size;
	int frame_index;
	int height, width;
	int stride_in_bytes;
	uint64_t timestamp;
	bool is_valid;


	/*--- data ---*/
	char *data;


public:

	/*--- Constructors ---*/
	J_VideoFrameRef ();
	J_VideoFrameRef (openni::VideoFrameRef *video_frame_ref);
	~J_VideoFrameRef ();

	/*--- Getting Data ---*/
	const char *		getData ();

	/*--- Getting/Setting Paramters ---*/
	void 						allocate_for_data ();

	void 						setResolutionX (int value);
	void 						setResolutionY (int value);
	void 						setCropOriginX (int value);
	void 						setCropOriginY (int value);
	void 						setCroppingEnabled (bool value);
	void						setDataSize (int value); 
	void 						setFrameIndex (int value);
	void 						setHeight (int value);
	void 						setWidth (int value);
	void 						setStrideInBytes (int value);
	void						setTimestamp (uint64_t value);
	void 						setValid (bool value);

	int 						getResolutionX ();
	int 						getResolutionY ();
	int 						getCropOriginX ();
	int 						getCropOriginY ();
	bool 						getCroppingEnabled ();
	int 						getDataSize (); 
	int 						getFrameIndex ();
	int 						getHeight ();
	int 						getWidth ();
	int 						getStrideInBytes ();
	uint64_t 					getTimestamp ();
	bool 						isValid ();


};

#endif