CPP = g++
CPPFLAGS += -std=c++20 -Wall -g

SRC = $(shell find . -name '*.cpp')
 
OBJ = $(SRC:.cpp=.o)

EXE = main 

$(EXE): $(OBJ)
	$(CPP) $(CPPFLAGS) -o main $(OBJ) 

clean:
	rm -f $(OBJ) main