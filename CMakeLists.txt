# Works with 3.11 and tested through 3.20
cmake_minimum_required(VERSION 3.11...3.20)

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

add_subdirectory(src)
add_subdirectory(cli-app)
