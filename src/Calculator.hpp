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

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace toycalc
{
    /**
     * A simple calculator. The public interface and behavior of this class are
     * modeled after a classic pocket calculator.
     */
    class Calculator
    {
    public:

        Calculator();

        /**
         * The operations the calculator can perform.
         */
        enum Operation
        {
            None, Add, Subtract, Multiply, Divide
        };

        /**
         * Press a digit button on the calculator.
         *
         * \param digit The digit to press.
         */
        void PressDigit(const int8_t digit);

        /**
         * Press an operation button on the calculator (+-/*).
         *
         * \param operation The operation to perform.
         */
        void PressOperation(const Operation operation);

        /**
         * Press the "equals" button on the calculator.
         */
        void PressEquals();

        /**
         * Returns the currently-displayed number as a std::string.
         */
        const std::string GetDisplayString() const;

        /**
         * Registers a listener for display update events. Every time the calculator
         * display is updated, the listeners will be called with the new number to
         * display.
         *
         * \param listener The listener to add.
         *
         * const std::function<void(std::string)>
         */
        template <typename Listener>
        void AddDisplayListener(Listener listener)
        {
            displayListeners.push_back(listener);
        }

    private:

        /**
         * The calculator stores two numbers at a time: an input field and an
         * accumulator field. Only one of these numbers is displayed on the screen
         * at any given time.
         */
        enum Display
        {
            Input, Accumulator
        };

        std::vector<std::function<void(std::string)> > displayListeners;
        int64_t accumulator;
        int64_t input;
        int64_t storedOperand;
        Operation currentOperation;
        Operation storedOperation;
        Display currentDisplay;
        bool equalsPressed;
        bool error;

        void PerformOperation();
        int64_t GetDisplayValue() const;
        void UpdateDisplay() const;
        void Reset();
    };
}

#endif // CALCULATOR_H
