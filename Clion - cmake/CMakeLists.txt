cmake_minimum_required(VERSION 3.24)
project(CPP_projekt_AGH_main)

set(CMAKE_CXX_STANDARD 14)

include_directories(functions)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

file(COPY "images" DESTINATION ${EXECUTABLE_OUTPUT_PATH})
file(COPY "font" DESTINATION ${EXECUTABLE_OUTPUT_PATH})
file(COPY "highscores.txt" DESTINATION ${EXECUTABLE_OUTPUT_PATH})

# Pobierz SFML za pomocą FetchContent
include(FetchContent)
FetchContent_Declare(
        SFML
        URL https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip
)
FetchContent_MakeAvailable(SFML)

# Dodaj ścieżki do plików nagłówkowych SFML
set(SFML_INCLUDE_DIR "${CMAKE_BINARY_DIR}/_deps/sfml-src/include")
include_directories(${SFML_INCLUDE_DIR})

# Dodaj ścieżki do bibliotek SFML
set(SFML_LIBRARY_DIR "${CMAKE_BINARY_DIR}/_deps/sfml-src/lib")
link_directories(${SFML_LIBRARY_DIR})

add_executable(CPP_projekt_AGH_main
        functions/game.cpp
        functions/game.hpp
        main.cpp)


target_link_libraries(CPP_projekt_AGH_main sfml-graphics sfml-window sfml-system)
