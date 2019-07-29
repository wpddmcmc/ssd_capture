cmake_minimum_required (VERSION 2.8)

# project name
project (inspur_ssddetector)
# using C++11 
set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11 -pthread")

# if u have OpenCV version more than one, set the build path which one u want to use
 set(OpenCV_DIR "/home/mingcongchen/app/opencv-4.1.0/build/")
# find opencv
find_package(OpenCV REQUIRED)
# print message of opencv
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV include path: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "    libraries: ${OpenCV_LIBS}")

aux_source_directory(./src/ DIR_SRCS)

add_executable(inspur_ssddetector  ${DIR_SRCS})

include_directories ( 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    /home/mingcongchen/app/caffe-ssd/include
    /usr/local/cuda-9.0/include   
    /usr/local/include
    /usr/include 
${OpenCV_INCLUDE_DIRS})

target_link_libraries(inspur_ssddetector
${OpenCV_LIBS}
/home/mingcongchen/app/caffe-ssd/build/lib/libcaffe.so
/usr/lib
/usr/local/lib
/usr/local/lib/libglog.so.0
/usr/local/lib/libboost_system.so.1.66.0
    )
