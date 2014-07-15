CXX= g++
CXXCLANG= clang++33
CFLAGS= -Wextra -Werror -Wall -L/usr/lib/ -ltbb 
DIRTEST= check/
SRC= src/image.cc      \
     src/itr_sorter.cc \
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
	./$(BINGEN) 20 20
	imview img.ppm

check: generate
	imview final.ppm


clean:
	@rm -f ${DIRTEST}${BIN} ${BIN} ${BIN}.core ${OBJ} ${BINGEN}

.PHONY: check clean

