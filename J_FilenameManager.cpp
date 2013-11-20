/* ---------------------------------------------- 	*
 *	File: J_FilenameManager.cpp
 *	-------------------------
 *	manages all filenames for a given recording given
 * 	only the location of the .sync file
 *
 *	----------------------------------------------	*/
/*--- Standard ---*/
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <map>
#include <vector>

/*--- My Files ---*/
#include "J_FilenameManager.h"

/*--- Namespaces ---*/
using namespace std;




/* Function: Constructor
 * ---------------------
 * fills in all the appropriate filenames, fills the map
 */
J_FilenameManager::J_FilenameManager () {}
J_FilenameManager::J_FilenameManager (const char *filepath) {

	/*### Step 1: get base directory names ###*/
	base_directory.assign (filepath);
	raw_directory 		= base_directory + "/Raw/";
	marked_directory 	= base_directory + "/Marked/";
	synced_directory	= base_directory + "/Synced/";

	/*### Step 2: for each directory, assign names ###*/
	raw_skel 	= raw_directory + "skeleton.skel";
	raw_oni 	= raw_directory + "video.oni";
	raw_jvid	= raw_directory + "video.jvid"; 

	marked_skel = marked_directory + "skeleton.skel";
	marked_oni 	= marked_directory + "video.oni";
	marked_jvid	= marked_directory + "video.jvid"; 

	synced_skel = synced_directory + "skeleton.skel";
	synced_oni 	= synced_directory + "video.oni";
	synced_jvid	= synced_directory + "video.jvid"; 

	/*### Step 3: fill the subdir maps ###*/
	raw_map.insert (std::pair<int, string>(SKEL_FILE, raw_skel));
	raw_map.insert (std::pair<int, string>(JVID_FILE, raw_jvid));
	raw_map.insert (std::pair<int, string>(ONI_FILE, raw_oni));

	marked_map.insert (std::pair<int, string>(SKEL_FILE, marked_skel));
	marked_map.insert (std::pair<int, string>(JVID_FILE, marked_jvid));
	marked_map.insert (std::pair<int, string>(ONI_FILE, marked_oni));

	synced_map.insert (std::pair<int, string>(SKEL_FILE, synced_skel));
	synced_map.insert (std::pair<int, string>(JVID_FILE, synced_jvid));
	synced_map.insert (std::pair<int, string>(ONI_FILE, synced_oni));

	/*### Step 4: fill the filenames map ###*/
	filenames.insert(std::pair <int, map<int, string> > (RAW, raw_map));
	filenames.insert(std::pair <int, map<int, string> > (MARKED, marked_map));
	filenames.insert(std::pair <int, map<int, string> > (SYNCED, synced_map));		

	return;
}


/* Function: get_filename
 * ----------------------
 * given the recording stage and filetype, this returns the appropriate name
 */
const char* J_FilenameManager::get_filename (int recording_stage, int filetype) {
	string filename = filenames.at(recording_stage).at(filetype);
	return filename.c_str();
}
