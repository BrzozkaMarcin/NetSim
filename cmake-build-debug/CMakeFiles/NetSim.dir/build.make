# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Programy\CLion 2021.1.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Programy\CLion 2021.1.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Programowanie\NetSim

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Programowanie\NetSim\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/NetSim.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/NetSim.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/NetSim.dir/flags.make

CMakeFiles/NetSim.dir/main.cpp.obj: CMakeFiles/NetSim.dir/flags.make
CMakeFiles/NetSim.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Programowanie\NetSim\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/NetSim.dir/main.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\NetSim.dir\main.cpp.obj -c D:\Programowanie\NetSim\main.cpp

CMakeFiles/NetSim.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NetSim.dir/main.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Programowanie\NetSim\main.cpp > CMakeFiles\NetSim.dir\main.cpp.i

CMakeFiles/NetSim.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NetSim.dir/main.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Programowanie\NetSim\main.cpp -o CMakeFiles\NetSim.dir\main.cpp.s

# Object files for target NetSim
NetSim_OBJECTS = \
"CMakeFiles/NetSim.dir/main.cpp.obj"

# External object files for target NetSim
NetSim_EXTERNAL_OBJECTS =

NetSim.exe: CMakeFiles/NetSim.dir/main.cpp.obj
NetSim.exe: CMakeFiles/NetSim.dir/build.make
NetSim.exe: CMakeFiles/NetSim.dir/linklibs.rsp
NetSim.exe: CMakeFiles/NetSim.dir/objects1.rsp
NetSim.exe: CMakeFiles/NetSim.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Programowanie\NetSim\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable NetSim.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\NetSim.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/NetSim.dir/build: NetSim.exe

.PHONY : CMakeFiles/NetSim.dir/build

CMakeFiles/NetSim.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\NetSim.dir\cmake_clean.cmake
.PHONY : CMakeFiles/NetSim.dir/clean

CMakeFiles/NetSim.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Programowanie\NetSim D:\Programowanie\NetSim D:\Programowanie\NetSim\cmake-build-debug D:\Programowanie\NetSim\cmake-build-debug D:\Programowanie\NetSim\cmake-build-debug\CMakeFiles\NetSim.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NetSim.dir/depend

