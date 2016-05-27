cmake_minimum_required(VERSION 2.6)
project(Pancho)

set(CMAKE_C_COMPILER C:/MinGW/mingw64/bin/gcc.exe)
set(CMAKE_CXX_COMPILER C:/MinGW/mingw64/bin/g++.exe)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
file(GLOB SOURCES "src/*.cpp" "src/objects/*.cpp")

add_executable(pancho ${SOURCES})

if (WIN32)
	include_directories(C:/MinGW/mingw64/lib/gcc/x86_64-w64-mingw32/4.9.2/include)
	link_directories(C:/MinGW/mingw64/lib)
	target_link_libraries(pancho glew32s glfw3 opengl32 gdi32 png z OpenAL32)
endif (WIN32)
