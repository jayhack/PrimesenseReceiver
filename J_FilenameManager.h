/* ---------------------------------------------- 	*
 *	File: J_FilenameManager.h
 *	-------------------------
 *	manages all filenames for a given recording given
 * 	only the location of the .sync file
 *
 *	----------------------------------------------	*/
#ifndef _J_FILE_MAN_H_
#define _J_FILE_MAN_H_ 


/*--- Standard ---*/
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <map>
#include <vector>

/*--- Constants ---*/
#define RAW 0
#define MARKED 1
#define SYNCED 2
#define SKEL_FILE 0
#define JVID_FILE 1
#define ONI_FILE 2

/*--- Namespaces ---*/
using namespace std;

class J_FilenameManager {
private:

	/*--- base ---*/
	string base_directory;

	/*--- raw ---*/
	string raw_directory;
	string raw_skel;
	string raw_oni;
	string raw_jvid;

	/*--- marked ---*/
	string marked_directory;
	string marked_skel;
	string marked_oni;
	string marked_jvid;

	/*--- synced ---*/
	string synced_directory;
	string synced_skel;
	string synced_oni;
	string synced_jvid;

	/*--- Container ---*/
	map<int, string> raw_map;
	map<int, string> marked_map;
	map<int, string> synced_map;
	map<int, map<int, string> > filenames;

public:

	/*--- Constructor ---*/
	J_FilenameManager	();
	J_FilenameManager 	(const char *base_directory_filepath);

	/*--- Getter ---*/
	const char *get_filename (int recording_stage, int file_type);

};

#endif //_J_FILE_MAN_H_