cmake_minimum_required(VERSION 3.7.0)

project(Central_Server)

set (CMAKE_C_FLAGS "-D_GNU_SOURCE -Wall -std=c99")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_BUILD_TYPE Debug)

# if(DEFINED ARCH)
#   if(${ARCH} STREQUAL "RASPBERRY")
#     message("-- Created ${ARCH} compilation.")  
#     set (LIBS hardware interface)
#     set (FOLDER "raspberry")  
#   elseif(${ARCH} STREQUAL "PC")
#     message("-- Created ${ARCH} compilation.") 
#     set (LIBS interface)
#     set (FOLDER "pc")
#   endif()
# else()
#   message(WARNING "")
#   message("-- You must specify the ARCH variable")
#   message("-- cmake -DARCH=PC  ..")
#   message("-- or")
#   message("-- cmake -DARCH=RASPBERRY  ..")
#   message("")
#   message(FATAL_ERROR "")
# endif()

# build button_process
add_executable(centralserver "")

# target_link_libraries(centralserver PUBLIC ${LIBS})
target_link_libraries(centralserver PUBLIC comm)

target_sources(centralserver
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/server/src/main.c
  )

target_include_directories(centralserver 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/server/include  
  )

install(TARGETS centralserver DESTINATION bin)

# file(COPY config/kill_process.sh DESTINATION bin)
# file(COPY properties/mqtt_properties.json DESTINATION bin)