﻿# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.31

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Dell\Downloads\CS202-SuperMario

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Dell\Downloads\CS202-SuperMario\build

# Include any dependencies generated for this target.
include CMakeFiles\SuperMario.dir\depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles\SuperMario.dir\compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles\SuperMario.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\SuperMario.dir\flags.make

CMakeFiles\SuperMario.dir\codegen:
.PHONY : CMakeFiles\SuperMario.dir\codegen

CMakeFiles\SuperMario.dir\src\Main.cpp.obj: CMakeFiles\SuperMario.dir\flags.make
CMakeFiles\SuperMario.dir\src\Main.cpp.obj: C:\Users\Dell\Downloads\CS202-SuperMario\src\Main.cpp
CMakeFiles\SuperMario.dir\src\Main.cpp.obj: CMakeFiles\SuperMario.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Dell\Downloads\CS202-SuperMario\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SuperMario.dir/src/Main.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\SuperMario.dir\src\Main.cpp.obj.d --working-dir=C:\Users\Dell\Downloads\CS202-SuperMario\build --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~3\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\SuperMario.dir\src\Main.cpp.obj /FdCMakeFiles\SuperMario.dir\ /FS -c C:\Users\Dell\Downloads\CS202-SuperMario\src\Main.cpp
<<

CMakeFiles\SuperMario.dir\src\Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SuperMario.dir/src/Main.cpp.i"
	C:\PROGRA~2\MICROS~3\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe > CMakeFiles\SuperMario.dir\src\Main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Dell\Downloads\CS202-SuperMario\src\Main.cpp
<<

CMakeFiles\SuperMario.dir\src\Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SuperMario.dir/src/Main.cpp.s"
	C:\PROGRA~2\MICROS~3\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\SuperMario.dir\src\Main.cpp.s /c C:\Users\Dell\Downloads\CS202-SuperMario\src\Main.cpp
<<

# Object files for target SuperMario
SuperMario_OBJECTS = \
"CMakeFiles\SuperMario.dir\src\Main.cpp.obj"

# External object files for target SuperMario
SuperMario_EXTERNAL_OBJECTS =

SuperMario.exe: CMakeFiles\SuperMario.dir\src\Main.cpp.obj
SuperMario.exe: CMakeFiles\SuperMario.dir\build.make
SuperMario.exe: CMakeFiles\SuperMario.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\Dell\Downloads\CS202-SuperMario\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SuperMario.exe"
	"C:\Program Files\CMake\bin\cmake.exe" -E vs_link_exe --msvc-ver=1942 --intdir=CMakeFiles\SuperMario.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100226~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100226~1.0\x86\mt.exe --manifests -- C:\PROGRA~2\MICROS~3\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\SuperMario.dir\objects1.rsp @<<
 /out:SuperMario.exe /implib:SuperMario.lib /pdb:C:\Users\Dell\Downloads\CS202-SuperMario\build\SuperMario.pdb /version:0.0 /machine:X86 /debug /INCREMENTAL /subsystem:console   -LIBPATH:C:\Users\Dell\Downloads\CS202-SuperMario\lib\lib  raylib.lib opengl32.lib gdi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\SuperMario.dir\build: SuperMario.exe
.PHONY : CMakeFiles\SuperMario.dir\build

CMakeFiles\SuperMario.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\SuperMario.dir\cmake_clean.cmake
.PHONY : CMakeFiles\SuperMario.dir\clean

CMakeFiles\SuperMario.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\Dell\Downloads\CS202-SuperMario C:\Users\Dell\Downloads\CS202-SuperMario C:\Users\Dell\Downloads\CS202-SuperMario\build C:\Users\Dell\Downloads\CS202-SuperMario\build C:\Users\Dell\Downloads\CS202-SuperMario\build\CMakeFiles\SuperMario.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles\SuperMario.dir\depend

