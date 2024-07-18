cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(appmap-test LANGUAGES CXX)

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)

CPMAddPackage(
  GITHUB_REPOSITORY eranpeer/FakeIt
  GIT_TAG 2.4.0
)

target_link_libraries(appmap-instrumentation PRIVATE FakeIt::FakeIt-doctest)

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(appmap-test ${sources})
target_link_libraries(appmap-test doctest appmap-instrumentation FakeIt::FakeIt-doctest)

set_target_properties(appmap-test PROPERTIES CXX_STANDARD 20)

# enable compiler warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  target_compile_options(appmap-instrumentation PUBLIC -Wall -pedantic -Wextra -Werror)
elseif(MSVC)
  target_compile_options(appmap-instrumentation PUBLIC /W4 /WX)
  target_compile_definitions(appmap-instrumentation PUBLIC DOCTEST_CONFIG_USE_STD_HEADERS)
endif()

enable_testing()

include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(appmap-test)

if(ENABLE_TEST_COVERAGE)
  target_compile_options(appmap-instrumentation PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(appmap-instrumentation PUBLIC -fprofile-arcs -ftest-coverage)
endif()
