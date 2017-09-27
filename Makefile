COMPILER = g++ -std=c++11 -Wall -g -O3
EXEC_PROG = app
BINARIES = $(EXEC_PROG)
LIBS = -lboost_system -lboost_filesystem -lboost_program_options

SOURCES := $(shell find -name '*.cpp')

OBJECTS = $(SOURCES:.cpp=.o)
all: $(EXEC_PROG)
	@echo Build Completed

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
