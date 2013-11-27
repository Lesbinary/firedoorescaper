GCC=g++
CFLAGS=
INC_DIR=include/
LIB_DIR=lib/ 
MAINFILE=main
OBJFILE=firebitch
LIBS=-lFireDoorEscaper -lboost_random -larmadillo
MORE_INCLUDES= KVMachine.cpp LRMachine.cpp 

all: $(MAINFILE) 

$(MAINFILE): $(MAINFILE).cpp
	$(GCC) $(CFLAGS) $(MAINFILE).cpp -o $(OBJFILE) -I $(INC_DIR) $(MORE_INCLUDES) -O2  -L$(LIB_DIR) $(LIBS)
