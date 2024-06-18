QT       += core gui multimedia multimediawidgets sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/app/main.cpp \
    src/app/main_window.cpp \
    src/core/Database/databasemanager.cpp \
    src/core/Database/playlistdataaccess.cpp \
    src/core/Database/userdataaccess.cpp \
    src/ui/components/addtoplaylistdialog.cpp \
    src/ui/components/album.cpp \
    src/ui/components/artist.cpp \
    src/ui/components/chatmanager.cpp \
    src/ui/components/clickablelabel.cpp \
    src/ui/components/footer_components.cpp \
    src/ui/components/header_components.cpp \
    src/ui/components/icon.cpp \
    src/ui/components/new_playlist_create.cpp \
    src/ui/components/newplaylist.cpp \
    src/ui/components/play.cpp \
    src/ui/components/playlist.cpp \
    src/ui/components/songinfo.cpp \
    src/ui/components/songlist.cpp \
    src/ui/components/user.cpp \
    src/ui/views/admin/adminwindow.cpp \
    src/ui/views/central_area/central_area_view.cpp \
    src/ui/views/footer/footer_view.cpp \
    src/ui/views/header/header_view.cpp \
    src/ui/views/left_sidebar/left_sidebar_view.cpp \
    src/ui/views/right_sidebar/right_sidebar_view.cpp \
    src/ui/views/login/generator.cpp \
    src/ui/views/login/newaccount.cpp \
    src/ui/views/login/welcome.cpp \
    src/viewmodels/usercentralareaviewmodel.cpp



HEADERS += \
    src/app/main_window.h \
    src/core/Database/databasemanager.h \
    src/core/Database/playlistdataaccess.h \
    src/core/Database/userdataaccess.h \
    src/ui/components/addtoplaylistdialog.h \
    src/ui/components/album.h \
    src/ui/components/artist.h \
    src/ui/components/chatmanager.h \
    src/ui/components/clickablelabel.h \
    src/ui/components/footer_components.h \
    src/ui/components/header_components.h \
    src/ui/components/icon.h \
    src/ui/components/new_playlist_create.h \
    src/ui/components/newplaylist.h \
    src/ui/components/play.h \
    src/ui/components/playlist.h \
    src/ui/components/songinfo.h \
    src/ui/components/songlist.h \
    src/ui/components/user.h \
    src/ui/views/admin/adminwindow.h \
    src/ui/views/central_area/central_area_view.h \
    src/ui/views/footer/footer_view.h \
    src/ui/views/header/header_view.h \
    src/ui/views/left_sidebar/left_sidebar_view.h \
    src/ui/views/right_sidebar/right_sidebar_view.h \
    src/ui/views/login/generator.h \
    src/ui/views/login/newaccount.h \
    src/ui/views/login/welcome.h \
    src/viewmodels/usercentralareaviewmodel.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
