/* ---------------------------------------------- 	*
 *	File: J_DeviceDelegate.cpp
 *	--------------------------
 *	Class to take care of all interface with the device;
 *	you can poll it for a new J_Frame at any point with read_J_Frame
 *
 *	----------------------------------------------	*/
/*--- Standard ---*/
#include <stdlib.h>
#include <stdio.h>

/*--- NiTE ---*/
#include <NiTE.h>


/*--- My Files ---*/
#include "J_Frame.h"
#include "J_DeviceDelegate.h"



/*########################################################################################################################*/
/*###############################[--- Constructor/Initialization/Destructor ---] #########################################*/
/*########################################################################################################################*/
 /* Function: constructor
  * ---------------------
  * sets up the device and the user tracker
  */
J_DeviceDelegate::J_DeviceDelegate () {

	openni::Status rc;

 	/*### Step 1: allocate and open the device ###*/
	device = new openni::Device ();
	rc = device->open(openni::ANY_DEVICE);


	/*### Step 2: ensure that it was opened successfully ###*/
	if ( (rc != openni::STATUS_OK) || (!device->isValid ())) {
		print_error ("Failed to open device", openni::OpenNI::getExtendedError());
	}


	/*### Step 3: allocate and initialize the user tracker, make sure it was opened correctly ###*/
	user_tracker = new nite::UserTracker ();
	if (user_tracker->create(device) != nite::STATUS_OK) {
		print_error ("Could not create the user tracker", "Not sure what to do here...");
	}


	/*### Step 4: set up the color stream as well ###*/
	rc = color_stream.create(*device, openni::SENSOR_COLOR);
	if (rc == openni::STATUS_OK) {
		rc = color_stream.start();
		if (rc != openni::STATUS_OK) {
			print_error ("J_DeviceDelegate", "the color stream is not starting");
			color_stream.destroy();
		}
	}
	else {
		print_error ("J_DeviceDelegate", "Failed to find color stream");
	}
	if (!color_stream.isValid()) {
		print_error ("J_DeviceDelegate", "the color stream is invalid. shutting down");
		openni::OpenNI::shutdown();
	}


}


/* Function: destructor
 * --------------------
 * frees memory allocated for the user tracker and device
 */
J_DeviceDelegate::~J_DeviceDelegate () {
	delete device;
	delete user_tracker;
}



/*########################################################################################################################*/
/*###############################[--- Reading Frames ---] ################################################################*/
/*########################################################################################################################*/
/* Function: readFrame
 * -------------------
 * this functino will return a pointer to the next J_Frame;
 * note that it will allocate the memory for it, so it is up to the user
 * to free the memory allocated for the received J_Frame somewhere down the line.
 * NOTE: this will also store the *absolute* coordinates of the skeleton in it. 
 */
J_Frame * J_DeviceDelegate::readFrame () {

	/*--- temporary objects we will use ---*/
	nite::UserTrackerFrameRef userTrackerFrame;
	openni::VideoFrameRef ni_depthFrame;
	openni::VideoFrameRef ni_colorFrame;


	/*### Step 1: get the color frame ###*/
	if (!color_stream.isValid()) {
		print_error ("J_DeviceDelegate", "the color stream is invalid. shutting down");
		openni::OpenNI::shutdown();
	}
	color_stream.readFrame (&ni_colorFrame);
	if (!ni_colorFrame.isValid ()) {
		print_error ("could not get the color frame", "do something about it");
	}

	/*### Step 1: get a userTrackerFrame from user_tracker, depth frame ###*/
	nite::Status rc = user_tracker->readFrame(&userTrackerFrame);
	if (rc != nite::STATUS_OK) {
		print_error ("Display", "Could not get a next frame from user_tracker");
	}
	ni_depthFrame = userTrackerFrame.getDepthFrame();


	/*### Step 2: get a J_Skeleton out of it ###*/
	const nite::Array<nite::UserData>& users = userTrackerFrame.getUsers();
	J_Skeleton *skeleton = NULL;

	/*### --- Note: For now, only deal with a single skeleton ---###*/
	if (users.getSize() > 0) {

		const nite::UserData & user = users[0];
		if (user.isNew ()) {
			user_tracker->startSkeletonTracking(user.getId());
			user_tracker->startPoseDetection(user.getId(), nite::POSE_CROSSED_HANDS);
		}
		else if (!user.isLost()) {
			if (users[0].getSkeleton().getState() == nite::SKELETON_TRACKED) {

					nite::Skeleton nite_skeleton = users[0].getSkeleton ();
					skeleton = new J_Skeleton (&nite_skeleton, user_tracker);
					J_Joint *current_joint = skeleton->getJoint ((nite::JointType) 0);
			}
		}
	}
	else {
		skeleton = NULL;
	}


	/*### Step 4: create the actual frame ###*/
	J_VideoFrameRef *j_depth_frame = new J_VideoFrameRef (&ni_depthFrame);
	J_VideoFrameRef *j_color_frame = new J_VideoFrameRef (&ni_colorFrame);
	J_Frame * new_frame = new J_Frame (skeleton, j_depth_frame, j_color_frame);
	return new_frame;

}








