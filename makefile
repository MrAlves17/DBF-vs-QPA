# compiler
GXX := g++

# compiler flags
GXXFLAGS :=

# target executable
TARGET := MAIN

# header files
INCLUDES := -I src/include

# source files
SOURCES := src/lib/generate_task_set.cpp src/lib/dbf_algorithm.cpp

# object files
# src/lib/ -> build/
OBJECTS := $(patsubst src/lib/%,build/%,$(SOURCES))
# .cpp -> .o
OBJECTS := $(patsubst %.cpp,%.o,$(OBJECTS))

all: $(TARGET)

$(TARGET): src/main.cpp $(OBJECTS) src/include/
	$(GXX) $(GXXFLAGS) $(INCLUDES) src/main.cpp -o $@ $(OBJECTS)

build/generate_task_set.o: src/lib/generate_task_set.cpp
	mkdir -p $(dir $@)
	$(GXX) $(GXXFLAGS) $(INCLUDES) -c src/lib/generate_task_set.cpp -o $@

build/dbf_algorithm.o: src/lib/dbf_algorithm.cpp
	mkdir -p $(dir $@)
	$(GXX) $(GXXFLAGS) $(INCLUDES) -c src/lib/dbf_algorithm.cpp -o $@

clean:
	$(RM) -r build
	$(RM) $(TARGET)