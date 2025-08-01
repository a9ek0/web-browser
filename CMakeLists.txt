cmake_minimum_required(VERSION 3.19)
project(WebBrowser LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "F:/Qt/6.9.1/msvc2022_64" )

find_package(Qt6 6.9.1 REQUIRED COMPONENTS Core Widgets WebEngineWidgets)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(WebBrowser
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    browsertab.h browsertab.cpp browsertab.ui
    tabwidget.h tabwidget.cpp
    controlpanel.h controlpanel.cpp controlpanel.ui
    resources.qrc
    customwebenginepage.h customwebenginepage.cpp
    historymanager.h historymanager.cpp
    historywidget.h historywidget.cpp historywidget.ui
    historyentrywidget.h historyentrywidget.cpp historyentrywidget.ui
)

set_target_properties(WebBrowser PROPERTIES
    AUTORCC ON
)

target_include_directories(WebBrowser
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(WebBrowser
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::WebEngineWidgets
)
target_link_libraries(WebBrowser PRIVATE Qt6::Core)

include(GNUInstallDirs)

install(TARGETS WebBrowser
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET WebBrowser
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
