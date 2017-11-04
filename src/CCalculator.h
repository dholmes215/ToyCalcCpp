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

#ifndef CCALCULATOR_H
#define CCALCULATOR_H

// C interface to class Calculator.

struct Calculator * calculator_new();

void calculator_delete(struct Calculator * calculator);

void calculator_press_digit(struct Calculator * calculator, int digit);

void calculator_press_operation(struct Calculator * calculator, int op);

void calculator_press_equals(struct Calculator * calculator);

void calculator_add_display_listener(struct Calculator * calculator, void (*listenerFunc)(void *, const char *), void * listenerFuncData);

#endif // CCALCULATOR_H
