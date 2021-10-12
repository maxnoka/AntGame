set( SOURCES_LIST 
  "Camera.cpp"
  "Game.cpp"
  "InputHandler.cpp"
  "main.cpp"
  "TextRenderer.cpp"
  "TreeRenderer.cpp"
  "WorldObjectRenderer.cpp"
)

add_executable(sdl_app ${SOURCES_LIST})
target_include_directories(sdl_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(sdl_app PRIVATE cxx_std_17)
target_compile_definitions(sdl_app PRIVATE ASSET_PATH="${PROJECT_SOURCE_DIR}/assets/")

target_link_libraries(sdl_app PRIVATE antgame_library) 

#####################################
# External Dependencies
#####################################
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_gfx REQUIRED)
target_link_libraries(sdl_app PRIVATE SDL2::Main SDL2::TTF SDL2::GFX)
target_link_libraries(sdl_app PRIVATE scopeguard) 
