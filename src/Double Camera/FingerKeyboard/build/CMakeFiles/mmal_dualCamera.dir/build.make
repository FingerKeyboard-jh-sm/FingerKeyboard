# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/pi/src/FUCKYOU

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/src/FUCKYOU/build

# Include any dependencies generated for this target.
include CMakeFiles/mmal_dualCamera.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mmal_dualCamera.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mmal_dualCamera.dir/flags.make

CMakeFiles/mmal_dualCamera.dir/Main.cpp.o: CMakeFiles/mmal_dualCamera.dir/flags.make
CMakeFiles/mmal_dualCamera.dir/Main.cpp.o: ../Main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/src/FUCKYOU/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mmal_dualCamera.dir/Main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mmal_dualCamera.dir/Main.cpp.o -c /home/pi/src/FUCKYOU/Main.cpp

CMakeFiles/mmal_dualCamera.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mmal_dualCamera.dir/Main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/src/FUCKYOU/Main.cpp > CMakeFiles/mmal_dualCamera.dir/Main.cpp.i

CMakeFiles/mmal_dualCamera.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mmal_dualCamera.dir/Main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/src/FUCKYOU/Main.cpp -o CMakeFiles/mmal_dualCamera.dir/Main.cpp.s

CMakeFiles/mmal_dualCamera.dir/Main.cpp.o.requires:
.PHONY : CMakeFiles/mmal_dualCamera.dir/Main.cpp.o.requires

CMakeFiles/mmal_dualCamera.dir/Main.cpp.o.provides: CMakeFiles/mmal_dualCamera.dir/Main.cpp.o.requires
	$(MAKE) -f CMakeFiles/mmal_dualCamera.dir/build.make CMakeFiles/mmal_dualCamera.dir/Main.cpp.o.provides.build
.PHONY : CMakeFiles/mmal_dualCamera.dir/Main.cpp.o.provides

CMakeFiles/mmal_dualCamera.dir/Main.cpp.o.provides.build: CMakeFiles/mmal_dualCamera.dir/Main.cpp.o

CMakeFiles/mmal_dualCamera.dir/MmalDualCamera.cpp.o: CMakeFiles/mmal_dualCamera.dir/flags.make
CMakeFiles/mmal_dualCamera.dir/MmalDualCamera.cpp.o: ../MmalDualCamera.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/src/FUCKYOU/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mmal_dualCamera.dir/MmalDualCamera.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mmal_dualCamera.dir/MmalDualCamera.cpp.o -c /home/pi/src/FUCKYOU/MmalDualCamera.cpp

CMakeFiles/mmal_dualCamera.dir/MmalDualCamera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mmal_dualCamera.dir/MmalDualCamera.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/src/FUCKYOU/MmalDualCamera.cpp > CMakeFiles/mmal_dualCamera.dir/MmalDualCamera.cpp.i

CMakeFiles/mmal_dualCamera.dir/MmalDualCamera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mmal_dualCamera.dir/MmalDualCamera.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/src/FUCKYOU/MmalDualCamera.cpp -o CMakeFiles/mmal_dualCamera.dir/MmalDualCamera.cpp.s

CMakeFiles/mmal_dualCamera.dir/MmalDualCamera.cpp.o.requires:
.PHONY : CMakeFiles/mmal_dualCamera.dir/MmalDualCamera.cpp.o.requires

CMakeFiles/mmal_dualCamera.dir/MmalDualCamera.cpp.o.provides: CMakeFiles/mmal_dualCamera.dir/MmalDualCamera.cpp.o.requires
	$(MAKE) -f CMakeFiles/mmal_dualCamera.dir/build.make CMakeFiles/mmal_dualCamera.dir/MmalDualCamera.cpp.o.provides.build
.PHONY : CMakeFiles/mmal_dualCamera.dir/MmalDualCamera.cpp.o.provides

CMakeFiles/mmal_dualCamera.dir/MmalDualCamera.cpp.o.provides.build: CMakeFiles/mmal_dualCamera.dir/MmalDualCamera.cpp.o

CMakeFiles/mmal_dualCamera.dir/FkCamera.cpp.o: CMakeFiles/mmal_dualCamera.dir/flags.make
CMakeFiles/mmal_dualCamera.dir/FkCamera.cpp.o: ../FkCamera.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/src/FUCKYOU/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mmal_dualCamera.dir/FkCamera.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mmal_dualCamera.dir/FkCamera.cpp.o -c /home/pi/src/FUCKYOU/FkCamera.cpp

CMakeFiles/mmal_dualCamera.dir/FkCamera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mmal_dualCamera.dir/FkCamera.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/src/FUCKYOU/FkCamera.cpp > CMakeFiles/mmal_dualCamera.dir/FkCamera.cpp.i

CMakeFiles/mmal_dualCamera.dir/FkCamera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mmal_dualCamera.dir/FkCamera.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/src/FUCKYOU/FkCamera.cpp -o CMakeFiles/mmal_dualCamera.dir/FkCamera.cpp.s

CMakeFiles/mmal_dualCamera.dir/FkCamera.cpp.o.requires:
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkCamera.cpp.o.requires

CMakeFiles/mmal_dualCamera.dir/FkCamera.cpp.o.provides: CMakeFiles/mmal_dualCamera.dir/FkCamera.cpp.o.requires
	$(MAKE) -f CMakeFiles/mmal_dualCamera.dir/build.make CMakeFiles/mmal_dualCamera.dir/FkCamera.cpp.o.provides.build
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkCamera.cpp.o.provides

CMakeFiles/mmal_dualCamera.dir/FkCamera.cpp.o.provides.build: CMakeFiles/mmal_dualCamera.dir/FkCamera.cpp.o

CMakeFiles/mmal_dualCamera.dir/FkFingerKeyboard.cpp.o: CMakeFiles/mmal_dualCamera.dir/flags.make
CMakeFiles/mmal_dualCamera.dir/FkFingerKeyboard.cpp.o: ../FkFingerKeyboard.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/src/FUCKYOU/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mmal_dualCamera.dir/FkFingerKeyboard.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mmal_dualCamera.dir/FkFingerKeyboard.cpp.o -c /home/pi/src/FUCKYOU/FkFingerKeyboard.cpp

CMakeFiles/mmal_dualCamera.dir/FkFingerKeyboard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mmal_dualCamera.dir/FkFingerKeyboard.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/src/FUCKYOU/FkFingerKeyboard.cpp > CMakeFiles/mmal_dualCamera.dir/FkFingerKeyboard.cpp.i

CMakeFiles/mmal_dualCamera.dir/FkFingerKeyboard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mmal_dualCamera.dir/FkFingerKeyboard.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/src/FUCKYOU/FkFingerKeyboard.cpp -o CMakeFiles/mmal_dualCamera.dir/FkFingerKeyboard.cpp.s

CMakeFiles/mmal_dualCamera.dir/FkFingerKeyboard.cpp.o.requires:
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkFingerKeyboard.cpp.o.requires

CMakeFiles/mmal_dualCamera.dir/FkFingerKeyboard.cpp.o.provides: CMakeFiles/mmal_dualCamera.dir/FkFingerKeyboard.cpp.o.requires
	$(MAKE) -f CMakeFiles/mmal_dualCamera.dir/build.make CMakeFiles/mmal_dualCamera.dir/FkFingerKeyboard.cpp.o.provides.build
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkFingerKeyboard.cpp.o.provides

CMakeFiles/mmal_dualCamera.dir/FkFingerKeyboard.cpp.o.provides.build: CMakeFiles/mmal_dualCamera.dir/FkFingerKeyboard.cpp.o

CMakeFiles/mmal_dualCamera.dir/FkPostprocessor.cpp.o: CMakeFiles/mmal_dualCamera.dir/flags.make
CMakeFiles/mmal_dualCamera.dir/FkPostprocessor.cpp.o: ../FkPostprocessor.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/src/FUCKYOU/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mmal_dualCamera.dir/FkPostprocessor.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mmal_dualCamera.dir/FkPostprocessor.cpp.o -c /home/pi/src/FUCKYOU/FkPostprocessor.cpp

CMakeFiles/mmal_dualCamera.dir/FkPostprocessor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mmal_dualCamera.dir/FkPostprocessor.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/src/FUCKYOU/FkPostprocessor.cpp > CMakeFiles/mmal_dualCamera.dir/FkPostprocessor.cpp.i

CMakeFiles/mmal_dualCamera.dir/FkPostprocessor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mmal_dualCamera.dir/FkPostprocessor.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/src/FUCKYOU/FkPostprocessor.cpp -o CMakeFiles/mmal_dualCamera.dir/FkPostprocessor.cpp.s

CMakeFiles/mmal_dualCamera.dir/FkPostprocessor.cpp.o.requires:
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkPostprocessor.cpp.o.requires

CMakeFiles/mmal_dualCamera.dir/FkPostprocessor.cpp.o.provides: CMakeFiles/mmal_dualCamera.dir/FkPostprocessor.cpp.o.requires
	$(MAKE) -f CMakeFiles/mmal_dualCamera.dir/build.make CMakeFiles/mmal_dualCamera.dir/FkPostprocessor.cpp.o.provides.build
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkPostprocessor.cpp.o.provides

CMakeFiles/mmal_dualCamera.dir/FkPostprocessor.cpp.o.provides.build: CMakeFiles/mmal_dualCamera.dir/FkPostprocessor.cpp.o

CMakeFiles/mmal_dualCamera.dir/FkFingertipDetector.cpp.o: CMakeFiles/mmal_dualCamera.dir/flags.make
CMakeFiles/mmal_dualCamera.dir/FkFingertipDetector.cpp.o: ../FkFingertipDetector.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/src/FUCKYOU/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mmal_dualCamera.dir/FkFingertipDetector.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mmal_dualCamera.dir/FkFingertipDetector.cpp.o -c /home/pi/src/FUCKYOU/FkFingertipDetector.cpp

CMakeFiles/mmal_dualCamera.dir/FkFingertipDetector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mmal_dualCamera.dir/FkFingertipDetector.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/src/FUCKYOU/FkFingertipDetector.cpp > CMakeFiles/mmal_dualCamera.dir/FkFingertipDetector.cpp.i

CMakeFiles/mmal_dualCamera.dir/FkFingertipDetector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mmal_dualCamera.dir/FkFingertipDetector.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/src/FUCKYOU/FkFingertipDetector.cpp -o CMakeFiles/mmal_dualCamera.dir/FkFingertipDetector.cpp.s

CMakeFiles/mmal_dualCamera.dir/FkFingertipDetector.cpp.o.requires:
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkFingertipDetector.cpp.o.requires

CMakeFiles/mmal_dualCamera.dir/FkFingertipDetector.cpp.o.provides: CMakeFiles/mmal_dualCamera.dir/FkFingertipDetector.cpp.o.requires
	$(MAKE) -f CMakeFiles/mmal_dualCamera.dir/build.make CMakeFiles/mmal_dualCamera.dir/FkFingertipDetector.cpp.o.provides.build
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkFingertipDetector.cpp.o.provides

CMakeFiles/mmal_dualCamera.dir/FkFingertipDetector.cpp.o.provides.build: CMakeFiles/mmal_dualCamera.dir/FkFingertipDetector.cpp.o

CMakeFiles/mmal_dualCamera.dir/FkCurrentMode.cpp.o: CMakeFiles/mmal_dualCamera.dir/flags.make
CMakeFiles/mmal_dualCamera.dir/FkCurrentMode.cpp.o: ../FkCurrentMode.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/src/FUCKYOU/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mmal_dualCamera.dir/FkCurrentMode.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mmal_dualCamera.dir/FkCurrentMode.cpp.o -c /home/pi/src/FUCKYOU/FkCurrentMode.cpp

CMakeFiles/mmal_dualCamera.dir/FkCurrentMode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mmal_dualCamera.dir/FkCurrentMode.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/src/FUCKYOU/FkCurrentMode.cpp > CMakeFiles/mmal_dualCamera.dir/FkCurrentMode.cpp.i

CMakeFiles/mmal_dualCamera.dir/FkCurrentMode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mmal_dualCamera.dir/FkCurrentMode.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/src/FUCKYOU/FkCurrentMode.cpp -o CMakeFiles/mmal_dualCamera.dir/FkCurrentMode.cpp.s

CMakeFiles/mmal_dualCamera.dir/FkCurrentMode.cpp.o.requires:
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkCurrentMode.cpp.o.requires

CMakeFiles/mmal_dualCamera.dir/FkCurrentMode.cpp.o.provides: CMakeFiles/mmal_dualCamera.dir/FkCurrentMode.cpp.o.requires
	$(MAKE) -f CMakeFiles/mmal_dualCamera.dir/build.make CMakeFiles/mmal_dualCamera.dir/FkCurrentMode.cpp.o.provides.build
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkCurrentMode.cpp.o.provides

CMakeFiles/mmal_dualCamera.dir/FkCurrentMode.cpp.o.provides.build: CMakeFiles/mmal_dualCamera.dir/FkCurrentMode.cpp.o

CMakeFiles/mmal_dualCamera.dir/FkImageProcessor.cpp.o: CMakeFiles/mmal_dualCamera.dir/flags.make
CMakeFiles/mmal_dualCamera.dir/FkImageProcessor.cpp.o: ../FkImageProcessor.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/src/FUCKYOU/build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mmal_dualCamera.dir/FkImageProcessor.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mmal_dualCamera.dir/FkImageProcessor.cpp.o -c /home/pi/src/FUCKYOU/FkImageProcessor.cpp

CMakeFiles/mmal_dualCamera.dir/FkImageProcessor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mmal_dualCamera.dir/FkImageProcessor.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/src/FUCKYOU/FkImageProcessor.cpp > CMakeFiles/mmal_dualCamera.dir/FkImageProcessor.cpp.i

CMakeFiles/mmal_dualCamera.dir/FkImageProcessor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mmal_dualCamera.dir/FkImageProcessor.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/src/FUCKYOU/FkImageProcessor.cpp -o CMakeFiles/mmal_dualCamera.dir/FkImageProcessor.cpp.s

CMakeFiles/mmal_dualCamera.dir/FkImageProcessor.cpp.o.requires:
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkImageProcessor.cpp.o.requires

CMakeFiles/mmal_dualCamera.dir/FkImageProcessor.cpp.o.provides: CMakeFiles/mmal_dualCamera.dir/FkImageProcessor.cpp.o.requires
	$(MAKE) -f CMakeFiles/mmal_dualCamera.dir/build.make CMakeFiles/mmal_dualCamera.dir/FkImageProcessor.cpp.o.provides.build
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkImageProcessor.cpp.o.provides

CMakeFiles/mmal_dualCamera.dir/FkImageProcessor.cpp.o.provides.build: CMakeFiles/mmal_dualCamera.dir/FkImageProcessor.cpp.o

CMakeFiles/mmal_dualCamera.dir/FkKeyButton.cpp.o: CMakeFiles/mmal_dualCamera.dir/flags.make
CMakeFiles/mmal_dualCamera.dir/FkKeyButton.cpp.o: ../FkKeyButton.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/src/FUCKYOU/build/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mmal_dualCamera.dir/FkKeyButton.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mmal_dualCamera.dir/FkKeyButton.cpp.o -c /home/pi/src/FUCKYOU/FkKeyButton.cpp

CMakeFiles/mmal_dualCamera.dir/FkKeyButton.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mmal_dualCamera.dir/FkKeyButton.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/src/FUCKYOU/FkKeyButton.cpp > CMakeFiles/mmal_dualCamera.dir/FkKeyButton.cpp.i

CMakeFiles/mmal_dualCamera.dir/FkKeyButton.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mmal_dualCamera.dir/FkKeyButton.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/src/FUCKYOU/FkKeyButton.cpp -o CMakeFiles/mmal_dualCamera.dir/FkKeyButton.cpp.s

CMakeFiles/mmal_dualCamera.dir/FkKeyButton.cpp.o.requires:
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkKeyButton.cpp.o.requires

CMakeFiles/mmal_dualCamera.dir/FkKeyButton.cpp.o.provides: CMakeFiles/mmal_dualCamera.dir/FkKeyButton.cpp.o.requires
	$(MAKE) -f CMakeFiles/mmal_dualCamera.dir/build.make CMakeFiles/mmal_dualCamera.dir/FkKeyButton.cpp.o.provides.build
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkKeyButton.cpp.o.provides

CMakeFiles/mmal_dualCamera.dir/FkKeyButton.cpp.o.provides.build: CMakeFiles/mmal_dualCamera.dir/FkKeyButton.cpp.o

CMakeFiles/mmal_dualCamera.dir/FkKeyButtonEventListener.cpp.o: CMakeFiles/mmal_dualCamera.dir/flags.make
CMakeFiles/mmal_dualCamera.dir/FkKeyButtonEventListener.cpp.o: ../FkKeyButtonEventListener.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/src/FUCKYOU/build/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mmal_dualCamera.dir/FkKeyButtonEventListener.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mmal_dualCamera.dir/FkKeyButtonEventListener.cpp.o -c /home/pi/src/FUCKYOU/FkKeyButtonEventListener.cpp

CMakeFiles/mmal_dualCamera.dir/FkKeyButtonEventListener.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mmal_dualCamera.dir/FkKeyButtonEventListener.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/src/FUCKYOU/FkKeyButtonEventListener.cpp > CMakeFiles/mmal_dualCamera.dir/FkKeyButtonEventListener.cpp.i

CMakeFiles/mmal_dualCamera.dir/FkKeyButtonEventListener.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mmal_dualCamera.dir/FkKeyButtonEventListener.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/src/FUCKYOU/FkKeyButtonEventListener.cpp -o CMakeFiles/mmal_dualCamera.dir/FkKeyButtonEventListener.cpp.s

CMakeFiles/mmal_dualCamera.dir/FkKeyButtonEventListener.cpp.o.requires:
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkKeyButtonEventListener.cpp.o.requires

CMakeFiles/mmal_dualCamera.dir/FkKeyButtonEventListener.cpp.o.provides: CMakeFiles/mmal_dualCamera.dir/FkKeyButtonEventListener.cpp.o.requires
	$(MAKE) -f CMakeFiles/mmal_dualCamera.dir/build.make CMakeFiles/mmal_dualCamera.dir/FkKeyButtonEventListener.cpp.o.provides.build
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkKeyButtonEventListener.cpp.o.provides

CMakeFiles/mmal_dualCamera.dir/FkKeyButtonEventListener.cpp.o.provides.build: CMakeFiles/mmal_dualCamera.dir/FkKeyButtonEventListener.cpp.o

CMakeFiles/mmal_dualCamera.dir/FkMessage.cpp.o: CMakeFiles/mmal_dualCamera.dir/flags.make
CMakeFiles/mmal_dualCamera.dir/FkMessage.cpp.o: ../FkMessage.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/src/FUCKYOU/build/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mmal_dualCamera.dir/FkMessage.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mmal_dualCamera.dir/FkMessage.cpp.o -c /home/pi/src/FUCKYOU/FkMessage.cpp

CMakeFiles/mmal_dualCamera.dir/FkMessage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mmal_dualCamera.dir/FkMessage.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/src/FUCKYOU/FkMessage.cpp > CMakeFiles/mmal_dualCamera.dir/FkMessage.cpp.i

CMakeFiles/mmal_dualCamera.dir/FkMessage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mmal_dualCamera.dir/FkMessage.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/src/FUCKYOU/FkMessage.cpp -o CMakeFiles/mmal_dualCamera.dir/FkMessage.cpp.s

CMakeFiles/mmal_dualCamera.dir/FkMessage.cpp.o.requires:
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkMessage.cpp.o.requires

CMakeFiles/mmal_dualCamera.dir/FkMessage.cpp.o.provides: CMakeFiles/mmal_dualCamera.dir/FkMessage.cpp.o.requires
	$(MAKE) -f CMakeFiles/mmal_dualCamera.dir/build.make CMakeFiles/mmal_dualCamera.dir/FkMessage.cpp.o.provides.build
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkMessage.cpp.o.provides

CMakeFiles/mmal_dualCamera.dir/FkMessage.cpp.o.provides.build: CMakeFiles/mmal_dualCamera.dir/FkMessage.cpp.o

CMakeFiles/mmal_dualCamera.dir/FkMouse.cpp.o: CMakeFiles/mmal_dualCamera.dir/flags.make
CMakeFiles/mmal_dualCamera.dir/FkMouse.cpp.o: ../FkMouse.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/src/FUCKYOU/build/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mmal_dualCamera.dir/FkMouse.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mmal_dualCamera.dir/FkMouse.cpp.o -c /home/pi/src/FUCKYOU/FkMouse.cpp

CMakeFiles/mmal_dualCamera.dir/FkMouse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mmal_dualCamera.dir/FkMouse.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/src/FUCKYOU/FkMouse.cpp > CMakeFiles/mmal_dualCamera.dir/FkMouse.cpp.i

CMakeFiles/mmal_dualCamera.dir/FkMouse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mmal_dualCamera.dir/FkMouse.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/src/FUCKYOU/FkMouse.cpp -o CMakeFiles/mmal_dualCamera.dir/FkMouse.cpp.s

CMakeFiles/mmal_dualCamera.dir/FkMouse.cpp.o.requires:
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkMouse.cpp.o.requires

CMakeFiles/mmal_dualCamera.dir/FkMouse.cpp.o.provides: CMakeFiles/mmal_dualCamera.dir/FkMouse.cpp.o.requires
	$(MAKE) -f CMakeFiles/mmal_dualCamera.dir/build.make CMakeFiles/mmal_dualCamera.dir/FkMouse.cpp.o.provides.build
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkMouse.cpp.o.provides

CMakeFiles/mmal_dualCamera.dir/FkMouse.cpp.o.provides.build: CMakeFiles/mmal_dualCamera.dir/FkMouse.cpp.o

CMakeFiles/mmal_dualCamera.dir/FkMouseListener.cpp.o: CMakeFiles/mmal_dualCamera.dir/flags.make
CMakeFiles/mmal_dualCamera.dir/FkMouseListener.cpp.o: ../FkMouseListener.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/src/FUCKYOU/build/CMakeFiles $(CMAKE_PROGRESS_13)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mmal_dualCamera.dir/FkMouseListener.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mmal_dualCamera.dir/FkMouseListener.cpp.o -c /home/pi/src/FUCKYOU/FkMouseListener.cpp

CMakeFiles/mmal_dualCamera.dir/FkMouseListener.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mmal_dualCamera.dir/FkMouseListener.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/src/FUCKYOU/FkMouseListener.cpp > CMakeFiles/mmal_dualCamera.dir/FkMouseListener.cpp.i

CMakeFiles/mmal_dualCamera.dir/FkMouseListener.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mmal_dualCamera.dir/FkMouseListener.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/src/FUCKYOU/FkMouseListener.cpp -o CMakeFiles/mmal_dualCamera.dir/FkMouseListener.cpp.s

CMakeFiles/mmal_dualCamera.dir/FkMouseListener.cpp.o.requires:
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkMouseListener.cpp.o.requires

CMakeFiles/mmal_dualCamera.dir/FkMouseListener.cpp.o.provides: CMakeFiles/mmal_dualCamera.dir/FkMouseListener.cpp.o.requires
	$(MAKE) -f CMakeFiles/mmal_dualCamera.dir/build.make CMakeFiles/mmal_dualCamera.dir/FkMouseListener.cpp.o.provides.build
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkMouseListener.cpp.o.provides

CMakeFiles/mmal_dualCamera.dir/FkMouseListener.cpp.o.provides.build: CMakeFiles/mmal_dualCamera.dir/FkMouseListener.cpp.o

CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard.cpp.o: CMakeFiles/mmal_dualCamera.dir/flags.make
CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard.cpp.o: ../FkPaperKeyboard.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/src/FUCKYOU/build/CMakeFiles $(CMAKE_PROGRESS_14)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard.cpp.o -c /home/pi/src/FUCKYOU/FkPaperKeyboard.cpp

CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/src/FUCKYOU/FkPaperKeyboard.cpp > CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard.cpp.i

CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/src/FUCKYOU/FkPaperKeyboard.cpp -o CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard.cpp.s

CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard.cpp.o.requires:
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard.cpp.o.requires

CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard.cpp.o.provides: CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard.cpp.o.requires
	$(MAKE) -f CMakeFiles/mmal_dualCamera.dir/build.make CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard.cpp.o.provides.build
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard.cpp.o.provides

CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard.cpp.o.provides.build: CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard.cpp.o

CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard_TypeA.cpp.o: CMakeFiles/mmal_dualCamera.dir/flags.make
CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard_TypeA.cpp.o: ../FkPaperKeyboard_TypeA.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/src/FUCKYOU/build/CMakeFiles $(CMAKE_PROGRESS_15)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard_TypeA.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard_TypeA.cpp.o -c /home/pi/src/FUCKYOU/FkPaperKeyboard_TypeA.cpp

CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard_TypeA.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard_TypeA.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/src/FUCKYOU/FkPaperKeyboard_TypeA.cpp > CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard_TypeA.cpp.i

CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard_TypeA.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard_TypeA.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/src/FUCKYOU/FkPaperKeyboard_TypeA.cpp -o CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard_TypeA.cpp.s

CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard_TypeA.cpp.o.requires:
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard_TypeA.cpp.o.requires

CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard_TypeA.cpp.o.provides: CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard_TypeA.cpp.o.requires
	$(MAKE) -f CMakeFiles/mmal_dualCamera.dir/build.make CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard_TypeA.cpp.o.provides.build
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard_TypeA.cpp.o.provides

CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard_TypeA.cpp.o.provides.build: CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard_TypeA.cpp.o

CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboardRecognizer.cpp.o: CMakeFiles/mmal_dualCamera.dir/flags.make
CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboardRecognizer.cpp.o: ../FkPaperKeyboardRecognizer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/src/FUCKYOU/build/CMakeFiles $(CMAKE_PROGRESS_16)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboardRecognizer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboardRecognizer.cpp.o -c /home/pi/src/FUCKYOU/FkPaperKeyboardRecognizer.cpp

CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboardRecognizer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboardRecognizer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/src/FUCKYOU/FkPaperKeyboardRecognizer.cpp > CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboardRecognizer.cpp.i

CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboardRecognizer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboardRecognizer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/src/FUCKYOU/FkPaperKeyboardRecognizer.cpp -o CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboardRecognizer.cpp.s

CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboardRecognizer.cpp.o.requires:
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboardRecognizer.cpp.o.requires

CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboardRecognizer.cpp.o.provides: CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboardRecognizer.cpp.o.requires
	$(MAKE) -f CMakeFiles/mmal_dualCamera.dir/build.make CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboardRecognizer.cpp.o.provides.build
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboardRecognizer.cpp.o.provides

CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboardRecognizer.cpp.o.provides.build: CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboardRecognizer.cpp.o

CMakeFiles/mmal_dualCamera.dir/FkPreprocessor.cpp.o: CMakeFiles/mmal_dualCamera.dir/flags.make
CMakeFiles/mmal_dualCamera.dir/FkPreprocessor.cpp.o: ../FkPreprocessor.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/src/FUCKYOU/build/CMakeFiles $(CMAKE_PROGRESS_17)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mmal_dualCamera.dir/FkPreprocessor.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mmal_dualCamera.dir/FkPreprocessor.cpp.o -c /home/pi/src/FUCKYOU/FkPreprocessor.cpp

CMakeFiles/mmal_dualCamera.dir/FkPreprocessor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mmal_dualCamera.dir/FkPreprocessor.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/src/FUCKYOU/FkPreprocessor.cpp > CMakeFiles/mmal_dualCamera.dir/FkPreprocessor.cpp.i

CMakeFiles/mmal_dualCamera.dir/FkPreprocessor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mmal_dualCamera.dir/FkPreprocessor.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/src/FUCKYOU/FkPreprocessor.cpp -o CMakeFiles/mmal_dualCamera.dir/FkPreprocessor.cpp.s

CMakeFiles/mmal_dualCamera.dir/FkPreprocessor.cpp.o.requires:
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkPreprocessor.cpp.o.requires

CMakeFiles/mmal_dualCamera.dir/FkPreprocessor.cpp.o.provides: CMakeFiles/mmal_dualCamera.dir/FkPreprocessor.cpp.o.requires
	$(MAKE) -f CMakeFiles/mmal_dualCamera.dir/build.make CMakeFiles/mmal_dualCamera.dir/FkPreprocessor.cpp.o.provides.build
.PHONY : CMakeFiles/mmal_dualCamera.dir/FkPreprocessor.cpp.o.provides

CMakeFiles/mmal_dualCamera.dir/FkPreprocessor.cpp.o.provides.build: CMakeFiles/mmal_dualCamera.dir/FkPreprocessor.cpp.o

# Object files for target mmal_dualCamera
mmal_dualCamera_OBJECTS = \
"CMakeFiles/mmal_dualCamera.dir/Main.cpp.o" \
"CMakeFiles/mmal_dualCamera.dir/MmalDualCamera.cpp.o" \
"CMakeFiles/mmal_dualCamera.dir/FkCamera.cpp.o" \
"CMakeFiles/mmal_dualCamera.dir/FkFingerKeyboard.cpp.o" \
"CMakeFiles/mmal_dualCamera.dir/FkPostprocessor.cpp.o" \
"CMakeFiles/mmal_dualCamera.dir/FkFingertipDetector.cpp.o" \
"CMakeFiles/mmal_dualCamera.dir/FkCurrentMode.cpp.o" \
"CMakeFiles/mmal_dualCamera.dir/FkImageProcessor.cpp.o" \
"CMakeFiles/mmal_dualCamera.dir/FkKeyButton.cpp.o" \
"CMakeFiles/mmal_dualCamera.dir/FkKeyButtonEventListener.cpp.o" \
"CMakeFiles/mmal_dualCamera.dir/FkMessage.cpp.o" \
"CMakeFiles/mmal_dualCamera.dir/FkMouse.cpp.o" \
"CMakeFiles/mmal_dualCamera.dir/FkMouseListener.cpp.o" \
"CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard.cpp.o" \
"CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard_TypeA.cpp.o" \
"CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboardRecognizer.cpp.o" \
"CMakeFiles/mmal_dualCamera.dir/FkPreprocessor.cpp.o"

# External object files for target mmal_dualCamera
mmal_dualCamera_EXTERNAL_OBJECTS =

mmal_dualCamera: CMakeFiles/mmal_dualCamera.dir/Main.cpp.o
mmal_dualCamera: CMakeFiles/mmal_dualCamera.dir/MmalDualCamera.cpp.o
mmal_dualCamera: CMakeFiles/mmal_dualCamera.dir/FkCamera.cpp.o
mmal_dualCamera: CMakeFiles/mmal_dualCamera.dir/FkFingerKeyboard.cpp.o
mmal_dualCamera: CMakeFiles/mmal_dualCamera.dir/FkPostprocessor.cpp.o
mmal_dualCamera: CMakeFiles/mmal_dualCamera.dir/FkFingertipDetector.cpp.o
mmal_dualCamera: CMakeFiles/mmal_dualCamera.dir/FkCurrentMode.cpp.o
mmal_dualCamera: CMakeFiles/mmal_dualCamera.dir/FkImageProcessor.cpp.o
mmal_dualCamera: CMakeFiles/mmal_dualCamera.dir/FkKeyButton.cpp.o
mmal_dualCamera: CMakeFiles/mmal_dualCamera.dir/FkKeyButtonEventListener.cpp.o
mmal_dualCamera: CMakeFiles/mmal_dualCamera.dir/FkMessage.cpp.o
mmal_dualCamera: CMakeFiles/mmal_dualCamera.dir/FkMouse.cpp.o
mmal_dualCamera: CMakeFiles/mmal_dualCamera.dir/FkMouseListener.cpp.o
mmal_dualCamera: CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard.cpp.o
mmal_dualCamera: CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard_TypeA.cpp.o
mmal_dualCamera: CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboardRecognizer.cpp.o
mmal_dualCamera: CMakeFiles/mmal_dualCamera.dir/FkPreprocessor.cpp.o
mmal_dualCamera: CMakeFiles/mmal_dualCamera.dir/build.make
mmal_dualCamera: /usr/lib/libopencv_calib3d.so
mmal_dualCamera: /usr/lib/libopencv_contrib.so
mmal_dualCamera: /usr/lib/libopencv_core.so
mmal_dualCamera: /usr/lib/libopencv_features2d.so
mmal_dualCamera: /usr/lib/libopencv_flann.so
mmal_dualCamera: /usr/lib/libopencv_highgui.so
mmal_dualCamera: /usr/lib/libopencv_imgproc.so
mmal_dualCamera: /usr/lib/libopencv_legacy.so
mmal_dualCamera: /usr/lib/libopencv_ml.so
mmal_dualCamera: /usr/lib/libopencv_objdetect.so
mmal_dualCamera: /usr/lib/libopencv_photo.so
mmal_dualCamera: /usr/lib/libopencv_stitching.so
mmal_dualCamera: /usr/lib/libopencv_ts.so
mmal_dualCamera: /usr/lib/libopencv_video.so
mmal_dualCamera: /usr/lib/libopencv_videostab.so
mmal_dualCamera: CMakeFiles/mmal_dualCamera.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable mmal_dualCamera"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mmal_dualCamera.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mmal_dualCamera.dir/build: mmal_dualCamera
.PHONY : CMakeFiles/mmal_dualCamera.dir/build

CMakeFiles/mmal_dualCamera.dir/requires: CMakeFiles/mmal_dualCamera.dir/Main.cpp.o.requires
CMakeFiles/mmal_dualCamera.dir/requires: CMakeFiles/mmal_dualCamera.dir/MmalDualCamera.cpp.o.requires
CMakeFiles/mmal_dualCamera.dir/requires: CMakeFiles/mmal_dualCamera.dir/FkCamera.cpp.o.requires
CMakeFiles/mmal_dualCamera.dir/requires: CMakeFiles/mmal_dualCamera.dir/FkFingerKeyboard.cpp.o.requires
CMakeFiles/mmal_dualCamera.dir/requires: CMakeFiles/mmal_dualCamera.dir/FkPostprocessor.cpp.o.requires
CMakeFiles/mmal_dualCamera.dir/requires: CMakeFiles/mmal_dualCamera.dir/FkFingertipDetector.cpp.o.requires
CMakeFiles/mmal_dualCamera.dir/requires: CMakeFiles/mmal_dualCamera.dir/FkCurrentMode.cpp.o.requires
CMakeFiles/mmal_dualCamera.dir/requires: CMakeFiles/mmal_dualCamera.dir/FkImageProcessor.cpp.o.requires
CMakeFiles/mmal_dualCamera.dir/requires: CMakeFiles/mmal_dualCamera.dir/FkKeyButton.cpp.o.requires
CMakeFiles/mmal_dualCamera.dir/requires: CMakeFiles/mmal_dualCamera.dir/FkKeyButtonEventListener.cpp.o.requires
CMakeFiles/mmal_dualCamera.dir/requires: CMakeFiles/mmal_dualCamera.dir/FkMessage.cpp.o.requires
CMakeFiles/mmal_dualCamera.dir/requires: CMakeFiles/mmal_dualCamera.dir/FkMouse.cpp.o.requires
CMakeFiles/mmal_dualCamera.dir/requires: CMakeFiles/mmal_dualCamera.dir/FkMouseListener.cpp.o.requires
CMakeFiles/mmal_dualCamera.dir/requires: CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard.cpp.o.requires
CMakeFiles/mmal_dualCamera.dir/requires: CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboard_TypeA.cpp.o.requires
CMakeFiles/mmal_dualCamera.dir/requires: CMakeFiles/mmal_dualCamera.dir/FkPaperKeyboardRecognizer.cpp.o.requires
CMakeFiles/mmal_dualCamera.dir/requires: CMakeFiles/mmal_dualCamera.dir/FkPreprocessor.cpp.o.requires
.PHONY : CMakeFiles/mmal_dualCamera.dir/requires

CMakeFiles/mmal_dualCamera.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mmal_dualCamera.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mmal_dualCamera.dir/clean

CMakeFiles/mmal_dualCamera.dir/depend:
	cd /home/pi/src/FUCKYOU/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/src/FUCKYOU /home/pi/src/FUCKYOU /home/pi/src/FUCKYOU/build /home/pi/src/FUCKYOU/build /home/pi/src/FUCKYOU/build/CMakeFiles/mmal_dualCamera.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mmal_dualCamera.dir/depend
