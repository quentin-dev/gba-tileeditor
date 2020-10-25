# cmake_minimum_required(VERSION 3.14)

# project(gba-tileeditor)

# set(CMAKE_CXX_STANDARD 17)

# Otherwise headers are not processed by AUTOMOC
# cmake_policy(SET CMP0100 NEW)


set(CMAKE_AUTOMOC ON)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS "forms")
# set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets PrintSupport REQUIRED)

set(TARGET ${CMAKE_PROJECT_NAME})

set(SOURCES
    "src/editorwindow.cc"
    "src/map.cc"
    "src/mapview.cc"
    "src/newdialog.cc"
    "src/paletteview.cc"
)

set(FORMS
    "forms/mainwindow.ui"
    "forms/newmap.ui"
)

set(RESOURCE
    "icons.qrc"
)

set(HEADERS
    "src/command.hh"
    "src/editorwindow.hh"
    "json.hpp"
    "map.hh"
    "mapview.hh"
    "newdialog.hh"
    "paletteview.hh"
    "saveheadercommand.hh"
    "savejsoncommand.hh"
    "savesourcescommand.hh"
)

set(INCLUDES
    "src"
)

# qt5_wrap_ui(UI_HEADERS ${FORMS})

add_executable(${TARGET} "src/main.cc")
target_sources(${TARGET} PRIVATE ${SOURCES} ${RESOURCE})
target_compile_options(${TARGET} PRIVATE -Wall -Wextra)
target_include_directories(${TARGET} PRIVATE ${INCLUDES})

target_link_libraries(${TARGET} Qt5::Widgets Qt5::PrintSupport)
