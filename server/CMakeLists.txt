cmake_minimum_required(VERSION 3.7.0)

project(Central_Server)

set (CMAKE_C_FLAGS "-D_GNU_SOURCE -Wall -std=c99")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_BUILD_TYPE Debug)

# build button_process
add_executable(centralserver "")

# target_link_libraries(centralserver PUBLIC ${LIBS})
target_link_libraries(centralserver PUBLIC comm)

target_sources(centralserver
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/src/main.c
  )

target_include_directories(centralserver 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/include  
  )


install(TARGETS centralserver DESTINATION bin)
# install(TARGETS  util ipc comm database collection json LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
