# Makefile
# Author: Wenyu
# Date: 03/18/2019
# Version: 1.0
# Env: Ubuntu 12.04 x86, gcc 4.6.3, SIGVerse 2.2.2
# Function:
#	v1.0 [03/18/2019]: create single so from multi source in different folder

#sigverse header
SIG_SRC = $(SIGVERSE_PATH)/include/sigverse

# local header
DIR_INC = ./include

# local build
DIR_OBJ = ./build

# local source
DIR_SRC = ./src

SRC = $(wildcard $(DIR_SRC)/*.cpp)
#OBJ = $(patsubst %.cpp,${DIR_OBJ}/%.so,$(notdir $(SRC)))
OBJ = $(DIR_OBJ)/mainController.so

all: $(OBJ)

#compile
$(OBJ): $(SRC)
#$(DIR_OBJ)/%.so: $(DIR_SRC)/%.cpp
	g++ -DCONTROLLER -DNDEBUG -DUSE_ODE -DdDOUBLE -I$(SIG_SRC) -I$(SIG_SRC)/comm/controller -I$(DIR_INC) -fPIC -shared -o $@ $^

clean:
	rm $(DIR_OBJ)/*.so