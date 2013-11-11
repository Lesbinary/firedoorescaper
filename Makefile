GCC=g++
CFLAGS=
INC_DIR=include/
LIB_DIR=lib/
MAINFILE=main
LIBS=-lFireDoorEscaper -lboost_random

all: $(MAINFILE) 

$(MAINFILE): $(MAINFILE).cpp
	$(GCC) $(CFLAGS) $(MAINFILE).cpp -o $(MAINFILE) -I$(INC_DIR) -L$(LIB_DIR) $(LIBS)
