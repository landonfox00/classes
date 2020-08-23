
TARGET = main
LIBS = -lm
HEADERS = 
SRCS = main.cc
OBJECTS := $(patsubst %.cc,%.o,$(SRCS))
CXX = g++
CXX_FLAGS = -Wall -std=c++11

.PHONY: default all clean

$(TARGET): $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $(OBJECTS) $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
