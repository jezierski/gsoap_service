# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jezierski/public_html/soap_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jezierski/public_html/soap_server

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running interactive CMake command-line interface..."
	/usr/bin/cmake -i .
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/jezierski/public_html/soap_server/CMakeFiles /home/jezierski/public_html/soap_server/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/jezierski/public_html/soap_server/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named build/homesys

# Build rule for target.
build/homesys: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 build/homesys
.PHONY : build/homesys

# fast build rule for target.
build/homesys/fast:
	$(MAKE) -f CMakeFiles/build/homesys.dir/build.make CMakeFiles/build/homesys.dir/build
.PHONY : build/homesys/fast

homesys/CSoapServer.o: homesys/CSoapServer.cpp.o
.PHONY : homesys/CSoapServer.o

# target to build an object file
homesys/CSoapServer.cpp.o:
	$(MAKE) -f CMakeFiles/build/homesys.dir/build.make CMakeFiles/build/homesys.dir/homesys/CSoapServer.cpp.o
.PHONY : homesys/CSoapServer.cpp.o

homesys/CSoapServer.i: homesys/CSoapServer.cpp.i
.PHONY : homesys/CSoapServer.i

# target to preprocess a source file
homesys/CSoapServer.cpp.i:
	$(MAKE) -f CMakeFiles/build/homesys.dir/build.make CMakeFiles/build/homesys.dir/homesys/CSoapServer.cpp.i
.PHONY : homesys/CSoapServer.cpp.i

homesys/CSoapServer.s: homesys/CSoapServer.cpp.s
.PHONY : homesys/CSoapServer.s

# target to generate assembly for a file
homesys/CSoapServer.cpp.s:
	$(MAKE) -f CMakeFiles/build/homesys.dir/build.make CMakeFiles/build/homesys.dir/homesys/CSoapServer.cpp.s
.PHONY : homesys/CSoapServer.cpp.s

homesys/homesys.o: homesys/homesys.cpp.o
.PHONY : homesys/homesys.o

# target to build an object file
homesys/homesys.cpp.o:
	$(MAKE) -f CMakeFiles/build/homesys.dir/build.make CMakeFiles/build/homesys.dir/homesys/homesys.cpp.o
.PHONY : homesys/homesys.cpp.o

homesys/homesys.i: homesys/homesys.cpp.i
.PHONY : homesys/homesys.i

# target to preprocess a source file
homesys/homesys.cpp.i:
	$(MAKE) -f CMakeFiles/build/homesys.dir/build.make CMakeFiles/build/homesys.dir/homesys/homesys.cpp.i
.PHONY : homesys/homesys.cpp.i

homesys/homesys.s: homesys/homesys.cpp.s
.PHONY : homesys/homesys.s

# target to generate assembly for a file
homesys/homesys.cpp.s:
	$(MAKE) -f CMakeFiles/build/homesys.dir/build.make CMakeFiles/build/homesys.dir/homesys/homesys.cpp.s
.PHONY : homesys/homesys.cpp.s

raspberry/CGPIOClass.o: raspberry/CGPIOClass.cpp.o
.PHONY : raspberry/CGPIOClass.o

# target to build an object file
raspberry/CGPIOClass.cpp.o:
	$(MAKE) -f CMakeFiles/build/homesys.dir/build.make CMakeFiles/build/homesys.dir/raspberry/CGPIOClass.cpp.o
.PHONY : raspberry/CGPIOClass.cpp.o

raspberry/CGPIOClass.i: raspberry/CGPIOClass.cpp.i
.PHONY : raspberry/CGPIOClass.i

# target to preprocess a source file
raspberry/CGPIOClass.cpp.i:
	$(MAKE) -f CMakeFiles/build/homesys.dir/build.make CMakeFiles/build/homesys.dir/raspberry/CGPIOClass.cpp.i
.PHONY : raspberry/CGPIOClass.cpp.i

raspberry/CGPIOClass.s: raspberry/CGPIOClass.cpp.s
.PHONY : raspberry/CGPIOClass.s

# target to generate assembly for a file
raspberry/CGPIOClass.cpp.s:
	$(MAKE) -f CMakeFiles/build/homesys.dir/build.make CMakeFiles/build/homesys.dir/raspberry/CGPIOClass.cpp.s
.PHONY : raspberry/CGPIOClass.cpp.s

webservice/soapC.o: webservice/soapC.cpp.o
.PHONY : webservice/soapC.o

# target to build an object file
webservice/soapC.cpp.o:
	$(MAKE) -f CMakeFiles/build/homesys.dir/build.make CMakeFiles/build/homesys.dir/webservice/soapC.cpp.o
.PHONY : webservice/soapC.cpp.o

webservice/soapC.i: webservice/soapC.cpp.i
.PHONY : webservice/soapC.i

# target to preprocess a source file
webservice/soapC.cpp.i:
	$(MAKE) -f CMakeFiles/build/homesys.dir/build.make CMakeFiles/build/homesys.dir/webservice/soapC.cpp.i
.PHONY : webservice/soapC.cpp.i

webservice/soapC.s: webservice/soapC.cpp.s
.PHONY : webservice/soapC.s

# target to generate assembly for a file
webservice/soapC.cpp.s:
	$(MAKE) -f CMakeFiles/build/homesys.dir/build.make CMakeFiles/build/homesys.dir/webservice/soapC.cpp.s
.PHONY : webservice/soapC.cpp.s

webservice/soaphomesysService.o: webservice/soaphomesysService.cpp.o
.PHONY : webservice/soaphomesysService.o

# target to build an object file
webservice/soaphomesysService.cpp.o:
	$(MAKE) -f CMakeFiles/build/homesys.dir/build.make CMakeFiles/build/homesys.dir/webservice/soaphomesysService.cpp.o
.PHONY : webservice/soaphomesysService.cpp.o

webservice/soaphomesysService.i: webservice/soaphomesysService.cpp.i
.PHONY : webservice/soaphomesysService.i

# target to preprocess a source file
webservice/soaphomesysService.cpp.i:
	$(MAKE) -f CMakeFiles/build/homesys.dir/build.make CMakeFiles/build/homesys.dir/webservice/soaphomesysService.cpp.i
.PHONY : webservice/soaphomesysService.cpp.i

webservice/soaphomesysService.s: webservice/soaphomesysService.cpp.s
.PHONY : webservice/soaphomesysService.s

# target to generate assembly for a file
webservice/soaphomesysService.cpp.s:
	$(MAKE) -f CMakeFiles/build/homesys.dir/build.make CMakeFiles/build/homesys.dir/webservice/soaphomesysService.cpp.s
.PHONY : webservice/soaphomesysService.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... build/homesys"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... homesys/CSoapServer.o"
	@echo "... homesys/CSoapServer.i"
	@echo "... homesys/CSoapServer.s"
	@echo "... homesys/homesys.o"
	@echo "... homesys/homesys.i"
	@echo "... homesys/homesys.s"
	@echo "... raspberry/CGPIOClass.o"
	@echo "... raspberry/CGPIOClass.i"
	@echo "... raspberry/CGPIOClass.s"
	@echo "... webservice/soapC.o"
	@echo "... webservice/soapC.i"
	@echo "... webservice/soapC.s"
	@echo "... webservice/soaphomesysService.o"
	@echo "... webservice/soaphomesysService.i"
	@echo "... webservice/soaphomesysService.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

