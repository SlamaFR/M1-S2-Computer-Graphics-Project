cmake_minimum_required(VERSION 2.8)

# find opencv
find_package(OpenCV REQUIRED)

include_directories(AFTER SYSTEM $ENV{G3X_PATH}/include)

set(CMAKE_C_FLAGS "-lm -L$ENV{lGL_PATH} -framework OpenGL -framework GLUT -L$ENV{G3X_PATH} -lg3x.6d.$ENV{PROCBIT}")

# or the automatic version
file(GLOB_RECURSE SRC_FILES *.c)
file(GLOB_RECURSE SRC_SHAPES shapes/*.c)

# for each sample file, make an exe
add_executable(project ${SRC_FILES} ${SRC_SHAPES})
target_link_libraries(project ${OpenCV_LIBS})

