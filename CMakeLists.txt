# Works with 3.11 and tested through 3.20
cmake_minimum_required(VERSION 3.14...3.20)

project(
  AntGame
  VERSION 0.1
  DESCRIPTION "A game/simulator of ants"
  LANGUAGES CXX)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_EXTENSIONS OFF)

  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  include(CTest)
  include(FetchContent)
endif()

# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

add_subdirectory(extern/easyloggingpp)

add_subdirectory(src)
add_subdirectory(cli-app)
add_subdirectory(sdl-app)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
   AND BUILD_TESTING)

  option(PACKAGE_TESTS "Build the tests" ON)
  if(PACKAGE_TESTS)
      enable_testing()
      include(GoogleTest)
      add_subdirectory(tests)
  endif()
endif()
