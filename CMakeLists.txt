# OGRE Base Project
#
# 2022-2023
#
# Originally based on the Official Ogre Tutorials
# (Tutorial Framework) http://www.ogre3d.org/tikiwiki/
# heavily modified for CMU students - CIS5012.

# Set the Executable name.
set(APP "BeerPong")

project(${APP})

cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads)


set(HDRS
	./src/Game.h
	./src/Objects/Object4o.h
	./src/Objects/OCamera.h

)

set(SRCS
	./src/Game.cpp
	./src/Objects/Object4o.cpp
	./src/Objects/OCamera.cpp
	./src/main.cpp

)

include("tools/cmake/common.cmake")

# As of Ogre 1.13 Bullet is a plugin, so as long as
# its found by CMake we've nothing else to do.

include("tools/cmake/bulletBase.cmake")
include("tools/cmake/ogreBase.cmake")
