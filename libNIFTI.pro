#-------------------------------------------------
#
# Project created by QtCreator 2017-08-30T22:04:15
#
#-------------------------------------------------

QT       -= gui

TARGET = libNIFTI
TEMPLATE = lib

# Include ZLIB files and link dynamic libraries
# (This is used in NIFTI library)
LIBS += -LD:/DevelLibs/zlib-1.2.8/build/lib \
        -lzlib

# Include QuaZip files for handling Zip files
INCLUDEPATH += 'D:/DevelLibs/quazip-0.7.3/build/include'
DEPENDPATH += 'D:/DevelLibs/quazip-0.7.3/build/include'

CONFIG(debug, debug|release): LIBS += -LD:/DevelLibs/quazip-0.7.3/build/lib \
        -lquazipd

CONFIG(release, debug|release): LIBS += -LD:/DevelLibs/quazip-0.7.3/build/lib \
        -lquazip

CONFIG(debug, debug|release) {
     mac: TARGET = $$join(TARGET,,,_debug)
     win32: TARGET = $$join(TARGET,,,d)
}

# You'll need to define this one manually if using a build system other
# than qmake or using QuaZIP sources directly in your project.
CONFIG(staticlib): DEFINES += LIBNIFTI_STATIC

DEFINES += LIBNIFTI_LIBRARY

SOURCES += libnifti.cpp \
    nifti1_io.c \
    znzlib.c

HEADERS += libnifti.h\
        libnifti_global.h \
    nifti1.h \
    nifti1_io.h \
    znzlib.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
