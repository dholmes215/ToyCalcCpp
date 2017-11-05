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

#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QLayout>

#include "../Calculator.hpp"

using namespace calc;


/**
 * Button customized for a calculator.
 *
 * A subclass is necessary because it appears that overriding sizeHint is
 * the only way to get the default size to be what I want.  The official
 * Qt calculator example does it the same way.
 */
class CalcButton : public QPushButton
{
public:
    template <typename Slot>
    CalcButton(const QString & label, QWidget * parent, Slot action)
    : QPushButton(label, parent)
    {
        // Make font big.
        QFont f = font();
        f.setPointSize(24);
        setFont(f);

        // This causes the buttons to expand to fill their grid cell, both
        // horizontally (which is their default) and vertically (NOT their
        // default).  Qt layouts determine size and positioning of widgets
        // based on size policies and size hints.
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        setMinimumHeight(50);
        setMinimumWidth(50);

        // Configure action handler.
        connect(this, &QPushButton::clicked, action);
    }

    QSize sizeHint() const override
    {
        // If we don't override the size hint, the default value will cause
        // the buttons to be smaller than I'd like.
        QSize size = QPushButton::sizeHint();
        size.rwidth() = 50;
        return size;
    }
};

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);

    QWidget widget;
    widget.setWindowTitle("Qt Calculator");

    Calculator calc;

    QGridLayout * mainLayout = new QGridLayout;

    QLabel * displayLabel = new QLabel("0", &widget);
    QFont font;
    font.setPointSize(32);
    displayLabel->setFont(font);
    calc.AddDisplayListener([displayLabel](std::string s) {
        displayLabel->setText(QString::fromStdString(s)); });
    displayLabel->setAlignment(Qt::AlignRight);
    displayLabel->setMaximumHeight(50);
    mainLayout->addWidget(displayLabel, 0, 0, 1, 4);

    std::array<QPushButton *, 10> digitButtons;
    for (int i=0; i<=9; i++) {
        QString label;
        label.setNum(i);
        digitButtons[i] = new CalcButton(label, &widget, [&calc, i](){ calc.PressDigit(i); });
    }

    QPushButton * addButton = new CalcButton("+", &widget, [&calc](){ calc.PressOperation(Calculator::Operation::Add); });
    QPushButton * subButton = new CalcButton("-", &widget, [&calc](){ calc.PressOperation(Calculator::Operation::Subtract); });
    QPushButton * mulButton = new CalcButton(u8"\u00d7", &widget, [&calc](){ calc.PressOperation(Calculator::Operation::Multiply); });
    QPushButton * divButton = new CalcButton(u8"\u00f7", &widget, [&calc](){ calc.PressOperation(Calculator::Operation::Divide); });
    QPushButton * eqButton = new CalcButton("=", &widget, [&calc](){ calc.PressEquals(); });

    mainLayout->addWidget(digitButtons[7], 1, 0, 1, 1);
    mainLayout->addWidget(digitButtons[8], 1, 1, 1, 1);
    mainLayout->addWidget(digitButtons[9], 1, 2, 1, 1);
    mainLayout->addWidget(digitButtons[4], 2, 0, 1, 1);
    mainLayout->addWidget(digitButtons[5], 2, 1, 1, 1);
    mainLayout->addWidget(digitButtons[6], 2, 2, 1, 1);
    mainLayout->addWidget(digitButtons[1], 3, 0, 1, 1);
    mainLayout->addWidget(digitButtons[2], 3, 1, 1, 1);
    mainLayout->addWidget(digitButtons[3], 3, 2, 1, 1);
    mainLayout->addWidget(digitButtons[0], 4, 0, 1, 2);

    mainLayout->addWidget(addButton, 1, 3, 1, 1);
    mainLayout->addWidget(subButton, 2, 3, 1, 1);
    mainLayout->addWidget(mulButton, 3, 3, 1, 1);
    mainLayout->addWidget(divButton, 4, 3, 1, 1);
    mainLayout->addWidget(eqButton, 4, 2, 1, 1);

    widget.setLayout(mainLayout);

    widget.adjustSize();

    widget.show();

    return app.exec();
}
