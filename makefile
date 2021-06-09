# compiler
GXX := g++

# compiler flags
GXXFLAGS :=

# target executable
TARGET := MAIN.out

# header files
INCLUDES := -I src/include

# source files
SOURCES := src/lib/generate_task_set.cpp src/lib/dbf_star_algorithm.cpp src/lib/qpa_algorithm.cpp src/lib/io_functions.cpp src/lib/tests.cpp

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

build/dbf_star_algorithm.o: src/lib/dbf_star_algorithm.cpp
	mkdir -p $(dir $@)
	$(GXX) $(GXXFLAGS) $(INCLUDES) -c src/lib/dbf_star_algorithm.cpp -o $@

build/qpa_algorithm.o: src/lib/qpa_algorithm.cpp
	mkdir -p $(dir $@)
	$(GXX) $(GXXFLAGS) $(INCLUDES) -c src/lib/qpa_algorithm.cpp -o $@

build/io_functions.o: src/lib/io_functions.cpp
	mkdir -p $(dir $@)
	$(GXX) $(GXXFLAGS) $(INCLUDES) -c src/lib/io_functions.cpp -o $@

build/tests.o: src/lib/tests.cpp
	mkdir -p $(dir $@)
	$(GXX) $(GXXFLAGS) $(INCLUDES) -c src/lib/tests.cpp -o $@

clean:
	$(RM) -r build
	$(RM) $(TARGET)