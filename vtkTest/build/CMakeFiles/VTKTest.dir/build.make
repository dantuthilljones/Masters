# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/dan/Documents/cmake/cmake-3.9.4-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/dan/Documents/cmake/cmake-3.9.4-Linux-x86_64/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dan/Documents/Masters/vtkTest/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dan/Documents/Masters/vtkTest/build

# Include any dependencies generated for this target.
include CMakeFiles/VTKTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/VTKTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/VTKTest.dir/flags.make

CMakeFiles/VTKTest.dir/VTKTest.cpp.o: CMakeFiles/VTKTest.dir/flags.make
CMakeFiles/VTKTest.dir/VTKTest.cpp.o: /home/dan/Documents/Masters/vtkTest/src/VTKTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dan/Documents/Masters/vtkTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/VTKTest.dir/VTKTest.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/VTKTest.dir/VTKTest.cpp.o -c /home/dan/Documents/Masters/vtkTest/src/VTKTest.cpp

CMakeFiles/VTKTest.dir/VTKTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VTKTest.dir/VTKTest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dan/Documents/Masters/vtkTest/src/VTKTest.cpp > CMakeFiles/VTKTest.dir/VTKTest.cpp.i

CMakeFiles/VTKTest.dir/VTKTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VTKTest.dir/VTKTest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dan/Documents/Masters/vtkTest/src/VTKTest.cpp -o CMakeFiles/VTKTest.dir/VTKTest.cpp.s

CMakeFiles/VTKTest.dir/VTKTest.cpp.o.requires:

.PHONY : CMakeFiles/VTKTest.dir/VTKTest.cpp.o.requires

CMakeFiles/VTKTest.dir/VTKTest.cpp.o.provides: CMakeFiles/VTKTest.dir/VTKTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/VTKTest.dir/build.make CMakeFiles/VTKTest.dir/VTKTest.cpp.o.provides.build
.PHONY : CMakeFiles/VTKTest.dir/VTKTest.cpp.o.provides

CMakeFiles/VTKTest.dir/VTKTest.cpp.o.provides.build: CMakeFiles/VTKTest.dir/VTKTest.cpp.o


# Object files for target VTKTest
VTKTest_OBJECTS = \
"CMakeFiles/VTKTest.dir/VTKTest.cpp.o"

# External object files for target VTKTest
VTKTest_EXTERNAL_OBJECTS =

VTKTest: CMakeFiles/VTKTest.dir/VTKTest.cpp.o
VTKTest: CMakeFiles/VTKTest.dir/build.make
VTKTest: /usr/local/lib/libvtkInteractionStyle-8.0.so.1
VTKTest: /usr/local/lib/libvtkFiltersExtraction-8.0.so.1
VTKTest: /usr/local/lib/libvtkFiltersStatistics-8.0.so.1
VTKTest: /usr/local/lib/libvtkImagingFourier-8.0.so.1
VTKTest: /usr/local/lib/libvtkImagingCore-8.0.so.1
VTKTest: /usr/local/lib/libvtkalglib-8.0.so.1
VTKTest: /usr/local/lib/libvtkRenderingOpenGL2-8.0.so.1
VTKTest: /usr/local/lib/libvtkglew-8.0.so.1
VTKTest: /usr/local/lib/libvtkIOXML-8.0.so.1
VTKTest: /usr/local/lib/libvtkIOXMLParser-8.0.so.1
VTKTest: /usr/local/lib/libvtkexpat-8.0.so.1
VTKTest: /usr/local/lib/libvtkIOGeometry-8.0.so.1
VTKTest: /usr/local/lib/libvtkRenderingCore-8.0.so.1
VTKTest: /usr/local/lib/libvtkFiltersSources-8.0.so.1
VTKTest: /usr/local/lib/libvtkFiltersGeneral-8.0.so.1
VTKTest: /usr/local/lib/libvtkCommonComputationalGeometry-8.0.so.1
VTKTest: /usr/local/lib/libvtkCommonColor-8.0.so.1
VTKTest: /usr/local/lib/libvtkFiltersGeometry-8.0.so.1
VTKTest: /usr/local/lib/libvtkFiltersCore-8.0.so.1
VTKTest: /usr/lib/x86_64-linux-gnu/libSM.so
VTKTest: /usr/lib/x86_64-linux-gnu/libICE.so
VTKTest: /usr/lib/x86_64-linux-gnu/libX11.so
VTKTest: /usr/lib/x86_64-linux-gnu/libXext.so
VTKTest: /usr/lib/x86_64-linux-gnu/libXt.so
VTKTest: /usr/local/lib/libvtkIOLegacy-8.0.so.1
VTKTest: /usr/local/lib/libvtkIOCore-8.0.so.1
VTKTest: /usr/local/lib/libvtkCommonExecutionModel-8.0.so.1
VTKTest: /usr/local/lib/libvtkCommonDataModel-8.0.so.1
VTKTest: /usr/local/lib/libvtkCommonTransforms-8.0.so.1
VTKTest: /usr/local/lib/libvtkCommonMisc-8.0.so.1
VTKTest: /usr/local/lib/libvtkCommonMath-8.0.so.1
VTKTest: /usr/local/lib/libvtkCommonSystem-8.0.so.1
VTKTest: /usr/local/lib/libvtkCommonCore-8.0.so.1
VTKTest: /usr/local/lib/libvtksys-8.0.so.1
VTKTest: /usr/local/lib/libvtklz4-8.0.so.1
VTKTest: /usr/local/lib/libvtkzlib-8.0.so.1
VTKTest: CMakeFiles/VTKTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dan/Documents/Masters/vtkTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable VTKTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VTKTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/VTKTest.dir/build: VTKTest

.PHONY : CMakeFiles/VTKTest.dir/build

CMakeFiles/VTKTest.dir/requires: CMakeFiles/VTKTest.dir/VTKTest.cpp.o.requires

.PHONY : CMakeFiles/VTKTest.dir/requires

CMakeFiles/VTKTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/VTKTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/VTKTest.dir/clean

CMakeFiles/VTKTest.dir/depend:
	cd /home/dan/Documents/Masters/vtkTest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dan/Documents/Masters/vtkTest/src /home/dan/Documents/Masters/vtkTest/src /home/dan/Documents/Masters/vtkTest/build /home/dan/Documents/Masters/vtkTest/build /home/dan/Documents/Masters/vtkTest/build/CMakeFiles/VTKTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/VTKTest.dir/depend
