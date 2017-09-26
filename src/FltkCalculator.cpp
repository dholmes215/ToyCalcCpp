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

#include <array>

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Window.H>

#include "Calculator.hpp"

using namespace toycalc;

struct DigitCallbackData
{
    int8_t digit;
    Calculator * calc;
};

struct OpCallbackData
{
    Calculator::Operation op;
    Calculator * calc;

    OpCallbackData(Calculator::Operation op, Calculator * calc) : op(op), calc(calc) {};
};

void PressDigit(Fl_Widget *, void * arg)
{
    DigitCallbackData * callbackData = static_cast<DigitCallbackData *>(arg);
    callbackData->calc->PressDigit(callbackData->digit);
}

void PressOperation(Fl_Widget *, void * arg)
{
    OpCallbackData * callbackData = static_cast<OpCallbackData *>(arg);
    callbackData->calc->PressOperation(callbackData->op);
}

void PressEquals(Fl_Widget *, void * arg)
{
    Calculator * calc = static_cast<Calculator *>(arg);
    calc->PressEquals();
}

Fl_Button * CreateDigitButton(int x, int y, int w, int h, const char * label, const DigitCallbackData & data)
{
    Fl_Button * button = new Fl_Button(x, y, w, h, label);
    button->callback((Fl_Callback *)PressDigit, (void *)(&data));

    return button;
}

Fl_Button * CreateOpButton(int x, int y, int w, int h, const char * label, const OpCallbackData & data)
{
    Fl_Button * button = new Fl_Button(x, y, w, h, label);
    button->callback((Fl_Callback *)PressOperation, (void *)(&data));

    return button;
}

int main(int argc, char ** argv)
{
    Calculator calc;
    Fl_Window *window = new Fl_Window(192, 240);
    window->label("ToyCalcCpp");

    Fl_Output *display = new Fl_Output(0, 0, 240, 48);
    display->align(FL_ALIGN_RIGHT);
    display->labelsize(32);
    display->value("0");

    calc.AddDisplayListener([display](std::string s){ display->value(s.c_str()); });

    std::array<DigitCallbackData,10> DIGIT_CALLBACK_DATA;
    for (int i=0; i<=9; i++) {
        DIGIT_CALLBACK_DATA[i].digit = i;
        DIGIT_CALLBACK_DATA[i].calc = &calc;
    }
    std::array<Fl_Button *, 10> digitButtons;
    digitButtons[0] = CreateDigitButton( 0, 192, 96, 48, "0", DIGIT_CALLBACK_DATA[0]);
    digitButtons[1] = CreateDigitButton( 0, 144, 48, 48, "1", DIGIT_CALLBACK_DATA[1]);
    digitButtons[2] = CreateDigitButton(48, 144, 48, 48, "2", DIGIT_CALLBACK_DATA[2]);
    digitButtons[3] = CreateDigitButton(96, 144, 48, 48, "3", DIGIT_CALLBACK_DATA[3]);
    digitButtons[4] = CreateDigitButton( 0,  96, 48, 48, "4", DIGIT_CALLBACK_DATA[4]);
    digitButtons[5] = CreateDigitButton(48,  96, 48, 48, "5", DIGIT_CALLBACK_DATA[5]);
    digitButtons[6] = CreateDigitButton(96,  96, 48, 48, "6", DIGIT_CALLBACK_DATA[6]);
    digitButtons[7] = CreateDigitButton( 0,  48, 48, 48, "7", DIGIT_CALLBACK_DATA[7]);
    digitButtons[8] = CreateDigitButton(48,  48, 48, 48, "8", DIGIT_CALLBACK_DATA[8]);
    digitButtons[9] = CreateDigitButton(96,  48, 48, 48, "9", DIGIT_CALLBACK_DATA[9]);

    const std::array<OpCallbackData,4> OP_CALLBACK_DATA = {{
            { Calculator::Operation::Add, &calc },
            { Calculator::Operation::Subtract, &calc },
            { Calculator::Operation::Multiply, &calc },
            { Calculator::Operation::Divide, &calc }
    }};
    Fl_Button * addButton = CreateOpButton(144, 48,  48, 48, "+",        OP_CALLBACK_DATA[0]);
    Fl_Button * subButton = CreateOpButton(144, 96,  48, 48, "-",        OP_CALLBACK_DATA[1]);
    Fl_Button * mulButton = CreateOpButton(144, 144, 48, 48, u8"\u00d7", OP_CALLBACK_DATA[2]);
    Fl_Button * divButton = CreateOpButton(144, 192, 48, 48, u8"\u00f7", OP_CALLBACK_DATA[3]);

    Fl_Button * eqButton  = new Fl_Button(96, 192, 48, 48, "=");
    eqButton->callback((Fl_Callback *)PressEquals, static_cast<void *>(&calc));

    window->end();
    window->show(argc, argv);

    return Fl::run();
}
