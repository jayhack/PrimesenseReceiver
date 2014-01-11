/* ---------------------------------------------- 	*
 *	File: NI_app.cpp
 *	--------------
 *	Class to take care of all interface to device
 *	and body.
 *
 *	----------------------------------------------	*/
#if (defined _WIN32)
#define PRIu64 "llu"
#else
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#endif

/*--- Standard ---*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <sstream>

/*--- NiTE ---*/
#include <NiTE.h>

/*--- My Files ---*/
#include "NI_App.h"

/*--- Namespaces ---*/
using namespace std;


/*########################################################################################################################*/
/*########################################[ --- INITIALIZATION/DESTRUCTION --- ]##########################################*/
/*########################################################################################################################*/
 
/* Function: initialize_openni
 * ----------------------------
 * intializes openni
 */
void NI_App::initialize_openni () {
    openni::Status rc = openni::OpenNI::initialize ();
    if (rc != openni::STATUS_OK) {
        print_error("Failed to initialize OpenNI", openni::OpenNI::getExtendedError());
    }
}


/* Function: initialize_nite
 * ---------------------------
 * intializes nite
 */
void NI_App::initialize_nite () {
    nite::Status rc = nite::NiTE::initialize();
    if (rc != nite::STATUS_OK) {
        print_error("Failed to initialize OpenNI", openni::OpenNI::getExtendedError());
    }
}


/* Function: initialize_APIs
 * -------------------------
 * initalizes OpenNI, NiTE and OpenGL
 */
void NI_App::initialize_APIs () {

	/*### Step 1: Initialize OpenNI ###*/
	print_status ("Initialize_APIs", "Initializing OpenNI");
    initialize_openni ();

	/*### Step 2: initialize NiTE ###*/
    print_status ("Initialize_APIs", "Initializing NiTE");
    initialize_nite();
}


/* Function: constructor 
 * ---------------------
 * - intializes APIs (OpenNI, NiTE)
 * - creates device delegate
 */
NI_App::NI_App () {

	/*### Step 1: initialize the APIs ###*/
    initialize_APIs ();

	/*### Step 2: initialize the device/user tracker ###*/
	print_status ("Initialization", "Creating Device Delegate");
	device_delegate = new J_DeviceDelegate ();

    /*### Step 3: initialize the port communication ###*/
    print_status ("Initialization", "Starting Port Communication");
    port_interface = new PortInterface ();

}


/* Function: Destructor
 * --------------------
 * stops recording and closes all files
 */
NI_App::~NI_App () {
    
	/*### Step 1: free all memory allocatd for the device delegate ###*/
	print_status ("Finalization", "Deleting device delegate");
	delete device_delegate;
}








/*########################################################################################################################*/
/*########################################[ --- MAIN LOOP --- ]###########################################################*/
/*########################################################################################################################*/

/* Function: main_loop
 * -------------------
 * retrieves frames from primesense,
 * sends them out
 */
void NI_App::main_loop () {
    
    while (true) {
        
        J_Frame *frame = device_delegate->readFrame ();
        port_interface->send_frame (frame);
        delete frame;
    }
}










