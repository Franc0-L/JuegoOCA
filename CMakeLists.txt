cmake_minimum_required(VERSION 3.16)

project(JuegoOCA VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Juego
    ${CMAKE_CURRENT_SOURCE_DIR}/Juego/Casillas
    ${CMAKE_CURRENT_SOURCE_DIR}/Saves
    ${CMAKE_CURRENT_SOURCE_DIR}/Interfaz
)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(JuegoOCA
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        juego/dado.h juego/dado.cpp
        juego/jugador.h juego/jugador.cpp
        juego/casilla.h juego/casilla.cpp
        juego/casillanormal.h juego/casillanormal.cpp
        juego/casillaoca.h juego/casillaoca.cpp
        juego/casillapuente.h juego/casillapuente.cpp
        juego/casillaposada.h juego/casillaposada.cpp
        juego/casillapozo.h juego/casillapozo.cpp
        juego/casillalaberinto.h juego/casillalaberinto.cpp
        juego/casillacarcel.h juego/casillacarcel.cpp
        juego/casillacalavera.h juego/casillacalavera.cpp
        juego/tablero.h juego/tablero.cpp

        juego/juegooca.h juego/juegooca.cpp
        saves/gestorpartidas.h saves/gestorpartidas.cpp
        lectorarchivos.h lectorarchivos.cpp
        interfaz/menuprincipal.h interfaz/menuprincipal.cpp interfaz/menuprincipal.ui
        interfaz/menuconfiguracion.h interfaz/menuconfiguracion.cpp interfaz/menuconfiguracion.ui
        interfaz/menujuego.h interfaz/menujuego.cpp interfaz/menujuego.ui
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET JuegoOCA APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(JuegoOCA SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(JuegoOCA
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(JuegoOCA PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.JuegoOCA)
endif()
set_target_properties(JuegoOCA PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS JuegoOCA
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(JuegoOCA)
endif()
