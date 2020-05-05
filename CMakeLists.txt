cmake_minimum_required(VERSION 3.5)

set( PRO_PATCH $ENV{TRAVIS_BUILD_NUMBER})
if (NOT "${PRO_PATCH}")
  set(PRO_PATCH "1")
endif (NOT "${PRO_PATCH}")

project(async VERSION 0.0.${PRO_PATCH})

include_directories("src/" "include/")

find_package(Threads REQUIRED)

set(SOURCES src/async.cpp src/owner.cpp src/observer.cpp src/output_observer.cpp src/record_observer.cpp)
set(HEADERS include/async.h include/owner.h include/observer.h include/output_observer.h include/record_observer.h)

add_library(async ${SOURCES} ${HEADERS})

set_target_properties(
  async PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra;"
)

install(TARGETS async DESTINATION lib)

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_CONTACT mr.alligator@yandex.ru)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
include(CPack)
