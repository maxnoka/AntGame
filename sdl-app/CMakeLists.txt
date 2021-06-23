set( SOURCES_LIST 
  "Camera.cpp"
  "Game.cpp"
  "InputHandler.cpp"
  "main.cpp"
)

add_executable(sdl_app ${SOURCES_LIST})
target_include_directories(sdl_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(sdl_app PRIVATE cxx_std_17)
target_link_libraries(sdl_app PRIVATE antgame_library) 

#####################################
# External Dependencies
#####################################
find_package(SDL2 REQUIRED)
target_link_libraries(sdl_app PRIVATE SDL2::Main)
