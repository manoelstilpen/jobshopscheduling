ifndef VERBOSE
.SILENT:
endif

COMPILER = g++ -std=c++11 -Wall -g -O3 -Ofast
EXEC_PROG = app
BINARIES = $(EXEC_PROG)
LIBS = -lboost_system -lboost_filesystem -lboost_program_options

SOURCES := $(shell find -name '*.cpp')

OBJECTS = $(SOURCES:.cpp=.o)

all: message_compiling $(EXEC_PROG)
	@echo Done

%.o: %.cpp
	$(COMPILER) -c $(LIBS) -o $@ $< -w

$(EXEC_PROG): $(OBJECTS)
	$(COMPILER) -o $(EXEC_PROG) $(OBJECTS) $(LIBS)

# prevents make from getting confused
.PHONY : run
run:
	./$(EXEC_PROG)

.PHONY : clean 
clean:
	rm -rf $(EXEC_PROG) $(OBJECTS) *.txt

message_compiling:
	@echo Compiling ...
