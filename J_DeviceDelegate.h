/* ---------------------------------------------- 	*
 *	File: J_DeviceDelegate.h
 *	--------------------------
 *	Class to take care of all interface with the device;
 *	you can poll it for a new J_Frame at any point with readFrame
 *
 *	----------------------------------------------	*/
 #ifndef _J_DEV_DELEGATE_
 #define _J_DEV_DELEGATE_

/*--- NiTE ---*/
#include <NiTE.h>

/*--- My Files ---*/
#include "J_Frame.h"



class J_DeviceDelegate {
private:

	openni::Device *device;
	nite::UserTracker* user_tracker;
	openni::VideoStream color_stream;

public:

	/*--- constructor ---*/
	J_DeviceDelegate ();
	~J_DeviceDelegate ();

	/*--- getting frames ---*/
	J_Frame * readFrame ();

};







#endif // _J_DEV_DELEGATE_