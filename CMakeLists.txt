cmake_minimum_required (VERSION 3.0.0)
project (OX-L-T)

add_subdirectory(../OX-L-T/framework)
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OXYGINE_CXX_FLAGS}")

# Don't forget to include misc. additional files
file (GLOB APP_SOURCES source/Main.cpp source/Engine.cpp source/Scene.cpp source/Unit.cpp source/Object.cpp source/Figure.cpp source/Tile.cpp source/Grid.cpp)
file (GLOB APP_HEADERS source/Engine.h source/Scene.h source/Unit.h source/Object.h source/Figure.h source/Tile.h source/Grid.h source/Settings.h)

add_executable(OX-L-T ${APP_HEADERS} ${APP_SOURCES})
target_link_libraries(OX-L-T ${OXYGINE_CORE_LIBS})

if (WIN32)
	set_target_properties(OX-L-T PROPERTIES WIN32_EXECUTABLE TRUE)
endif(WIN32)

if (EMSCRIPTEN)
	SET(CMAKE_EXECUTABLE_SUFFIX ".html")	
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s NO_EXIT_RUNTIME=1 -s WASM=0 -s WARN_ON_UNDEFINED_SYMBOLS=1 --memory-init-file 0 -s TOTAL_MEMORY=50331648 -s FORCE_FILESYSTEM=1")
	em_link_pre_js(OX-L-T  ${OXYGINE_JS_LIBRARIES}  ${CMAKE_CURRENT_SOURCE_DIR}/data.js)
endif(EMSCRIPTEN)