QT += widgets

TEMPLATE = lib

CONFIG += warn_on plugin link_pkgconfig c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    htmlplaylist.cpp \
    htmlplaylistfactory.cpp \
    settingsdialog.cpp \
    template.cpp \
    templatebase.cpp \
    templateunstyledhtml.cpp \
    templatewinamp.cpp
HEADERS += \
    htmlplaylist.h \
    htmlplaylistfactory.h \
    settingsdialog.h \
    template.h \
    templatebase.h \
    templateunstyledhtml.h \
    templatewinamp.h

QMAKE_CLEAN += lib$${TARGET}.so

unix {
    PKGCONFIG += qmmp

    QMMP_PREFIX = $$system(pkg-config qmmp --variable=prefix)
    PLUGIN_DIR = $$system(pkg-config qmmp --variable=plugindir)/General
    # for some reason plugindir is "/usr//usr/lib64/qmmp-1.4" on my box :/
    PLUGIN_DIR = $$replace(PLUGIN_DIR, /usr//usr/, /usr/)
    LOCAL_INCLUDES = $${QMMP_PREFIX}/include
    LOCAL_INCLUDES -= $$QMAKE_DEFAULT_INCDIRS
    INCLUDEPATH += $$LOCAL_INCLUDES

    plugin.path = $${PLUGIN_DIR}
    plugin.files = lib$${TARGET}.so
    INSTALLS += plugin
}

FORMS += \
    settingsdialog.ui
