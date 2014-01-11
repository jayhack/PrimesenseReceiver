/* ---------------------------------------------- 	*
 *	File: PortInterface
 *	-------------------
 *	Class to take care of all communication via ports
 *  
 *
 *	----------------------------------------------	*/

/*--- Standard ---*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*--- ZeroMQ ---*/
#include <zmq.hpp>

/*--- My Files ---*/
#include "parameters.h"
#include "J_Frame.h"

/*--- Namespaces ---*/
using namespace std;


class PortInterface {

private:

    /*--- context/socket ---*/
	zmq::context_t * context;
    zmq::socket_t * publisher;


public:

    PortInterface ();
   	void send_frame (J_Frame * frame);
};