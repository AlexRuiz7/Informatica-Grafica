
# File Makefile

# Compiler flags
CFLAGS=    -g -DXWINDOWS -DSHM -I/usr/include -I.
CXXFLAGS=  -c -g -DXWINDOWS -DSHM -I/usr/include -I. -std=c++11

# Linker flags
LDFLAGS=  -lGLU -lGL -lglut -lX11 -lXmu

# Compiler
CC = g++

# Macros
SOURCES = brazo_robot.cpp cube.cpp dedo.cpp pinza.cpp brazo1.cpp brazo2.cpp robot.cpp
EXECUTABLE = Brazo_Robot
OBJECTS = $(SOURCES:.cpp=.o)

# Compilation
all: $(EXECUTABLE) clean

$(EXECUTABLE): $(OBJECTS)
		$(CC) $^ -o $@ $(LDFLAGS)

$(OBJECTS):
	@echo "Building project..."
	$(CC) $(CXXFLAGS) $(SOURCES)

# Utilities
# Remove object files
clean:
	@echo "Removing object files..."
	rm -f $(OBJECTS)

# Remove objects file and executable
superclean: clean
	@echo "Removing files..."
	rm $(EXECUTABLE)

# Clean and build project
remake: clean all

# Compress
tgz: superclean
	tar -zcvf $(EXECUTABLE).tgz *
