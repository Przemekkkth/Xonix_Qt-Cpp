greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    game.cpp \
    gamescene.cpp \
    main.cpp \
    view.cpp

HEADERS += \
    enemy.h \
    game.h \
    gamescene.h \
    view.h

RESOURCES += \
    resource.qrc
