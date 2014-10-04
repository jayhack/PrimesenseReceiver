include ./CommonDefs.mak

# BIN_DIR
# -------
# Bin directory (output directory)
BIN_DIR = Bin


# INC_DIRS: 
# ---------
# list of all additional include directories
INC_DIRS 	+= $(OPENNI2_INCLUDE) 					#OpenNI 
INC_DIRS 	+= $(NITE2_INCLUDE)						#NiTE
INC_DIRS 	+= /opt/local/include 					#Boost


# SRC_FILES:
# ----------
# list of all .cpp files to compile into the project
SRC_FILES = 	*.cpp 				
SRC_FILES += 	cpp_json/*.cpp 		


# LIB_DIRS:
# ---------
# List of additional library directories
LIB_DIRS += $(OPENNI2_REDIST)
LIB_DIRS += $(NITE2_REDIST64)
LIB_DIRS += /opt/local/lib 	# Boost
LIB_DIRS += /usr/local/lib 	# ZeroMQ


# USED_LIBS
# ---------
# list of libraries to link with
CFLAGS += -DMACOS
USED_LIBS += OpenNI2 NiTE2 
#--- for zeromq ---
USED_LIBS += zmq


# EXE_NAME:
# ---------
# name of the executable 
EXE_NAME = PrimesenseReceiver


# CFLAGS:
# -------
# additional flags for the compiler
CFLAGS += -Wall
CFLAGS += -DMACOS

include ./CommonCppMakefile
