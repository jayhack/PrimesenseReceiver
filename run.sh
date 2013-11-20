#!/bin/bash
# Jay Hack, jhack@stanford.edu
# Fall 2013
# Script: run.sh
# --------------
# runs the actual program

####################[ --- HELPER FUNCTIONS --- ]####################

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
		return
	else
		error_message "$1 does not exist" "run make in order to compile the program"
	fi
}



####################[ --- MAIN OPERATION --- ]####################
source SetupDevEnvironment.sh

cd Bin/x64-Release
require_file_exists "PrimesenseReceiver"
cd ..
./x64-Release/PrimesenseReceiver
cd ..


