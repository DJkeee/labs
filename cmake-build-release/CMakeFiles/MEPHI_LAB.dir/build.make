# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/clion-2024.2.2/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /opt/clion-2024.2.2/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dmitry/CLionProjects/labs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dmitry/CLionProjects/labs/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/MEPHI_LAB.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MEPHI_LAB.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MEPHI_LAB.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MEPHI_LAB.dir/flags.make

CMakeFiles/MEPHI_LAB.dir/PointersTest/SmartPtrTest.cpp.o: CMakeFiles/MEPHI_LAB.dir/flags.make
CMakeFiles/MEPHI_LAB.dir/PointersTest/SmartPtrTest.cpp.o: /home/dmitry/CLionProjects/labs/PointersTest/SmartPtrTest.cpp
CMakeFiles/MEPHI_LAB.dir/PointersTest/SmartPtrTest.cpp.o: CMakeFiles/MEPHI_LAB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dmitry/CLionProjects/labs/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MEPHI_LAB.dir/PointersTest/SmartPtrTest.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MEPHI_LAB.dir/PointersTest/SmartPtrTest.cpp.o -MF CMakeFiles/MEPHI_LAB.dir/PointersTest/SmartPtrTest.cpp.o.d -o CMakeFiles/MEPHI_LAB.dir/PointersTest/SmartPtrTest.cpp.o -c /home/dmitry/CLionProjects/labs/PointersTest/SmartPtrTest.cpp

CMakeFiles/MEPHI_LAB.dir/PointersTest/SmartPtrTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MEPHI_LAB.dir/PointersTest/SmartPtrTest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/CLionProjects/labs/PointersTest/SmartPtrTest.cpp > CMakeFiles/MEPHI_LAB.dir/PointersTest/SmartPtrTest.cpp.i

CMakeFiles/MEPHI_LAB.dir/PointersTest/SmartPtrTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MEPHI_LAB.dir/PointersTest/SmartPtrTest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/CLionProjects/labs/PointersTest/SmartPtrTest.cpp -o CMakeFiles/MEPHI_LAB.dir/PointersTest/SmartPtrTest.cpp.s

# Object files for target MEPHI_LAB
MEPHI_LAB_OBJECTS = \
"CMakeFiles/MEPHI_LAB.dir/PointersTest/SmartPtrTest.cpp.o"

# External object files for target MEPHI_LAB
MEPHI_LAB_EXTERNAL_OBJECTS =

MEPHI_LAB: CMakeFiles/MEPHI_LAB.dir/PointersTest/SmartPtrTest.cpp.o
MEPHI_LAB: CMakeFiles/MEPHI_LAB.dir/build.make
MEPHI_LAB: CMakeFiles/MEPHI_LAB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/dmitry/CLionProjects/labs/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MEPHI_LAB"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MEPHI_LAB.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MEPHI_LAB.dir/build: MEPHI_LAB
.PHONY : CMakeFiles/MEPHI_LAB.dir/build

CMakeFiles/MEPHI_LAB.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MEPHI_LAB.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MEPHI_LAB.dir/clean

CMakeFiles/MEPHI_LAB.dir/depend:
	cd /home/dmitry/CLionProjects/labs/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dmitry/CLionProjects/labs /home/dmitry/CLionProjects/labs /home/dmitry/CLionProjects/labs/cmake-build-release /home/dmitry/CLionProjects/labs/cmake-build-release /home/dmitry/CLionProjects/labs/cmake-build-release/CMakeFiles/MEPHI_LAB.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/MEPHI_LAB.dir/depend

