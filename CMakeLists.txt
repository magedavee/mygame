cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(mygame)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}" "/include")
message(STATUS ${PROJECT_SOURCE_DIR})
include_directories(${INC_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp )
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h )
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${mygame_SOURCE_DIR}/cmake")

#For Mac OS X Use @rpath on OS X
if(APPLE)
	if(POLICY CMP0042)
		CMAKE_POLICY(SET CMP0042 NEW)
	endif()
endif()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})


#########################################################
# FIND GLUT
#########################################################
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)
#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)
