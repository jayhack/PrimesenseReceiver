/* ---------------------------------------------- 	*
 *	File: Parameters
 *	----------------
 *	Contains all parameters that are variable as 
 *  constants
 *	----------------------------------------------	*/
#include <cfloat>


/*### json_utils ###*/
#define JSON_NAN_SUBSTITUTE FLT_MIN

/*### PortInterface ###*/
#define BIND_PORT "tcp://*:5555"
#define SUBSCRIBE_MESSAGE "__primesense__"
#define SUBSCRIBE_MESSAGE_LENGTH 14

/*### J_Skeleton ###*/
#define JSKEL_NUM_OF_JOINTS 15
#define JOINT_KEY_BASE "JOINT_"

/*### J_Joint ###*/
#define REAL_WORLD_POSITION_KEY "REAL_WORLD_POSITION"
#define PROJECTIVE_POSITION_KEY "PROJECTIVE_POSITION"
#define ORIENTATION_KEY "ORIENTATION"
