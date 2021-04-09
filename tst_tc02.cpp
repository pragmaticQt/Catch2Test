#include <catch.hpp>
#include <QTest>
#include <QSignalSpy>
#include "goto_line_tool.hpp"

using namespace ScIDE;

// Version 1 - bind to internal details deeply (NOT RECOMMENDED)
TEST_CASE("GoToLineTool emits signal when Go button clicked") {
    // Arrange -
    GoToLineTool widget;
    widget.raise();
    widget.show();
    widget.setMaximum(27);
    widget.setFocus();

    // get hold of child widget - !!! fragile method
    auto spinner = widget.findChild<QSpinBox*>();
    REQUIRE(spinner != nullptr);

    auto goButton = widget.findChild<QToolButton*>();
    REQUIRE(goButton != nullptr);

    // enable tracking of activated signal from widget
    QSignalSpy activatedSpy(&widget, &GoToLineTool::activated);
    REQUIRE(activatedSpy.isValid());


    // Act - simulate typein 17 and then go
    QTest::keyClicks(spinner, "1");
    QTest::keyClicks(spinner, "7");
    goButton->click();


    // Assert
    REQUIRE(activatedSpy.count() == 1);
    QList<QVariant> arguments = activatedSpy.takeFirst();
    const QVariant &argument = arguments.at(0);
    CHECK(argument.type() == QVariant::Int);
    CHECK(argument.toInt() == 17);
}

class GoToLineToolFixture {
protected:
    GoToLineTool mGoToLineTool;
    std::unique_ptr<QSignalSpy> mActivatedSpy;

    GoToLineToolFixture() {
        mGoToLineTool.raise();
        mGoToLineTool.show();
        mGoToLineTool.setMaximum(27);
        mGoToLineTool.setFocus();

        // enable tracking of activated signal from widget
        mActivatedSpy.reset(new QSignalSpy(&mGoToLineTool, &GoToLineTool::activated));
        REQUIRE(mActivatedSpy->isValid());
    }
public:
    void typeCharToSpinner(QChar c) {
        auto spinner = mGoToLineTool.findChild<QSpinBox*>();
        REQUIRE(spinner != nullptr);
        QTest::keyClicks(spinner, c);
    }

    void setMaximumLineCount(int maxLineCount) {
        mGoToLineTool.setMaximum(maxLineCount);
    }

    void clickGoButton() {
        auto goButton = mGoToLineTool.findChild<QToolButton*>();
        REQUIRE(goButton != nullptr);
        goButton->click();
    }

    void checkActivatedSignalCount(int expectedCount) {
        REQUIRE(mActivatedSpy->count() == expectedCount);
    }

    void checkActivatedSignalValue(int expectedCount) {
        REQUIRE(mActivatedSpy->count() > 0);
        QList<QVariant> arguments = mActivatedSpy->takeFirst();
        const QVariant &argument = arguments.at(0);
        CHECK(argument.type() == QVariant::Int);
        CHECK(argument.toInt() == expectedCount);
    }
};
TEST_CASE_METHOD(GoToLineToolFixture, "GoToLineTool emits signal when Go button clicked v3"){

    // Arrange
    setMaximumLineCount(27);

    // Act
    typeCharToSpinner('1');
    typeCharToSpinner('7');
    clickGoButton();

    // Assert
    checkActivatedSignalCount(1);
    checkActivatedSignalValue(17);
}
