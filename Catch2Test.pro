TEMPLATE = app
QT += gui widgets core qml quick sql concurrent testlib

CONFIG += c++11

isEmpty(CATCH_INCLUDE_DIR): CATCH_INCLUDE_DIR=$$(CATCH_INCLUDE_DIR)
!isEmpty(CATCH_INCLUDE_DIR): INCLUDEPATH *= $${CATCH_INCLUDE_DIR}

isEmpty(CATCH_INCLUDE_DIR): {
    message("CATCH_INCLUDE_DIR is not set, assuming Catch2 can be found automatically in your system")
}

INCLUDEPATH += "./supercollider/editors/sc-ide/widgets/util" \
               "./supercollider/editors/sc-ide/widgets"

HEADERS += ./supercollider/editors/sc-ide/widgets/util/color_widget.hpp \
           ./supercollider/editors/sc-ide/widgets/goto_line_tool.hpp

SOURCES += main.cpp \
    tst_tc01.cpp \
    tst_tc02.cpp
