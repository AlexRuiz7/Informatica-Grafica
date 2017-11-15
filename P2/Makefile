# File Makefile

# Compiler flags
CFLAGS=    -g -DXWINDOWS -DSHM -I/usr/include -I.
CXXFLAGS=  -c -g -DXWINDOWS -DSHM -I/usr/include -I. -std=c++11

# Linker flags
LDFLAGS=  -lGLU -lGL -lglut

# Compiler
CC = g++

# Macros
SOURCES = src/practica2.cpp src/object3d.cpp src/objectply.cpp src/esfera.cpp \
src/file_ply_stl.cpp src/ply_loader.cpp src/objectrev.cpp
EXECUTABLE = practica2
FILES = $(subst src/,,$(SOURCES))
OBJECTS = $(FILES:.cpp=.o)

.PHONY: all clean

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
	rm -f $(EXECUTABLE)
	rm -f doc/html/*

# Clean and build project
remake: clean all

# Compress
tgz: superclean
	@echo "Compressing files..."
	tar -zcvf $(EXECUTABLE).tgz *

# Doxygen documentation generation
documentation:
	doxygen doc/doxys/Doxyfile
