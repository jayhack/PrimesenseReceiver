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
#include "parameters.h"
#include "PortInterface.h"
#include "J_Skeleton.h"
#include "J_Frame.h"

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


/* Function: frame_to_string
 * -------------------------
 * given a frame, returns a json string representation of it
 */
string frame_to_string (J_Frame * frame) {

    /*### Step 1: extract skeleton (fill with empty skeleton if none present) ###*/
    std::vector<J_Skeleton *> *skeletons = frame->get_skeletons ();
    if (skeletons != NULL) {
        for (int i=0;i<skeletons->size();i++) {
            
            J_Skeleton* skeleton = skeletons->at(i);
            json::object json_skeleton = skeleton->get_json_representation ();
            cout << json::pretty_print (json_skeleton) << "\n\n";
            
        }
    }
    // json::object json_skeleton = skeleton->get_json_representation ();
    // cout << json::pretty_print (json_skeleton) << "\n\n";
    // string message_string = string (SUBSCRIBE_MESSAGE) + string (" ") + json::serialize(json_skeleton);
    string a;
    return a;
}


/* Function: send_frame
 * --------------------
 * given a frame, sends it out as a message
 */
void PortInterface::send_frame (J_Frame * frame) {

    /*=====[ Get string representation (print it) ]=====*/
    string message_string = frame_to_string (frame);

    /*=====[ Convert to zmq message ]=====*/
    zmq::message_t message (message_string.size());
    sprintf((char *) message.data(), "%s", message_string.c_str());


    /*=====[ Send zqm message ]=====*/
    publisher->send(message);
}