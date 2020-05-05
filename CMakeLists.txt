cmake_minimum_required(VERSION 3.0.0)
project(async VERSION 0.1.0)

include_directories("src/" "include/")

find_package(Threads REQUIRED)

set(SOURCES src/async.cpp src/owner.cpp src/observer.cpp src/output_observer.cpp src/record_observer.cpp)
set(HEADERS include/async.h include/owner.h include/observer.h include/output_observer.h include/record_observer.h)

add_executable(test_async main.cpp)

add_library(async ${SOURCES} ${HEADERS})

set_target_properties(
  test_async PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra;"
)

set_target_properties(
  async PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra;"
)

target_link_libraries(test_async
        async
        Threads::Threads
        )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
