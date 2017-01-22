#-------------------------------------------------
#
# Project created by QtCreator 2017-01-07T13:17:16
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = VisorOsciloscopio
TEMPLATE = app


##CONFIGURACIONEs DE ACUERDO
##A CADA PLATAFORMA
macx{
    QMAKE_MACOSX_DEPLOYMENT_TARGET=10.12
    CONFIG += c++14
    QMAKE_CXXFLAGS += -stdlib=libc++
    QMAKE_MAC_SDK = macosx10.12
}
ios{
    CONFIG += c++14
    QMAKE_CXXFLAGS += -stdlib=libc++
}
android{
    CONFIG += c++14
    INSTALLS += deployment
}
linux{
    QMAKE_CXXFLAGS += -std=c++1y
    CONFIG += c++14
}
win32-msvc2015{
    CONFIG += c++14
    LIBS +=   -lshell32
    LIBS += -lshell32 -loleaut32 -lole32
}
win32-g++{
    QMAKE_CXXFLAGS += -std=c++1y
    CONFIG += c++14
    LIBS +=   -lshell32
    LIBS += -lshell32 -loleaut32 -lole32 -lglu32 -lopengl32
}



SOURCES += main.cpp \
    vistaosciloscopio.cpp \
    config.cpp \
    cambioparametros.cpp \
    configuraacionred.cpp \
    ventanavisualizacion.cpp \
    comm.cpp

HEADERS  += \
    vistaosciloscopio.hpp \
    configuraacionred.hpp \
    ventanavisualizacion.hpp \
    glchunk.hpp

FORMS    += mainwindow.ui \
    vistaosciloscopio.ui \
    configuraacionred.ui

RESOURCES += \
    recursos.qrc
