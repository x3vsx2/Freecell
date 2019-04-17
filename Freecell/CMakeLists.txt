cmake_minimum_required(VERSION 3.13)
project(Freecell)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        Freecell.cpp
        pch.cpp pch.h
        FenetrePrincipale.cpp FenetrePrincipale.h
        Carte.cpp Carte.h PileCarte.cpp PileCarte.h
        Bouton.cpp Bouton.h)

add_executable(Freecell ${SOURCE_FILES})

# You can alter these according to your needs, e.g if you don't need to display images - set(YOU_NEED_X11 0)
set(YOU_NEED_X11 1)
set(YOU_NEED_PNG 1)
set(YOU_NEED_JPG 0)
set(THREADS_PREFER_PTHREAD_FLAG ON)

if (${YOU_NEED_X11} EQUAL 1)
    message(STATUS "Looking for X11...")
    find_package(X11 REQUIRED)
    find_package(Threads REQUIRED)
    target_link_libraries(Freecell Threads::Threads)
    include_directories(${X11_INCLUDE_DIR})
    target_link_libraries(Freecell ${X11_LIBRARIES})
else ()
    target_compile_definitions(Freecell PRIVATE cimg_display=0)
endif ()

if (${YOU_NEED_JPG} EQUAL 1)
    message(STATUS "Looking for libjpg...")
    find_package(JPEG REQUIRED)
    include_directories(${JPEG_INCLUDE_DIR})
    target_link_libraries(Freecell ${JPEG_LIBRARY})
    target_compile_definitions(Freecell PRIVATE cimg_use_jpeg=1)
endif ()

if (${YOU_NEED_PNG} EQUAL 1)
    message(STATUS "Looking for libpng...")
    find_package(PNG REQUIRED)
    include_directories(${PNG_INCLUDE_DIR})
    target_link_libraries(Freecell ${PNG_LIBRARY})
    target_compile_definitions(Freecell PRIVATE cimg_use_png=1)
endif ()