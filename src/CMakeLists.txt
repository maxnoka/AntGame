set( HEADER_LIST
  "${AntGame_SOURCE_DIR}/include/antgame/Agent.h"
  "${AntGame_SOURCE_DIR}/include/antgame/Ant.h"
  "${AntGame_SOURCE_DIR}/include/antgame/WorldObject.h"
  "${AntGame_SOURCE_DIR}/include/antgame/WorldTree.h"
  "${AntGame_SOURCE_DIR}/include/antgame/World.h"
)

set( SOURCES_LIST 
  "${AntGame_SOURCE_DIR}/src/Agent.cpp"
  "${AntGame_SOURCE_DIR}/src/Ant.cpp"
  "${AntGame_SOURCE_DIR}/src/WorldObject.cpp"
  "${AntGame_SOURCE_DIR}/src/WorldTree.cpp"
  "${AntGame_SOURCE_DIR}/src/World.cpp"

)

add_library(antgame_library ${SOURCES_LIST} ${HEADER_LIST})
target_include_directories(antgame_library PUBLIC ../include)
target_compile_features(antgame_library PRIVATE cxx_std_17)

#####################################
# Dependencies
#####################################
find_package(Boost 1.5)
IF (Boost_FOUND)
    message(STATUS "Boost version: ${Boost_VERSION}")
    target_include_directories(antgame_library PUBLIC ${Boost_INCLUDE_DIRS})
ELSE()
    message(STATUS "Boost not found")
endif()

# for IDEs
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)

