GCC=g++
CFLAGS=
INC_DIR=include/
LIB_DIR=lib/
MAINFILE=main
LIBS=-lFireDoorEscaper -lboost_random
MORE_INCLUDES= KVMachine.cpp LRMachine.cpp 

all: $(MAINFILE) 

$(MAINFILE): $(MAINFILE).cpp
	$(GCC) $(CFLAGS) $(MAINFILE).cpp -o $(MAINFILE) -I $(INC_DIR) $(MORE_INCLUDES)  -L$(LIB_DIR) $(LIBS)
