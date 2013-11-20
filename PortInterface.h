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
#include "J_Skeleton.h"

/*--- Namespaces ---*/
using namespace std;

/*--- Constants ---*/
#define BIND_PORT "tcp://*:5555"
#define SUBSCRIBE_MESSAGE "__primesense__"
#define SUBSCRIBE_MESSAGE_LENGTH 14

class PortInterface {

private:

    /*--- context/socket ---*/
	zmq::context_t * context;
    zmq::socket_t * publisher;


public:

    PortInterface ();
   	void send_skeleton (J_Skeleton *skeleton);
};