# Generated from securesocketclient.pro.

cmake_minimum_required(VERSION 3.14)
project(securesocketclient LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(INSTALL_EXAMPLEDIR "examples/network/securesocketclient")

find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS Network)
find_package(Qt6 COMPONENTS Widgets)

add_qt_gui_executable(securesocketclient
    certificateinfo.cpp certificateinfo.h certificateinfo.ui
    main.cpp
    sslclient.cpp sslclient.h sslclient.ui
    sslerrors.ui
)
target_link_libraries(securesocketclient PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Network
    Qt::Widgets
)


# Resources:
set(securesocketclient_resource_files
    "encrypted.png"
)

qt6_add_resources(securesocketclient "securesocketclient"
    PREFIX
        "/"
    FILES
        ${securesocketclient_resource_files}
)

install(TARGETS securesocketclient
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
