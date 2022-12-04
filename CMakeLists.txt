cmake_minimum_required(VERSION 3.24)

if(COMMAND cmake_policy)
cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

# Project Name
project(Almach)

# Set Executable Output in /bin/
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# Add lib Subdir
add_subdirectory(lib)

# Get Source Files
aux_source_directory(src SRC_LIST_1)
aux_source_directory(src/mode SRC_LIST_2)
aux_source_directory(src/function SRC_LIST_3)

# Set Header Files Path
include_directories(inc)
include_directories(lib/SOFA/src)
include_directories(lib/minIni/src)

# Assign Output Target
add_executable(almach ${SRC_LIST_1} ${SRC_LIST_2} ${SRC_LIST_3})

# Add Link Library
target_link_libraries(almach SOFA)
target_link_libraries(almach m)
target_link_libraries(almach minIni)