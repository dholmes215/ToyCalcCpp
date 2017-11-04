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

#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>

#include <array>
#include <exception>
#include <iostream>

#include "Calculator.hpp"

int main(int argc, char ** argv)
{
    // FIXME: all this needs to be moved out of here.  No initialization in main!

    auto app = Gtk::Application::create(argc, argv, "us.dholmes.gtkmm_glade_calculator");

    auto builder = Gtk::Builder::create();
    try {
        builder->add_from_file("GladeCalculator.glade");
    } catch (const std::exception & ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    calc::Calculator calc;

    Gtk::Window * window = nullptr;
    builder->get_widget("GladeCalculator", window);

    Gtk::Label * displayLabel = nullptr;
    builder->get_widget("display", displayLabel);
    calc.AddDisplayListener([displayLabel](std::string s) {
        displayLabel->set_markup(Glib::ustring::compose("<span font='32'>%1</span>", s));
    });

    std::array<Gtk::Button *, 10> digitButtons;
    for (int i=0; i<=9; i++) {
        std::string id("digit");
        id += std::to_string(i);
        builder->get_widget(id, digitButtons[i]);
        digitButtons[i]->signal_clicked().connect([&calc, i](){ calc.PressDigit(i); });
    }

    Gtk::Button * addButton = nullptr;
    Gtk::Button * subButton = nullptr;
    Gtk::Button * mulButton = nullptr;
    Gtk::Button * divButton = nullptr;
    Gtk::Button * eqButton = nullptr;

    builder->get_widget("opAdd", addButton);
    builder->get_widget("opSub", subButton);
    builder->get_widget("opMul", mulButton);
    builder->get_widget("opDiv", divButton);
    builder->get_widget("eq", eqButton);

    addButton->signal_clicked().connect([&calc](){ calc.PressOperation(calc::Calculator::Operation::Add); });
    subButton->signal_clicked().connect([&calc](){ calc.PressOperation(calc::Calculator::Operation::Subtract); });
    mulButton->signal_clicked().connect([&calc](){ calc.PressOperation(calc::Calculator::Operation::Multiply); });
    divButton->signal_clicked().connect([&calc](){ calc.PressOperation(calc::Calculator::Operation::Divide); });
    eqButton->signal_clicked().connect([&calc](){ calc.PressEquals(); });

	return app->run(*window);
}
