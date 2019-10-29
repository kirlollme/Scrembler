project(information)
cmake_minimum_required(VERSION 3.8)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH $ENV{QTDIR})

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Concurrent REQUIRED)
find_package(Qt5Network REQUIRED)

include_directories(${CMAKE_BINARY_DIR})

file(GLOB SOURCES
    "sources/*.h"
    "sources/*.cpp"
    "sources/mainwindow.ui"
)

foreach(source IN ITEMS ${SOURCES})
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" group_path "${source_path}")
    string(REPLACE "/" "\\" group_path "${group_path}")
    source_group("${group_path}" FILES "${source}")
endforeach()

qt5_wrap_ui(SOURCES sources/mainwindow.ui)

add_executable(information ${GUI_TYPE} ${SOURCES})

target_link_libraries(information PUBLIC Qt5::Core)
target_link_libraries(information PUBLIC Qt5::Widgets)
target_link_libraries(information PUBLIC Qt5::Gui)
target_link_libraries(information PUBLIC Qt5::Concurrent)
target_link_libraries(information PUBLIC Qt5::Network)


find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E
        env PATH="${_qt_bin_dir}" "${WINDEPLOYQT_EXECUTABLE}"
        "$<TARGET_FILE:${CMAKE_PROJECT_NAME}>"
        COMMENT "Running windeployqt..."
        )