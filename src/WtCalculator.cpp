/*
Copyright (C) 2017 David A Holmes Jr

This file is part of ToyCalcCpp.

ToyCalcCpp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

ToyCalcCpp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with ToyCalcCpp.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Calculator.hpp"

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WGridLayout.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

#include <array>
#include <memory>

namespace calc {

template <typename Action>
std::unique_ptr<Wt::WPushButton> createButton(Calculator & calc, const Wt::WString & label, Action action)
{
    auto button = std::make_unique<Wt::WPushButton>(label);
    button->setStyleClass("buttons");
    button->clicked().connect(action);
    return button;
}

std::unique_ptr<Wt::WPushButton> createDigitButton(Calculator & calc, int digit)
{
    return createButton(calc, std::to_string(digit),
            [&calc, digit](Wt::WMouseEvent e){ calc.PressDigit(digit); });
}

class WtCalculatorApplication : public Wt::WApplication
{
public:
    WtCalculatorApplication(const Wt::WEnvironment & env)
    : WApplication(env),
      calc()
    {
        setTitle("Wt Calculator");

        // TODO: Consider implementing both CSS-based and code-based layouts

        styleSheet().addRule(".display", "font-size: 36px;");
        styleSheet().addRule(".display", "text-align: right;");
        styleSheet().addRule(".display", "min-height: 36px;");
        styleSheet().addRule(".buttons", "font-size: 32px;");
        styleSheet().addRule(".buttons", "min-height: 50px;");
        styleSheet().addRule(".buttons", "min-width: 50px;");

        root()->resize(250, 250);

        // Notice the modern C++ idioms here: std::unique_ptr is RAII owner,
        // passing std::unique_ptr as parameter transfers ownership, retaining
        // raw pointer represents non-ownership.
        Wt::WGridLayout * layout = root()->setLayout(std::make_unique<Wt::WGridLayout>());

        Wt::WText * display = layout->addWidget(std::make_unique<Wt::WText>("0"), 0, 0, 1, 4);
        display->setStyleClass("display");

        Calculator & calcRef = calc;
        calc.AddDisplayListener([display](std::string s){ display->setText(s); });

        layout->addWidget(createDigitButton(calc, 0), 4, 0, 1, 2);
        layout->addWidget(createDigitButton(calc, 1), 3, 0);
        layout->addWidget(createDigitButton(calc, 2), 3, 1);
        layout->addWidget(createDigitButton(calc, 3), 3, 2);
        layout->addWidget(createDigitButton(calc, 4), 2, 0);
        layout->addWidget(createDigitButton(calc, 5), 2, 1);
        layout->addWidget(createDigitButton(calc, 6), 2, 2);
        layout->addWidget(createDigitButton(calc, 7), 1, 0);
        layout->addWidget(createDigitButton(calc, 8), 1, 1);
        layout->addWidget(createDigitButton(calc, 9), 1, 2);

        layout->addWidget(createButton(calc, "+", [&calcRef](Wt::WMouseEvent e){
            calcRef.PressOperation(Calculator::Operation::Add); }), 1, 3);
        layout->addWidget(createButton(calc, "-", [&calcRef](Wt::WMouseEvent e){
            calcRef.PressOperation(Calculator::Operation::Subtract); }), 2, 3);
        layout->addWidget(createButton(calc, u8"\u00d7", [&calcRef](Wt::WMouseEvent e){
            calcRef.PressOperation(Calculator::Operation::Multiply); }), 3, 3);
        layout->addWidget(createButton(calc, u8"\u00f7", [&calcRef](Wt::WMouseEvent e){
            calcRef.PressOperation(Calculator::Operation::Divide); }), 4, 3);
        layout->addWidget(createButton(calc, "=", [&calcRef](Wt::WMouseEvent e){
            calcRef.PressEquals(); }), 4, 2);
    }

private:
    Calculator calc;
};

} // namespace calc

// Run with: ./WtCalculator --docroot . --http-address 0.0.0.0 --http-port 9090
int main(int argc, char ** argv) {

    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
        return std::make_unique<calc::WtCalculatorApplication>(env);
    });
}
