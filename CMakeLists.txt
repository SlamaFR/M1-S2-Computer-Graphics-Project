cmake_minimum_required(VERSION 2.8...3.22)

project("OpenGL Scene Viewer")

include_directories(AFTER SYSTEM $ENV{G3X_PATH}/include)
set(CMAKE_C_FLAGS "-lm -L$ENV{lGL_PATH} -framework OpenGL -framework GLUT -L$ENV{G3X_PATH} -lg3x.6d.$ENV{PROCBIT}")

file(GLOB_RECURSE SCENES_FILES scenes/*.c)
file(GLOB_RECURSE SHAPES_FILES shapes/*.c)
file(GLOB_RECURSE TREES_FILES trees/*.c)
add_executable(project ${SCENES_FILES} ${SHAPES_FILES} ${TREES_FILES} utils.c main.c)

# Remove warnings at compilation time
add_definitions(-w)
