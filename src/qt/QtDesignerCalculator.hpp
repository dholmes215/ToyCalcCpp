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

#ifndef QTDESIGNERCALCULATOR_HPP
#define QTDESIGNERCALCULATOR_HPP

#include "../Calculator.hpp"

#include <QWidget>

namespace calc {

/**
 * calc::Ui::QtDesignerCalculator is autogenerated and put in
 * ui_QtDesignerCalculator.h.
 */
namespace Ui {
class QtDesignerCalculator;
}

/**
 * A custom QWidget implementing a calculator.
 */
class QtDesignerCalculator : public QWidget
{
    Q_OBJECT

public:
    explicit QtDesignerCalculator(QWidget *parent = 0);
    ~QtDesignerCalculator();

private slots:
    void on_digitButton0_clicked();
    void on_digitButton1_clicked();
    void on_digitButton2_clicked();
    void on_digitButton3_clicked();
    void on_digitButton4_clicked();
    void on_digitButton5_clicked();
    void on_digitButton6_clicked();
    void on_digitButton7_clicked();
    void on_digitButton8_clicked();
    void on_digitButton9_clicked();
    void on_addButton_clicked();
    void on_subButton_clicked();
    void on_mulButton_clicked();
    void on_divButton_clicked();
    void on_eqButton_clicked();

private:
    Ui::QtDesignerCalculator *ui;
    calc::Calculator calc;
};

} // namespace calc

#endif // QTDESIGNERCALCULATOR_HPP