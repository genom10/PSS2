# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\Docs_Saves\Git\PSS2\HW4\Passenger

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\Docs_Saves\Git\PSS2\HW4\Passenger\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Passenger.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Passenger.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Passenger.dir/flags.make

CMakeFiles/Passenger.dir/main.cpp.obj: CMakeFiles/Passenger.dir/flags.make
CMakeFiles/Passenger.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Docs_Saves\Git\PSS2\HW4\Passenger\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Passenger.dir/main.cpp.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Passenger.dir\main.cpp.obj -c E:\Docs_Saves\Git\PSS2\HW4\Passenger\main.cpp

CMakeFiles/Passenger.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Passenger.dir/main.cpp.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Docs_Saves\Git\PSS2\HW4\Passenger\main.cpp > CMakeFiles\Passenger.dir\main.cpp.i

CMakeFiles/Passenger.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Passenger.dir/main.cpp.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Docs_Saves\Git\PSS2\HW4\Passenger\main.cpp -o CMakeFiles\Passenger.dir\main.cpp.s

CMakeFiles/Passenger.dir/E_/Docs_Saves/Git/PSS2/HW4/includes/sqlite3.c.obj: CMakeFiles/Passenger.dir/flags.make
CMakeFiles/Passenger.dir/E_/Docs_Saves/Git/PSS2/HW4/includes/sqlite3.c.obj: E:/Docs_Saves/Git/PSS2/HW4/includes/sqlite3.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Docs_Saves\Git\PSS2\HW4\Passenger\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Passenger.dir/E_/Docs_Saves/Git/PSS2/HW4/includes/sqlite3.c.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Passenger.dir\E_\Docs_Saves\Git\PSS2\HW4\includes\sqlite3.c.obj   -c E:\Docs_Saves\Git\PSS2\HW4\includes\sqlite3.c

CMakeFiles/Passenger.dir/E_/Docs_Saves/Git/PSS2/HW4/includes/sqlite3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Passenger.dir/E_/Docs_Saves/Git/PSS2/HW4/includes/sqlite3.c.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E E:\Docs_Saves\Git\PSS2\HW4\includes\sqlite3.c > CMakeFiles\Passenger.dir\E_\Docs_Saves\Git\PSS2\HW4\includes\sqlite3.c.i

CMakeFiles/Passenger.dir/E_/Docs_Saves/Git/PSS2/HW4/includes/sqlite3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Passenger.dir/E_/Docs_Saves/Git/PSS2/HW4/includes/sqlite3.c.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S E:\Docs_Saves\Git\PSS2\HW4\includes\sqlite3.c -o CMakeFiles\Passenger.dir\E_\Docs_Saves\Git\PSS2\HW4\includes\sqlite3.c.s

# Object files for target Passenger
Passenger_OBJECTS = \
"CMakeFiles/Passenger.dir/main.cpp.obj" \
"CMakeFiles/Passenger.dir/E_/Docs_Saves/Git/PSS2/HW4/includes/sqlite3.c.obj"

# External object files for target Passenger
Passenger_EXTERNAL_OBJECTS =

Passenger.exe: CMakeFiles/Passenger.dir/main.cpp.obj
Passenger.exe: CMakeFiles/Passenger.dir/E_/Docs_Saves/Git/PSS2/HW4/includes/sqlite3.c.obj
Passenger.exe: CMakeFiles/Passenger.dir/build.make
Passenger.exe: CMakeFiles/Passenger.dir/linklibs.rsp
Passenger.exe: CMakeFiles/Passenger.dir/objects1.rsp
Passenger.exe: CMakeFiles/Passenger.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\Docs_Saves\Git\PSS2\HW4\Passenger\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Passenger.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Passenger.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Passenger.dir/build: Passenger.exe

.PHONY : CMakeFiles/Passenger.dir/build

CMakeFiles/Passenger.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Passenger.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Passenger.dir/clean

CMakeFiles/Passenger.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Docs_Saves\Git\PSS2\HW4\Passenger E:\Docs_Saves\Git\PSS2\HW4\Passenger E:\Docs_Saves\Git\PSS2\HW4\Passenger\cmake-build-debug E:\Docs_Saves\Git\PSS2\HW4\Passenger\cmake-build-debug E:\Docs_Saves\Git\PSS2\HW4\Passenger\cmake-build-debug\CMakeFiles\Passenger.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Passenger.dir/depend

