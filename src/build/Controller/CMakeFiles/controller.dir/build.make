# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build

# Include any dependencies generated for this target.
include Controller/CMakeFiles/controller.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Controller/CMakeFiles/controller.dir/compiler_depend.make

# Include the progress variables for this target.
include Controller/CMakeFiles/controller.dir/progress.make

# Include the compile flags for this target's objects.
include Controller/CMakeFiles/controller.dir/flags.make

Controller/CMakeFiles/controller.dir/tcp_client.c.o: Controller/CMakeFiles/controller.dir/flags.make
Controller/CMakeFiles/controller.dir/tcp_client.c.o: /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/Controller/tcp_client.c
Controller/CMakeFiles/controller.dir/tcp_client.c.o: Controller/CMakeFiles/controller.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object Controller/CMakeFiles/controller.dir/tcp_client.c.o"
	cd /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build/Controller && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Controller/CMakeFiles/controller.dir/tcp_client.c.o -MF CMakeFiles/controller.dir/tcp_client.c.o.d -o CMakeFiles/controller.dir/tcp_client.c.o -c /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/Controller/tcp_client.c

Controller/CMakeFiles/controller.dir/tcp_client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/controller.dir/tcp_client.c.i"
	cd /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build/Controller && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/Controller/tcp_client.c > CMakeFiles/controller.dir/tcp_client.c.i

Controller/CMakeFiles/controller.dir/tcp_client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/controller.dir/tcp_client.c.s"
	cd /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build/Controller && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/Controller/tcp_client.c -o CMakeFiles/controller.dir/tcp_client.c.s

Controller/CMakeFiles/controller.dir/tcp_server.c.o: Controller/CMakeFiles/controller.dir/flags.make
Controller/CMakeFiles/controller.dir/tcp_server.c.o: /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/Controller/tcp_server.c
Controller/CMakeFiles/controller.dir/tcp_server.c.o: Controller/CMakeFiles/controller.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object Controller/CMakeFiles/controller.dir/tcp_server.c.o"
	cd /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build/Controller && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Controller/CMakeFiles/controller.dir/tcp_server.c.o -MF CMakeFiles/controller.dir/tcp_server.c.o.d -o CMakeFiles/controller.dir/tcp_server.c.o -c /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/Controller/tcp_server.c

Controller/CMakeFiles/controller.dir/tcp_server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/controller.dir/tcp_server.c.i"
	cd /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build/Controller && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/Controller/tcp_server.c > CMakeFiles/controller.dir/tcp_server.c.i

Controller/CMakeFiles/controller.dir/tcp_server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/controller.dir/tcp_server.c.s"
	cd /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build/Controller && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/Controller/tcp_server.c -o CMakeFiles/controller.dir/tcp_server.c.s

Controller/CMakeFiles/controller.dir/handler_server.c.o: Controller/CMakeFiles/controller.dir/flags.make
Controller/CMakeFiles/controller.dir/handler_server.c.o: /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/Controller/handler_server.c
Controller/CMakeFiles/controller.dir/handler_server.c.o: Controller/CMakeFiles/controller.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object Controller/CMakeFiles/controller.dir/handler_server.c.o"
	cd /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build/Controller && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Controller/CMakeFiles/controller.dir/handler_server.c.o -MF CMakeFiles/controller.dir/handler_server.c.o.d -o CMakeFiles/controller.dir/handler_server.c.o -c /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/Controller/handler_server.c

Controller/CMakeFiles/controller.dir/handler_server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/controller.dir/handler_server.c.i"
	cd /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build/Controller && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/Controller/handler_server.c > CMakeFiles/controller.dir/handler_server.c.i

Controller/CMakeFiles/controller.dir/handler_server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/controller.dir/handler_server.c.s"
	cd /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build/Controller && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/Controller/handler_server.c -o CMakeFiles/controller.dir/handler_server.c.s

Controller/CMakeFiles/controller.dir/handler_client.c.o: Controller/CMakeFiles/controller.dir/flags.make
Controller/CMakeFiles/controller.dir/handler_client.c.o: /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/Controller/handler_client.c
Controller/CMakeFiles/controller.dir/handler_client.c.o: Controller/CMakeFiles/controller.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object Controller/CMakeFiles/controller.dir/handler_client.c.o"
	cd /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build/Controller && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Controller/CMakeFiles/controller.dir/handler_client.c.o -MF CMakeFiles/controller.dir/handler_client.c.o.d -o CMakeFiles/controller.dir/handler_client.c.o -c /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/Controller/handler_client.c

Controller/CMakeFiles/controller.dir/handler_client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/controller.dir/handler_client.c.i"
	cd /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build/Controller && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/Controller/handler_client.c > CMakeFiles/controller.dir/handler_client.c.i

Controller/CMakeFiles/controller.dir/handler_client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/controller.dir/handler_client.c.s"
	cd /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build/Controller && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/Controller/handler_client.c -o CMakeFiles/controller.dir/handler_client.c.s

# Object files for target controller
controller_OBJECTS = \
"CMakeFiles/controller.dir/tcp_client.c.o" \
"CMakeFiles/controller.dir/tcp_server.c.o" \
"CMakeFiles/controller.dir/handler_server.c.o" \
"CMakeFiles/controller.dir/handler_client.c.o"

# External object files for target controller
controller_EXTERNAL_OBJECTS =

Controller/libcontroller.a: Controller/CMakeFiles/controller.dir/tcp_client.c.o
Controller/libcontroller.a: Controller/CMakeFiles/controller.dir/tcp_server.c.o
Controller/libcontroller.a: Controller/CMakeFiles/controller.dir/handler_server.c.o
Controller/libcontroller.a: Controller/CMakeFiles/controller.dir/handler_client.c.o
Controller/libcontroller.a: Controller/CMakeFiles/controller.dir/build.make
Controller/libcontroller.a: Controller/CMakeFiles/controller.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C static library libcontroller.a"
	cd /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build/Controller && $(CMAKE_COMMAND) -P CMakeFiles/controller.dir/cmake_clean_target.cmake
	cd /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build/Controller && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/controller.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Controller/CMakeFiles/controller.dir/build: Controller/libcontroller.a
.PHONY : Controller/CMakeFiles/controller.dir/build

Controller/CMakeFiles/controller.dir/clean:
	cd /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build/Controller && $(CMAKE_COMMAND) -P CMakeFiles/controller.dir/cmake_clean.cmake
.PHONY : Controller/CMakeFiles/controller.dir/clean

Controller/CMakeFiles/controller.dir/depend:
	cd /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/Controller /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build/Controller /Users/axel/Desktop/Projets/Scolaire/Aquarium_Network/src/build/Controller/CMakeFiles/controller.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Controller/CMakeFiles/controller.dir/depend

