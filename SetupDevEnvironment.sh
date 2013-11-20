#!/bin/bash
# Jay Hack, jhack@stanford.edu
# Fall 2013
# Script: SetupDevEnvironment.sh
# ------------------------------
# script to setup the dev environment so that you can run 'make'
# 
# ===[ SETUP ]===
# make sure that OpenNI2 and NiTE2 are one level above, named OpenNI2 and NiTE2,
# respectively.

####################[ --- HELPER FUNCTIONS --- ]####################

# Function: status_message
# ------------------------
# Parameters (2): stage, status
# Description: out the status in the form "---> state: status"
function status_message {
	
	echo "---> $1: $2"
}

# Function: error_message
# -----------------------
# Parameters (2): top line, bottom line
# Description: prints out top line/bottom line as an error message,
# 	then exits
function error_message {

	echo 'ERROR: ' $1
	echo '--------'
	echo $2
	exit 
}


# Function: require_file_exists
# ---------------------
# Parameters (1): filename
# Description: prints out debug info; exits if file doesnt exist.
function require_file_exists {
	if [ -f $1 ]; then 
		echo "	-->  $1 exists"
	else
		error_message "$1 does not exist" "find it and put it in this directory"
	fi
}

# Function: require_directory_exists
# ----------------------------------
# Parameters (1): directory name
# Description: prints out debug info; exits if directory doesn't exist
function require_directory_exists {
	if [ -d $1 ]; then 
		echo "	-->  $1 exists"
	else
		error_message "$1 does not exist" "locate $1 and put it in parent directory of PrimeSenseReceiver"
	fi
}


# Function: check_internal_structure
# ----------------------------------
# Parameters (1):
#	- directory name
# Description:
#	makes sure that the directory passed in has Include/Redist 
# 	subdirectories.
function check_internal_structure {
	cd $1
	require_directory_exists "Include"
	require_directory_exists "Redist"
	cd ..
}

####################[ --- MAIN OPERATION --- ]####################
ORIGINAL_DIR=`pwd`


### --- directory names --- ###
OPENNI2_DIRECTORY_NAME="OpenNI2"
NITE2_DIRECTORY_NAME="NiTE2"

### Step 1: make sure that OpenNI2 and NiTE2 both exist ###
cd ..
status_message "Initial Checks" "Checking for OpenNI2"
require_directory_exists $OPENNI2_DIRECTORY_NAME
check_internal_structure $OPENNI2_DIRECTORY_NAME

status_message "Initial Checks" "Checking for NiTE2"
require_directory_exists $NITE2_DIRECTORY_NAME
check_internal_structure $NITE2_DIRECTORY_NAME


### Step 2: Environmental Variables ###
status_message "Setting Environmental Variables" "OpenNI2"
cd $OPENNI2_DIRECTORY_NAME
export OPENNI2_LOCATION=`pwd`
export OPENNI2_INCLUDE=`pwd`/Include
export OPENNI2_REDIST=`pwd`/Redist
cd ..
status_message "Setting Environmental Variables" "NiTE2"
cd $NITE2_DIRECTORY_NAME
export NITE2_LOCATION=`pwd`
export NITE2_INCLUDE=`pwd`/Include
export NITE2_REDIST=`pwd`/Redist
cd ..

cd $ORIGINAL_DIR






