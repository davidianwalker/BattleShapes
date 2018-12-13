set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

link_directories(${SDL2_LIBRARY_DIRS} ${SDL2IMAGE_LIBRARY_DIRS} ${SDL2TTF_LIBRARY_DIRS})

add_executable(battleshapes BattleShapes.cpp bullet.cpp game_rect.cpp player.cpp screen.cpp sdl_callbacks.cpp attacking_shape.cpp)
target_include_directories(battleshapes PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL_IMAGE_INCLUDE_DIRS} ${SDL_TTF_INCLUDE_DIRS})
target_link_libraries(battleshapes ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})

# copy resources to build output directory
add_custom_command(TARGET battleshapes PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/BattleShapes/resources $<TARGET_FILE_DIR:battleshapes>/resources)
