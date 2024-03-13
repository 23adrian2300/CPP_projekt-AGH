cmake_minimum_required(VERSION 3.16)
project(Tetris LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )
file(COPY "images" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY "font" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY "highscore" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)



add_executable(Tetris main.cpp functions/game.cpp functions/game.h functions/constans.h functions/menu.cpp functions/menu.h functions/textures.cpp functions/textures.h)
target_link_libraries(Tetris PRIVATE sfml-graphics )
target_compile_features(Tetris PRIVATE cxx_std_23)

if(WIN32)
    add_custom_command(
        TARGET Tetris
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Tetris>
        VERBATIM)
endif()

install(TARGETS Tetris)
