cmake_minimum_required(VERSION 2.8)

project( homework )

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( homework_1 homework_1.cpp )
add_executable( homework_2 homework_2.cpp )

################
target_link_libraries( homework_1 ${OpenCV_LIBS} )
target_link_libraries( homework_2 ${OpenCV_LIBS} )
