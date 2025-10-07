QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    interfaz/menuconfiguracion.cpp \
    interfaz/menujuego.cpp \
    interfaz/menupartida.cpp \
    interfaz/menuprincipal.cpp \
    juego/casilla.cpp \
    juego/casillacalavera.cpp \
    juego/casillacarcel.cpp \
    juego/casillajardin.cpp \
    juego/casillalaberinto.cpp \
    juego/casillanormal.cpp \
    juego/casillaoca.cpp \
    juego/casillaposada.cpp \
    juego/casillapozo.cpp \
    juego/casillapuente.cpp \
    juego/dado.cpp \
    juego/juegooca.cpp \
    juego/jugador.cpp \
    juego/tablero.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    interfaz/menuconfiguracion.h \
    interfaz/menujuego.h \
    interfaz/menupartida.h \
    interfaz/menuprincipal.h \
    juego/casilla.h \
    juego/casillacalavera.h \
    juego/casillacarcel.h \
    juego/casillajardin.h \
    juego/casillalaberinto.h \
    juego/casillanormal.h \
    juego/casillaoca.h \
    juego/casillaposada.h \
    juego/casillapozo.h \
    juego/casillapuente.h \
    juego/dado.h \
    juego/juegooca.h \
    juego/jugador.h \
    juego/tablero.h \
    mainwindow.h

FORMS += \
    interfaz/menuconfiguracion.ui \
    interfaz/menujuego.ui \
    interfaz/menupartida.ui \
    interfaz/menuprincipal.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
