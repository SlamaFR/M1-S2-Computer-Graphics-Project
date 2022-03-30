cmake_minimum_required(VERSION 2.8...3.22)

project("OpenGL Scene Viewer")

include_directories(AFTER SYSTEM $ENV{G3X_PATH}/include)
set(CMAKE_C_FLAGS "-lm -L$ENV{lGL_PATH} -framework OpenGL -framework GLUT -L$ENV{G3X_PATH} -lg3x.6d.$ENV{PROCBIT}")

file(GLOB_RECURSE SCENES_FILES src/scenes/*.c)
file(GLOB_RECURSE SHAPES_FILES src/shapes/*.c)
file(GLOB_RECURSE TREES_FILES src/trees/*.c)

add_executable(scene1 ${SCENES_FILES} ${SHAPES_FILES} ${TREES_FILES} src/utils.c src/scene1.c)
add_executable(scene2 ${SCENES_FILES} ${SHAPES_FILES} ${TREES_FILES} src/utils.c src/scene2.c)

# Remove warnings at compilation time
add_definitions(-w)
