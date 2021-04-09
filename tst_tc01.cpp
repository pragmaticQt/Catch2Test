#include <catch.hpp>
#include "color_widget.hpp"

namespace Catch {
template<>
struct StringMaker<QColor> {
    static std::string convert(QColor const& value ) {
        std::ostringstream stringStream;
        stringStream << "red: " << value.red() << ", green: " << value.green() << ", black: " << value.black() << ", ";
        stringStream << "alpha: " << value.alpha();
        return stringStream.str();
    }
};
}
using namespace ScIDE;

TEST_CASE("ColorWidget initial state")
{
    ColorWidget/*QLabel*/ widget;
    auto color = Catch::StringMaker<QColor>::convert(widget.color());
    CHECK(color == "red: 0, green: 0, black: 255, alpha: 255");
//    QColor expected_color(0, 0, 0, 255);
//    CHECK(widget.color() == expected_color);
}

TEST_CASE("ColorWidget changing color updates correctly") {
    // Arrange
    ColorWidget widget;
    QColor red("red");

    // Act
    widget.setColor(red);

    // Assert
    CHECK(widget.color() == red);
}
