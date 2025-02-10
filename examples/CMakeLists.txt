PROJECT(HW3)
## Add definitions ##
add_definitions(-D_LARGEFILE_SOURCE -D_LARGE_FILES -D_FILE_OFFSET_BITS=64)

## Targets ##
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../include"
                    "${CMAKE_CURRENT_BINARY_DIR}/../include")
link_directories("${CMAKE_CURRENT_BINARY_DIR}/../lib")

## Compile all example codes, including ds202_sample1.c and ds202_sample2.c
## Run a for loop for each C source file
## All executables will appear in build/examples directory.
foreach(src suftest mksary sasearch bwt unbwt ds202_sample1 ds202_sample2)
  add_executable(${src} ${src}.c)
  target_link_libraries(${src} divsufsort)
endforeach(src)

add_executable(hw3 hw3.cpp)
target_link_libraries(hw3 divsufsort)

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## 
## You can put your code in the "examples" directory of the project.
## Suppose your code file is called as ds202_homework.cpp, then add the following two 
## lines at the bottom of this file.
## 
## add_executable(ds202_homework ds202_homework.cpp)
## target_link_libraries(ds202_homework divsufsort)
## 
## After adding the two lines, go to build directory of your project. Run cmake
## and make commands again as communicated in README file. After a successful compile,
## you should see an executable named "ds202_homework" in the build/examples folder.
## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## 
