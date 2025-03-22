QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    action.cpp \
    advancement.cpp \
    auctionview.cpp \
    bank.cpp \
    bankview.cpp \
    board.cpp \
    boardview.cpp \
    card.cpp \
    cardview.cpp \
    company.cpp \
    dice.cpp \
    diceview.cpp \
    game.cpp \
    gamerules.cpp \
    main.cpp \
    gameview.cpp \
    menuscene.cpp \
    payment.cpp \
    player.cpp \
    playerview.cpp \
    prisonview.cpp \
    propertyview.cpp \
    savegame.cpp \
    station.cpp \
    street.cpp \
    tile.cpp \
    tileview.cpp \
    tokenview.cpp

HEADERS += \
    Color.h \
    action.h \
    advancement.h \
    auctionview.h \
    bank.h \
    bankview.h \
    board.h \
    boardview.h \
    card.h \
    cardtype.h \
    cardview.h \
    company.h \
    dice.h \
    diceview.h \
    figure.h \
    game.h \
    gamerules.h \
    gameview.h \
    menuscene.h \
    payment.h \
    player.h \
    playerview.h \
    prisonview.h \
    propertyview.h \
    savegame.h \
    station.h \
    street.h \
    tile.h \
    tileview.h \
    tokenview.h \
    transactiontype.h

FORMS += \
    gameview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
