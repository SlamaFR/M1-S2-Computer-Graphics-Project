cmake_minimum_required(VERSION 2.8)

include_directories(AFTER SYSTEM $ENV{G3X_PATH}/include)
set(CMAKE_C_FLAGS "-lm -L$ENV{lGL_PATH} -framework OpenGL -framework GLUT -L$ENV{G3X_PATH} -lg3x.6d.$ENV{PROCBIT}")

file(GLOB_RECURSE SRC_FILES *.c)
add_executable(project ${SRC_FILES})
