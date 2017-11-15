QT += core
QT -= gui

TARGET = HBXOsgDisElement
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    RedEleGeo.cpp \
    osgallkindtext.cpp \
    axisfirstheaven.cpp

#INCLUDEPATH += /usr/include/
#LIBS += -L/usr/lib/ -losg -losgDB -losgUtil -losgViewer -losgGA -lOpenThreads -losgText
INCLUDEPATH += C:/msys64/mingw64/include
LIBS += C:/msys64/mingw64/lib/libosg.dll.a
LIBS += C:/msys64/mingw64/lib/libosgViewer.dll.a
LIBS += C:/msys64/mingw64/lib/libosgDB.dll.a
LIBS += C:/msys64/mingw64/lib/libosgGA.dll.a
LIBS += C:/msys64/mingw64/lib/libosgText.dll.a
LIBS += C:/msys64/mingw64/lib/libosgUtil.dll.a
LIBS += C:/msys64/mingw64/lib/libOpenThreads.dll.a

HEADERS += \
    RedEleGeo.h \
    osgallkindtext.h \
    axisfirstheaven.h \
    initialInclude.h
