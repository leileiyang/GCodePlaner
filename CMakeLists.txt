cmake_minimum_required (VERSION 2.8)

project (Workpiece)

set_property (GLOBAL PROPERTY USE_FOLDERS ON)

if (MSVC)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif (MSVC)

file (GLOB SRC_FILES
  "workpiecedata.h"
  "workpiecedata.cpp"
  "workpiece.h"
  "workpiece.cpp")

file (GLOB GCODE_FILES
  "gcode/*.h"
  "gcode/*.cpp")

file (GLOB NEOMATH_FILES
  "neomath/*h"
  "neomath/*.c"
  "neomath/*.cpp")

source_group ("gcode" FILES ${GCODE_FILES})
source_group ("neomath" FILES ${NEOMATH_FILES})

include_directories (.)

if (UNIX)
include_directories ("/usr/include/qt4")
endif (UNIX)

add_library (Workpiece STATIC ${SRC_FILES} ${GCODE_FILES} ${NEOMATH_FILES})
