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

#ifndef WXCALCULATOR_H
#define WXCALCULATOR_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "Calculator.hpp"

namespace toycalc
{
    /**
     * wxWidgets ToyCalcCpp application.
     */
    class WxCalculator : public wxApp
    {
    public:
        virtual bool OnInit() override;

    private:
        Calculator calc;
    };

    /**
     * Calculator user interface implementation.
     */
    class WxCalcFrame : public wxFrame
    {
    public:
        WxCalcFrame(Calculator & calc);
    };
}

#endif WXCALCULATOR_H
