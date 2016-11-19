cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(mygame)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}" "/include")
message(STATUS "include direrectory" ${INC_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp )
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h )
message (STATUS 'Sources:' ${sources})
message (STATUS 'Headers:' ${headers})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${mygame_SOURCE_DIR}/cmake")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(NAME "my_game")
set(EXECUTABLE "${CMAKE_BINARY_DIR}/bin/${NAME}")

#For Mac OS X Use @rpath on OS X
if(APPLE)
	if(POLICY CMP0042)
		CMAKE_POLICY(SET CMP0042 NEW)
	endif()
endif()

file(WRITE .run_dir ${EXECUTABLE})
execute_process(COMMAND mv .run_dir "${CMAKE_BINARY_DIR}/." WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_VARIABLE OUT)



#######################################################
# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

########################################################
########################################################
# FIND GLEW
########################################################
    find_package(GLEW REQUIRED)
    if (GLEW_FOUND)
	include_directories(${GLEW_INCLUDE_DIRS})
	link_libraries(${GLEW_LIBRARIES})
    endif()
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


add_library(GameLib SHARED ${sources} ${headers})
link_directories(${LIBRARY_OUTPUT_PATH})
target_link_libraries(GameLib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${SDL2_LIBRARY}
    ${SDL2_TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY} X11)

add_executable(${NAME} ${PROJECT_SOURCE_DIR}/main.cpp)


target_link_libraries(${NAME} GameLib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} X11)


set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3 -Wextra -Wpedantic")
set(CMAKE_BUILD_TYPE debug)
