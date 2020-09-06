
#specifying output files
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#finding the gtk packages
find_package(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

#linking with GTK3
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

set(INCLUDE_DIR ../include)

#compiling static libraries
# our_math.a
add_library(our_math STATIC 
            ${INCLUDE_DIR}/our_math.h our_math.cpp)
# graphics.a
add_library(graphics STATIC 
            ${INCLUDE_DIR}/graphics.h graphics.cpp 
            ${INCLUDE_DIR}/our_math.h our_math.cpp 
            ${INCLUDE_DIR}/logic.h logic.cpp)
# logic.a
add_library(logic STATIC 
            ${INCLUDE_DIR}/our_math.h our_math.cpp 
            ${INCLUDE_DIR}/logic.h logic.cpp)

#compiling ${PROJ_NAME_DYNAMIC_SUFF} libraries
# our_math-s.so
add_library(our_math-s SHARED 
            ${INCLUDE_DIR}/our_math.h our_math.cpp)
# graphics-s.so
add_library(graphics-s SHARED 
            ${INCLUDE_DIR}/graphics.h graphics.cpp 
            ${INCLUDE_DIR}/our_math.h our_math.cpp 
            ${INCLUDE_DIR}/logic.h logic.cpp)
# logic-s.so
add_library(logic-s SHARED 
            ${INCLUDE_DIR}/our_math.h our_math.cpp 
            ${INCLUDE_DIR}/logic.h logic.cpp)

#creates a variable LIBRARIES, that holds all the libraries
set(LIBRARIES graphics ${GTK3_LIBRARIES})
set(SHARED_LIBRARIES graphics-s ${GTK3_LIBRARIES})

#creating executables
#CMAKE_PROJECT_NAME is a variable set in the main CMakeLists.txt file

#calculator - the main program
add_executable(${CMAKE_PROJECT_NAME} main.cpp)

#calculator linked with .so libray
add_executable(${CMAKE_PROJECT_NAME}_${PROJ_NAME_DYNAMIC_SUFF} main.cpp)

#stddev program
add_executable(stddev stddev.cpp)

#stddev program compiled for profiling
add_executable(stddev_profile stddev.cpp 
               ${INCLUDE_DIR}/our_math.h our_math.cpp 
               ${INCLUDE_DIR}/logic.h logic.cpp)

#setting the compiler flags for profiling
set_target_properties(stddev_profile PROPERTIES COMPILE_FLAGS "-g -pg" LINK_FLAGS "-g -pg")

#linking graphics with GTK3
target_link_libraries(graphics ${GTK3_LIBRARIES})

#linking main with all the necessary libraries
target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBRARIES})
target_link_libraries(${CMAKE_PROJECT_NAME}_${PROJ_NAME_DYNAMIC_SUFF} ${SHARED_LIBRARIES})

#linking stddev with logic
target_link_libraries(stddev logic) 

#adding new executable which has to be linked with gtest_main to work
add_executable(${CMAKE_PROJECT_NAME}_test tests.cpp test_mock_stub.cpp ${INCLUDE_DIR}/tests.h)

#adding google tests
add_test(NAME ${CMAKE_PROJECT_NAME}_test COMMAND ${CMAKE_PROJECT_NAME}_test)

#creating variable TEST_LIBRARIES
set(TEST_LIBRARIES logic gtest gtest_main)

#linking tests with the libraries
target_link_libraries(${CMAKE_PROJECT_NAME}_test PUBLIC ${TEST_LIBRARIES})

