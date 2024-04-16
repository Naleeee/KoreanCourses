cmake_minimum_required(VERSION 3.8)

project("lab" VERSION 0.0.1 LANGUAGES CXX)

option(SHARED_LIBGCC "Shared Libgcc" ON)

###############################################################################
# BUILD PROJECT
###############################################################################

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -m32")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -lGL")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -lfltk")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -lfltk_gl")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -lGLU")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -m32")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -lGL")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -lfltk")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -lfltk_gl")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -lGLU")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_SOURCES
    src/Cyclone/body.cpp
    src/Cyclone/collide_coarse.cpp
    src/Cyclone/collide_fine.cpp
    src/Cyclone/contacts.cpp
    src/Cyclone/core.cpp
    src/Cyclone/fgen.cpp
    src/Cyclone/joints.cpp
    src/Cyclone/particle.cpp
    src/Cyclone/pcontacts.cpp
    src/Cyclone/pfgen.cpp
    src/Cyclone/plinks.cpp
    src/Cyclone/pworld.cpp
    src/Cyclone/random.cpp
    src/Cyclone/world.cpp
    src/3DUtils.cpp
    src/DrawUtils.cpp
		src/Fire.cpp
		src/Fireworks.cpp
		src/FireworksRule.cpp
    src/MMatrix.cpp
    src/MyGlWindow.cpp
		src/MySpring.cpp
    src/object.cpp
    src/stdafx.cpp
    src/timing.cpp
    src/Viewer.cpp
    )

add_executable(${PROJECT_NAME}
    src/main.cpp
    ${PROJECT_SOURCES}
    )

target_include_directories(
		${PROJECT_NAME}
		PRIVATE
    include/
		include/Cyclone
		include/FL
		include/GL
		include/glm
)
