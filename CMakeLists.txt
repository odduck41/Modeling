cmake_minimum_required(VERSION 3.29)
project(Modeling)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH "C:/Qt/6.6.1/mingw_64/lib/cmake")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_executable(${PROJECT_NAME} src/main.cpp
        include/Modeling.h
        src/Modeling.cpp
        src/Application.cpp
        include/Application.h
        src/QSFMLCanvas.cpp
        include/QSFMLCanvas.h
        src/Canvas.cpp
        include/Canvas.h)

if (WIN32)
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
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)


if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()



add_link_options(-static -static-libgcc -static-libstdc++)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE true)
endif()