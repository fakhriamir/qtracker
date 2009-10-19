TEMPLATE = app
TARGET = qTracker
QT += core \
    gui \
    xml
HEADERS += widgets/qgaugewidget.h \
    widgets/qmapwidget.h \
    images/ui.h \
    mobility/location_global.h \
    mobility/xqlocation_s60_p.h \
    mobility/xqlocation.h \
    widgets/qaltitudewidget.h \
    widgets/qclockwidget.h \
    widgets/qheadingwidget.h \
    widgets/qsatviewwidget.h \
    widgets/qspeedwidget.h \
    windows/qdashwindow.h
FORMS += 
RESOURCES += 
symbian { 
    TARGET.UID3 = 0xEA82CEF3
    LIBS += -llbs
    TARGET.CAPABILITY = Location \
        LocalServices \
        NetworkServices \
        PowerMgmt \
        ProtServ \
        ReadDeviceData \
        ReadUserData \
        SurroundingsDD \
        SwEvent \
        TrustedUI \
        UserEnvironment \
        WriteDeviceData \
        WriteUserData
    ICON = images/icon.svg
    UiFiles.sources += images/clock.svg \
        images/compass.svg \
        images/compassneedle.svg \
        images/longhand.svg \
        images/satview.svg \
        images/secondhand.svg \
        images/shorthand.svg \
        images/speed10.svg \
        images/speed200.svg \
        images/style.css \
        images/speedneedle.svg \
        images/map.svg \
        images/splash.png
    UiFiles.path = ./ui
    DEPLOYMENT += UiFiles
    VERSION = 1.0.3
    TARGET.EPOCHEAPSIZE = 0x20000 \
        0x1c00000
    TARGET.EPOCSTACKSIZE += 0x14000
}
SOURCES += widgets/qgaugewidget.cpp \
    widgets/qmapwidget.cpp \
    images/ui.cpp \
    mobility/xqlocation_s60_p.cpp \
    mobility/xqlocation.cpp \
    widgets/qaltitudewidget.cpp \
    widgets/qclockwidget.cpp \
    widgets/qheadingwidget.cpp \
    widgets/qsatviewwidget.cpp \
    widgets/qspeedwidget.cpp \
    windows/qdashwindow.cpp \
    main.cpp