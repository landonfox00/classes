
TARGET = main
LIBS = -lm
HEADERS = binary_node.h binary_tree_interface.h binary_node_tree.h binary_search_tree.h not_found_exception.h precond_violated_exception.h
SRCS = main.cc
OBJECTS := $(patsubst %.cc,%.o,$(SRCS))
CXX = g++
CXX_FLAGS = -Wall -std=c++11

.PHONY: default all clean

all: depend $(TARGET)

depend: .depend
.depend: $(HEADERS)
	rm -f ./.depend
	$(CXX) $(CXX_FLAGS) -MM $^ > ./.depend;
include .depend

%.o: %.cc $(HEADERS)
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $(OBJECTS) $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f ./.depend
	-rm -f $(TARGET)
