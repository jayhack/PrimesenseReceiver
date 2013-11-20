/*******************************************************************************
*                                                                              *
*   PrimeSense NiTE 2.0 - User Viewer Sample                                   *
*   Copyright (C) 2012 PrimeSense Ltd.                                         *
*                                                                              *
*******************************************************************************/

/*--- Standard ---*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*--- My Files ---*/
#include "Utilities.h"
#include "NI_App.h"

/*--- Namespaces ---*/
using namespace std;


int main(int argc, char** argv)
{
    NI_App * ni_app = new NI_App ();
    ni_app->main_loop ();
    delete ni_app;
	return 0;
}







