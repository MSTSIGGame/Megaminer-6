INCLUDEPATH += ./parser \
    ./parser/sexp
win32:LIBS += ./parser/sexp/sexpXP.a
else:LIBS += ./parser/sexp/sexp.a
SOURCES += main.cpp \
    visualizerWindow.cpp \
    gameboardWidget.cpp \
    gameboardTextureFxns.cpp \
    gameboardSpriteFxns.cpp \
    gameboardAnimationFxns.cpp \
    gameboardOtherRenderFxns.cpp
SOURCES += drawGLFont.cpp
SOURCES += ./parser/parser.cpp
SOURCES += ./parser/structures.cpp
SOURCES += texture.cpp \
    statsDialog.cpp \
    config.cpp \
    visettings.cpp \
    log.cpp
HEADERS += visualizerWindow.h \
    gameboardWidget.h \
    log.h
HEADERS += texture.h \
    statsDialog.h \
    config.h \
    visettings.h
HEADERS += drawGLFont.h
CONFIG += debug
QT += opengl
SUBDIRS += parser
