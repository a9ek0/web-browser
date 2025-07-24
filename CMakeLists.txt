cmake_minimum_required(VERSION 3.19)
project(WebBrowser LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "F:/Qt/6.9.1/msvc2022_64" )

find_package(Qt6 6.9.1 REQUIRED COMPONENTS Core Widgets WebEngineWidgets)

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
