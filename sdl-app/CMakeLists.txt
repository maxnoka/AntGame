add_executable(sdl_app main.cpp)

target_compile_features(sdl_app PRIVATE cxx_std_17)
target_link_libraries(sdl_app PRIVATE antgame_library) 

#####################################
# External Dependencies
#####################################
find_package(SDL2 REQUIRED)
target_link_libraries(sdl_app PRIVATE SDL2::Main)