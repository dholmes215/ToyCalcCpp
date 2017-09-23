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

#include <cmath>

const int32_t MAX_DIGITS = 8;

using namespace toycalc;

Calculator::Calculator()
    :
    displayListeners(),
    accumulator(0),
    input(0),
    storedOperand(0),
    currentOperation(Operation::None),
    storedOperation(Operation::None),
    currentDisplay(Display::Input),
    equalsPressed(false),
    error(false)
{
}

void Calculator::PressDigit(const int8_t digit)
{
    if (equalsPressed || error) {
        Reset();
    }

    if (currentDisplay == Display::Accumulator) {
        currentDisplay = Display::Input;
    }

    if (input == 0) {
        input = digit;
    }
    else if (input < std::pow(10, MAX_DIGITS - 1)) {
        input = input * 10 + digit;
    }

    UpdateDisplay();
}

void Calculator::PressOperation(const Operation operation)
{
    if (!equalsPressed) {
        PerformOperation();
        input = 0;
    }

    currentDisplay = Display::Accumulator;
    currentOperation = operation;
    equalsPressed = false;

    UpdateDisplay();
}

void Calculator::PressEquals()
{
    if (equalsPressed) {
        input = storedOperand;
        currentOperation = storedOperation;
    }
    PerformOperation();
    storedOperation = currentOperation;
    currentOperation = Operation::None;
    storedOperand = input;
    equalsPressed = true;
    currentDisplay = Display::Accumulator;
    input = 0;
    UpdateDisplay();
}

const std::string Calculator::GetDisplayString() const
{
    std::string out;
    if (error) {
        out = "error";
    }
    else {
        out = std::to_string(GetDisplayValue());
    }
    return out;
}

void Calculator::PerformOperation()
{
    switch (currentOperation) {
    case Operation::None:
        accumulator = input;
        break;
    case Operation::Add:
        accumulator += input;
        break;
    case Operation::Subtract:
        accumulator -= input;
        break;
    case Operation::Multiply:
        accumulator *= input;
        break;
    case Operation::Divide:
        if (input == 0) {
            error = true;
        }
        else {
            accumulator /= input;
        }
        break;
    }
}

int64_t Calculator::GetDisplayValue() const
{
    return (currentDisplay == Display::Input) ? input : accumulator;
}

void Calculator::UpdateDisplay() const
{
    for (const auto & listener : displayListeners) {
        listener(GetDisplayString());
    }
}

void Calculator::Reset()
{
    accumulator = 0;
    input = 0;
    storedOperand = 0;
    currentOperation = Operation::None;
    storedOperation = Operation::None;
    currentDisplay = Display::Input;
    equalsPressed = false;
    error = false;
}
