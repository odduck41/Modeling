cmake_minimum_required(VERSION 3.29)
project(Modeling)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} src/main.cpp
        include/Modeling.h
        src/Modeling.cpp
        include/Application.h
        src/Application.cpp
        include/Canvas.h
        src/Canvas.cpp
        include/Drawable.h
        src/Drawable.cpp
        include/QSFMLCanvas.h
        src/QSFMLCanvas.cpp
)

if (WIN32)
    set(CMAKE_PREFIX_PATH "C:/Qt/6.6.1/mingw_64/lib/cmake")
    message(STATUS "OS is Windows")
    # You should download sfml with vcpkg in Clion.
    # Or you can change this path to directory where SMFLConfig.cmake

    set(SFML_PATH "$ENV{USERPROFILE}/.vcpkg-clion/vcpkg/packages/sfml_x64-mingw-dynamic")
    set(SFML_DIR "${SFML_PATH}/share/sfml")

#    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E copy_if_different
##                "${SFML_PATH}/debug/bin/sfml-audio-d-2.dll"
#                "${SFML_PATH}/debug/bin/sfml-graphics-d-2.dll"
##                "${SFML_PATH}/debug/bin/sfml-network-d-2.dll"
#                "${SFML_PATH}/debug/bin/sfml-system-d-2.dll"
#                "${SFML_PATH}/debug/bin/sfml-window-d-2.dll"
#                "${CMAKE_CURRENT_BINARY_DIR}"
#        )
#    else()
#        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E copy_if_different
##                "${SFML_PATH}/bin/sfml-audio-2.dll"
#                "${SFML_PATH}/bin/sfml-graphics-2.dll"
##                "${SFML_PATH}/bin/sfml-network-2.dll"
#                "${SFML_PATH}/bin/sfml-system-2.dll"
#                "${SFML_PATH}/bin/sfml-window-2.dll"
#                "${CMAKE_CURRENT_BINARY_DIR}"
#        )
#    endif ()

else (LINUX)
    message(STATUS "OS is Linux-like")
endif(WIN32)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
message(STATUS "SFML is loaded")

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
message(STATUS "Qt is loaded")

target_link_libraries(${PROJECT_NAME} PRIVATE
        sfml-system
        sfml-network
        sfml-graphics
        sfml-window
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

