
# Shared library

add_library(fishy SHARED Fishy.cpp Sharky.cpp)
add_library(${PROJECT_NAME}::fishy ALIAS fishy)

target_include_directories(fishy
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

set(FISHY_HEADERS
  "${PROJECT_SOURCE_DIR}/include/Fishy.hpp"
  "${PROJECT_SOURCE_DIR}/include/Sharky.hpp")

set_target_properties(fishy
  PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION 1
  PUBLIC_HEADER "${FISHY_HEADERS}"
  EXPORT_NAME "${PROJECT_NAME}"
  )

install(TARGETS fishy
  EXPORT "${PROJECT_NAME}"
  LIBRARY
    COMPONENT dev
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE
    COMPONENT dev
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME
    COMPONENT runtime
    DESTINATION ${CMAKE_INSTALL_BINDIR}
  PUBLIC_HEADER
    COMPONENT dev
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/test-project)


# Executable

set(PROG_FILES main.cpp)
add_executable(sturdy-hello ${PROG_FILES})
target_link_libraries(sturdy-hello fishy)
set_target_properties(sturdy-hello PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

install(TARGETS sturdy-hello
    RUNTIME
    COMPONENT runtime
    DESTINATION ${CMAKE_INSTALL_BINDIR})

get_directory_property(STURDY_ALL_TARGETS BUILDSYSTEM_TARGETS)
set(STURDY_ALL_TARGETS "${STURDY_ALL_TARGETS}" CACHE STRING "All Targets")
