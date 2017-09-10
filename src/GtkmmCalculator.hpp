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

#ifndef GTKMMCALCULATOR_H
#define GTKMMCALCULATOR_H

#include <array>

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>

#include "Calculator.hpp"

namespace toycalc
{
    /**
     * Window implementing a calculator.
     */
    class GtkmmCalculator : public Gtk::Window
    {
    public:
        GtkmmCalculator();
        virtual ~GtkmmCalculator();

    private:
        Gtk::Box mainBox;
        Gtk::Label displayLabel;
        Gtk::Grid buttonGrid;
        std::array<Gtk::Button, 10> digitButtons;
        Gtk::Button addButton;
        Gtk::Button subButton;
        Gtk::Button mulButton;
        Gtk::Button divButton;
        Gtk::Button eqButton;

        Calculator calc;
    };
}


#endif // GTKMMCALCULATOR_H
