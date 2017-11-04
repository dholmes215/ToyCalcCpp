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

#include "QtDesignerCalculator.hpp"
#include "ui_QtDesignerCalculator.h"

#include <QApplication>
#include <QLabel>

using namespace calc;

QtDesignerCalculator::QtDesignerCalculator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtDesignerCalculator),
    calc()
{
    ui->setupUi(this);

    adjustSize();

    // Update the GUI when the calculator display changes.
    QLabel * displayLabel = ui->displayLabel;
    calc.AddDisplayListener([displayLabel](std::string s) {
        displayLabel->setText(QString::fromStdString(s)); });
}

QtDesignerCalculator::~QtDesignerCalculator()
{
    delete ui;
}

void QtDesignerCalculator::on_digitButton0_clicked() { calc.PressDigit(0); }
void QtDesignerCalculator::on_digitButton1_clicked() { calc.PressDigit(1); }
void QtDesignerCalculator::on_digitButton2_clicked() { calc.PressDigit(2); }
void QtDesignerCalculator::on_digitButton3_clicked() { calc.PressDigit(3); }
void QtDesignerCalculator::on_digitButton4_clicked() { calc.PressDigit(4); }
void QtDesignerCalculator::on_digitButton5_clicked() { calc.PressDigit(5); }
void QtDesignerCalculator::on_digitButton6_clicked() { calc.PressDigit(6); }
void QtDesignerCalculator::on_digitButton7_clicked() { calc.PressDigit(7); }
void QtDesignerCalculator::on_digitButton8_clicked() { calc.PressDigit(8); }
void QtDesignerCalculator::on_digitButton9_clicked() { calc.PressDigit(9); }
void QtDesignerCalculator::on_addButton_clicked()    { calc.PressOperation(Calculator::Operation::Add); }
void QtDesignerCalculator::on_subButton_clicked()    { calc.PressOperation(Calculator::Operation::Subtract); }
void QtDesignerCalculator::on_mulButton_clicked()    { calc.PressOperation(Calculator::Operation::Multiply); }
void QtDesignerCalculator::on_divButton_clicked()    { calc.PressOperation(Calculator::Operation::Divide); }
void QtDesignerCalculator::on_eqButton_clicked()     { calc.PressEquals(); }

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);

    QtDesignerCalculator widget;

    widget.show();

    return app.exec();
}
