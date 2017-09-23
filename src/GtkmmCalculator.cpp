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

#include "GtkmmCalculator.hpp"

using namespace toycalc;

template <typename Action>
void configureButton(Gtk::Button & button, const Glib::ustring & label, Action action)
{
    button.set_label(""); // Create the child label widget so we can get it
    Gtk::Label * buttonLabel = static_cast<Gtk::Label *>(button.get_child());
    if (buttonLabel != nullptr)
    {
        buttonLabel->set_markup(Glib::ustring::compose("<span font='24'>%1</span>", label));
    }
    button.set_hexpand(true);
    button.set_vexpand(true);
    button.signal_clicked().connect(action);
}

GtkmmCalculator::GtkmmCalculator()
    : mainBox(Gtk::ORIENTATION_VERTICAL, 10),
      displayLabel("", Gtk::ALIGN_END),
      buttonGrid(),
      digitButtons(),
      addButton(),
      subButton(),
      mulButton(),
      divButton(),
      eqButton(),
      calc()
{
    set_border_width(10);
    set_default_size(240, 240);
    set_title("ToyCalcCpp");

    //button.signal_clicked().connect(sigc::mem_fun(*this, &GtkmmCalculator::on_button_clicked));
    //button.signal_clicked().connect([](){ std::cout << "Hello World" << std::endl; });

    add(mainBox);

    displayLabel.set_markup("<span font='32'>0</span>");

    Gtk::Label & displayLabelRef = displayLabel;
    calc.AddDisplayListener([&displayLabelRef](std::string s) {
        displayLabelRef.set_markup(Glib::ustring::compose("<span font='32'>%1</span>", s));
    });

    mainBox.add(displayLabel);
    mainBox.add(buttonGrid);

    Calculator & calcRef = calc;
    for (int i=0; i<=9; i++)
    {
        configureButton(digitButtons[i], Glib::ustring::compose("%1", i), [&calcRef, i](){ calcRef.PressDigit(i); });
    }

    configureButton(addButton, "+", [&calcRef](){ calcRef.PressOperation(Calculator::Operation::Add); });
    configureButton(subButton, "-", [&calcRef](){ calcRef.PressOperation(Calculator::Operation::Subtract); });
    configureButton(mulButton, "*", [&calcRef](){ calcRef.PressOperation(Calculator::Operation::Multiply); });
    configureButton(divButton, "/", [&calcRef](){ calcRef.PressOperation(Calculator::Operation::Divide); });
    configureButton(eqButton, "=", [&calcRef](){ calcRef.PressEquals(); });

    buttonGrid.attach(digitButtons[7], 0, 0, 1, 1);
    buttonGrid.attach(digitButtons[8], 1, 0, 1, 1);
    buttonGrid.attach(digitButtons[9], 2, 0, 1, 1);
    buttonGrid.attach(digitButtons[4], 0, 1, 1, 1);
    buttonGrid.attach(digitButtons[5], 1, 1, 1, 1);
    buttonGrid.attach(digitButtons[6], 2, 1, 1, 1);
    buttonGrid.attach(digitButtons[1], 0, 2, 1, 1);
    buttonGrid.attach(digitButtons[2], 1, 2, 1, 1);
    buttonGrid.attach(digitButtons[3], 2, 2, 1, 1);
    buttonGrid.attach(digitButtons[0], 0, 3, 2, 1);

    buttonGrid.attach(addButton, 3, 0, 1, 1);
    buttonGrid.attach(subButton, 3, 1, 1, 1);
    buttonGrid.attach(mulButton, 3, 2, 1, 1);
    buttonGrid.attach(divButton, 3, 3, 1, 1);
    buttonGrid.attach(eqButton, 2, 3, 1, 1);

    // Show everything.
    for (int i=0; i<=9; i++) {
        digitButtons[i].show();
    }
    addButton.show();
    subButton.show();
    mulButton.show();
    divButton.show();
    eqButton.show();
    displayLabel.show();
    buttonGrid.show();
    mainBox.show();
    show();
}

GtkmmCalculator::~GtkmmCalculator()
{
}

int main(int argc, char ** argv)
{
    auto app = Gtk::Application::create(argc, argv, "us.dholmes.toycalc");

    GtkmmCalculator calc;

	return app->run(calc);
}
