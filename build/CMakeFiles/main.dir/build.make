# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/nular/Documents/cs8/final_proj

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nular/Documents/cs8/final_proj/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main.cpp.o: /Users/nular/Documents/cs8/final_proj/main.cpp
CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nular/Documents/cs8/final_proj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/main.cpp.o -MF CMakeFiles/main.dir/main.cpp.o.d -o CMakeFiles/main.dir/main.cpp.o -c /Users/nular/Documents/cs8/final_proj/main.cpp

CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nular/Documents/cs8/final_proj/main.cpp > CMakeFiles/main.dir/main.cpp.i

CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nular/Documents/cs8/final_proj/main.cpp -o CMakeFiles/main.dir/main.cpp.s

CMakeFiles/main.dir/includes/parser/parser.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/parser/parser.cpp.o: /Users/nular/Documents/cs8/final_proj/includes/parser/parser.cpp
CMakeFiles/main.dir/includes/parser/parser.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nular/Documents/cs8/final_proj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/includes/parser/parser.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/parser/parser.cpp.o -MF CMakeFiles/main.dir/includes/parser/parser.cpp.o.d -o CMakeFiles/main.dir/includes/parser/parser.cpp.o -c /Users/nular/Documents/cs8/final_proj/includes/parser/parser.cpp

CMakeFiles/main.dir/includes/parser/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/parser/parser.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nular/Documents/cs8/final_proj/includes/parser/parser.cpp > CMakeFiles/main.dir/includes/parser/parser.cpp.i

CMakeFiles/main.dir/includes/parser/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/parser/parser.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nular/Documents/cs8/final_proj/includes/parser/parser.cpp -o CMakeFiles/main.dir/includes/parser/parser.cpp.s

CMakeFiles/main.dir/includes/shuntingyard/shuntingyard.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/shuntingyard/shuntingyard.cpp.o: /Users/nular/Documents/cs8/final_proj/includes/shuntingyard/shuntingyard.cpp
CMakeFiles/main.dir/includes/shuntingyard/shuntingyard.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nular/Documents/cs8/final_proj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/includes/shuntingyard/shuntingyard.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/shuntingyard/shuntingyard.cpp.o -MF CMakeFiles/main.dir/includes/shuntingyard/shuntingyard.cpp.o.d -o CMakeFiles/main.dir/includes/shuntingyard/shuntingyard.cpp.o -c /Users/nular/Documents/cs8/final_proj/includes/shuntingyard/shuntingyard.cpp

CMakeFiles/main.dir/includes/shuntingyard/shuntingyard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/shuntingyard/shuntingyard.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nular/Documents/cs8/final_proj/includes/shuntingyard/shuntingyard.cpp > CMakeFiles/main.dir/includes/shuntingyard/shuntingyard.cpp.i

CMakeFiles/main.dir/includes/shuntingyard/shuntingyard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/shuntingyard/shuntingyard.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nular/Documents/cs8/final_proj/includes/shuntingyard/shuntingyard.cpp -o CMakeFiles/main.dir/includes/shuntingyard/shuntingyard.cpp.s

CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.o: /Users/nular/Documents/cs8/final_proj/includes/tokenizer/state_machine_functions.cpp
CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nular/Documents/cs8/final_proj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.o -MF CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.o.d -o CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.o -c /Users/nular/Documents/cs8/final_proj/includes/tokenizer/state_machine_functions.cpp

CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nular/Documents/cs8/final_proj/includes/tokenizer/state_machine_functions.cpp > CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.i

CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nular/Documents/cs8/final_proj/includes/tokenizer/state_machine_functions.cpp -o CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.s

CMakeFiles/main.dir/includes/tokenizer/stktoken.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/tokenizer/stktoken.cpp.o: /Users/nular/Documents/cs8/final_proj/includes/tokenizer/stktoken.cpp
CMakeFiles/main.dir/includes/tokenizer/stktoken.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nular/Documents/cs8/final_proj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/main.dir/includes/tokenizer/stktoken.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/tokenizer/stktoken.cpp.o -MF CMakeFiles/main.dir/includes/tokenizer/stktoken.cpp.o.d -o CMakeFiles/main.dir/includes/tokenizer/stktoken.cpp.o -c /Users/nular/Documents/cs8/final_proj/includes/tokenizer/stktoken.cpp

CMakeFiles/main.dir/includes/tokenizer/stktoken.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/tokenizer/stktoken.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nular/Documents/cs8/final_proj/includes/tokenizer/stktoken.cpp > CMakeFiles/main.dir/includes/tokenizer/stktoken.cpp.i

CMakeFiles/main.dir/includes/tokenizer/stktoken.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/tokenizer/stktoken.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nular/Documents/cs8/final_proj/includes/tokenizer/stktoken.cpp -o CMakeFiles/main.dir/includes/tokenizer/stktoken.cpp.s

CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o: /Users/nular/Documents/cs8/final_proj/includes/tokenizer/stokenize.cpp
CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nular/Documents/cs8/final_proj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o -MF CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o.d -o CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o -c /Users/nular/Documents/cs8/final_proj/includes/tokenizer/stokenize.cpp

CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nular/Documents/cs8/final_proj/includes/tokenizer/stokenize.cpp > CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.i

CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nular/Documents/cs8/final_proj/includes/tokenizer/stokenize.cpp -o CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.o" \
"CMakeFiles/main.dir/includes/parser/parser.cpp.o" \
"CMakeFiles/main.dir/includes/shuntingyard/shuntingyard.cpp.o" \
"CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.o" \
"CMakeFiles/main.dir/includes/tokenizer/stktoken.cpp.o" \
"CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

bin/main: CMakeFiles/main.dir/main.cpp.o
bin/main: CMakeFiles/main.dir/includes/parser/parser.cpp.o
bin/main: CMakeFiles/main.dir/includes/shuntingyard/shuntingyard.cpp.o
bin/main: CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.o
bin/main: CMakeFiles/main.dir/includes/tokenizer/stktoken.cpp.o
bin/main: CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o
bin/main: CMakeFiles/main.dir/build.make
bin/main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/nular/Documents/cs8/final_proj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable bin/main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: bin/main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /Users/nular/Documents/cs8/final_proj/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nular/Documents/cs8/final_proj /Users/nular/Documents/cs8/final_proj /Users/nular/Documents/cs8/final_proj/build /Users/nular/Documents/cs8/final_proj/build /Users/nular/Documents/cs8/final_proj/build/CMakeFiles/main.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/main.dir/depend

