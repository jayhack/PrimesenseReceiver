//
//  Weather update server in C++
//  Binds PUB socket to tcp://*:5556
//  Publishes random weather updates
//
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*--- ZeroMQ ---*/
#include <zmq.hpp>

/*--- cpp_json ---*/
#include "cpp_json/json.h"

/*--- My Files ---*/
#include "PortInterface.h"
#include "J_Skeleton.h"

/*--- Namespaces ---*/
using namespace std;

/* Function: constructor
 * ---------------------
 * sets up everything necessary for send_message to be called 
 */
PortInterface::PortInterface () {

    /*### Step 1: initialize context/socket, bind to port ###*/
    context = new zmq::context_t (1);
    publisher = new zmq::socket_t (*context, ZMQ_PUB);
    publisher->bind(BIND_PORT);
}


/* Function: skeleton_to_message_string
 * ------------------------------------
 * given a skeleton, returns a serialized version of it
 * via json.
 */
string skeleton_to_string (J_Skeleton * skeleton) {

    json::object json_skeleton = skeleton->get_json_representation ();
    string message_string = string (SUBSCRIBE_MESSAGE) + string (" ") + json::serialize(json_skeleton);
    return message_string;
}



/* Function: send_skeleton
 * -----------------------
 * given a J_Skeleton, sends it out as a message
 */
void PortInterface::send_skeleton (J_Skeleton * skeleton) {

    /*### Step 1: get a string representation of the skeleton ###*/
    string message_string = skeleton_to_string (skeleton);

    /*### Step 2: get a zmq message out of it ###*/
    zmq::message_t message (message_string.size());
    sprintf((char *) message.data(), "%s", message_string.c_str());

    /*### Step 3: send the actual message ###*/
    publisher->send(message);
}