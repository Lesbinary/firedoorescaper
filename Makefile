GCC=g++
CFLAGS=
INC_DIR=include/
LIB_DIR=lib/ 
MAINFILE=main
OBJFILE=firebitch
LIBS=-lFireDoorEscaper -lboost_random -larmadillo -lCGAL
SVMKernels= SVMachine/LinearKernel.cpp SVMachine/PolynomialKernel.cpp SVMachine/RBFKernel.cpp
MORE_INCLUDES= KVMachine.cpp LRMachine.cpp NNMachine.cpp SVMachine/SVMachine.cpp

all: $(MAINFILE) 

$(MAINFILE): $(MAINFILE).cpp
	$(GCC) $(CFLAGS) $(MAINFILE).cpp -o $(OBJFILE) -I $(INC_DIR) $(MORE_INCLUDES) $(SVMKernels) -L$(LIB_DIR) $(LIBS) -frounding-math -fopenmp
