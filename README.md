--------------------------------------------
PrimeSenseReceiver
------------------
Making skeleton data from primesense available
throughout your system via TCP ports
by Jay Hack, Fall 2013
--------------------------------------------

1: Description
==============

This program provides a utility for broadcasting 
skeleton data gathered by the primesense across your
system via TCP ports. I, for instance, read in the data
with python, shape it with pandas, then run inference 
and statistical analysis procedures on it in real time.

The body pose frames themselves are sent across TCP as 
JSON dictionaries.

This is written in C++ and uses the following libraries:
• OpenNI: communicates with the primesense
• NiTE: extracts body pose information out of point clouds
	gathered from primesense
• ZeroMQ: interface to TCP ports
• cpp_json: serializes skeleton data structures.


2: Setup/Installation
=====================

Set up development environment:
~$: source SetupDevEnvironment.sh

Compile:
~$: make

Make sure you can run it:
~$: chmod +x run.sh


3: Usage
========

Run the program:
~$: ./run.sh
