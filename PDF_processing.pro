QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = PDF_processing
TEMPLATE = app
#CONFIG += console c++11
#CONFIG -= app_bundle
#CONFIG -= qt

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    processall.cpp


defineTest(copyToDestdir) {
    files = $$1

    for(FILE, files) {
        DDIR = $$OUT_PWD

        # Replace slashes in paths with backslashes for Windows
        win32:FILE ~= s,/,\\,g
        win32:DDIR ~= s,/,\\,g

        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t)
    }

    export(QMAKE_POST_LINK)
}

copyToDestdir($$PWD/pdftotext)
copyToDestdir($$PWD/stanford-ner.jar)
copyToDestdir($$PWD/class.crf.ser.gz)

HEADERS += \
    paper.h \
    stringrelative.h \
    txt.h \
    findinfo.h \
    mainwindow.h \
    listitem.h \
    processall.h

FORMS += \
    mainwindow.ui
