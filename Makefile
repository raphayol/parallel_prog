CXX= g++
CXXCLANG= clang++33
CFLAGS= -Wextra -Werror -Wall -pedantic -g3
DIRTEST= check/
SRC= src/image.cc     \
     src/itr_sorter.cc\
     src/para_sorter.cc\
     src/main.cc

OBJ=$(SRC:.cc=.o)
BIN= out

SGENSRC= generator/main.cc 

OBJGEN=$(SGENSRC:.cc=.o)
BINGEN=gen

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CFLAGS) -o $(BIN) $(SRC)

generate: 
	$(CXX) $(CFLAGS) -o $(BINGEN) $(SGENSRC)
	./$(BINGEN)
	imview img.ppm

clean:
	@rm -f ${DIRTEST}${BIN} ${BIN} ${BIN}.core ${OBJ} ${BINGEN}

.PHONY: check clean

