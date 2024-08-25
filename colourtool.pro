QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basecolourwidget.cpp \
    colourgallerywidget.cpp \
    colourgrid.cpp \
    colourgridwidget.cpp \
    colourrectanglewidget.cpp \
    coloursamplerdelegate.cpp \
    colourslider.cpp \
    coloursliderbar.cpp \
    coloursliderindicator.cpp \
    colourwheel.cpp \
    colourwheeldisplay.cpp \
    colourwheelindicators.cpp \
    favouriteitemwidget.cpp \
    favouriteswidget.cpp \
    frameseperator.cpp \
    hslcoloursampler.cpp \
    main.cpp \
    mainwindow.cpp \
    rgbcoloursampler.cpp

HEADERS += \
    basecolourwidget.h \
    colourgallerywidget.h \
    colourgrid.h \
    colourgridwidget.h \
    colourrectanglewidget.h \
    coloursamplerdelegate.h \
    colourslider.h \
    coloursliderbar.h \
    coloursliderindicator.h \
    colourwheel.h \
    colourwheeldisplay.h \
    colourwheelindicators.h \
    favouriteitemwidget.h \
    favouriteswidget.h \
    frameseperator.h \
    hslcoloursampler.h \
    mainwindow.h \
    rgbcoloursampler.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
