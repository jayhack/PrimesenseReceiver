/* ---------------------------------------------- 	*
 *	File: NI_app.h
 *	--------------
 *	an abstract class that both NI_Recorder and NI_Player
 *	inherit from. both of them contain:
 *	- J_StorageDelegate
 *	- J_Drawer
 *	- 
 *	----------------------------------------------	*/

#ifndef _NI_APP_H_
#define _NI_APP_H_

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
#include "NiTE.h"

/*--- My Files ---*/
#include "Utilities.h"
#include "J_DeviceDelegate.h"
#include "PortInterface.h"


/*--- Namespaces ---*/
using namespace std;



/*########################################################################################################################*/
/*###############################[--- NI_app CLASS DEF ---]#######################################################################*/
/*########################################################################################################################*/

class NI_App {
protected:

    /*--- Device Access ---*/
    J_DeviceDelegate * device_delegate;

    /*--- Port Communication ---*/
    PortInterface * port_interface;
    
	/*--- Initialization ---*/
    void initialize_openni  ();
    void initialize_nite    ();
	void initialize_APIs    ();

    

public:

	/*--- Constructor/Destructor ---*/
	NI_App ();
    ~NI_App ();

    /*--- Main Loop ---*/
    void main_loop ();
    
};


#endif // _NI_APP_H_
