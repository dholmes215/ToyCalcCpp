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

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/gbsizer.h>

#include "Calculator.hpp"

namespace calc {

template <typename Action>
wxButton * createButton(wxWindow * const parent, const wxString label, Action action)
{
    wxButton * button = new wxButton(parent, wxID_ANY, label);
    wxFont buttonFont = button->GetFont();
    buttonFont.SetPointSize(24);
    button->SetFont(buttonFont);

    // By default, the buttons are wider than I'd like, so I override the size
    // hints to get them to the size I want.
    button->SetSizeHints(50,50);

    button->Bind(wxEVT_BUTTON, action);

    return button;
}

wxButton * createDigitButton(Calculator & calc, wxWindow * const parent, const int8_t digit)
{
    wxString label;
    label << digit;

    return createButton(parent, label, [&calc, digit](wxCommandEvent &) { calc.PressDigit(digit); });
}

/**
 * A wxFrame (a window) implementing a calculator.
 */
class WxCalcFrame : public wxFrame
{
public:
    WxCalcFrame(Calculator & calc) : wxFrame(nullptr, wxID_ANY, _T("wxWidgets Calculator"), wxDefaultPosition, wxSize(300, 300))
    {
        wxPanel * panel = new wxPanel(this, wxID_ANY);
        wxGridBagSizer * sizer = new wxGridBagSizer();

        wxStaticText * display = new wxStaticText(panel, wxID_ANY,
                calc.GetDisplayString());
        wxFont displayFont = display->GetFont();
        displayFont.SetPointSize(32);
        display->SetFont(displayFont);

        calc.AddDisplayListener([display](std::string s) { display->SetLabel(s); });

        sizer->Add(display, wxGBPosition(0, 0), wxGBSpan(1, 4), wxALIGN_RIGHT);
        sizer->Add(createDigitButton(calc, panel, 0), wxGBPosition(4, 0), wxGBSpan(1, 2), wxEXPAND);
        sizer->Add(createDigitButton(calc, panel, 1), wxGBPosition(3, 0), wxDefaultSpan, wxEXPAND);
        sizer->Add(createDigitButton(calc, panel, 2), wxGBPosition(3, 1), wxDefaultSpan, wxEXPAND);
        sizer->Add(createDigitButton(calc, panel, 3), wxGBPosition(3, 2), wxDefaultSpan, wxEXPAND);
        sizer->Add(createDigitButton(calc, panel, 4), wxGBPosition(2, 0), wxDefaultSpan, wxEXPAND);
        sizer->Add(createDigitButton(calc, panel, 5), wxGBPosition(2, 1), wxDefaultSpan, wxEXPAND);
        sizer->Add(createDigitButton(calc, panel, 6), wxGBPosition(2, 2), wxDefaultSpan, wxEXPAND);
        sizer->Add(createDigitButton(calc, panel, 7), wxGBPosition(1, 0), wxDefaultSpan, wxEXPAND);
        sizer->Add(createDigitButton(calc, panel, 8), wxGBPosition(1, 1), wxDefaultSpan, wxEXPAND);
        sizer->Add(createDigitButton(calc, panel, 9), wxGBPosition(1, 2), wxDefaultSpan, wxEXPAND);

        wxButton * addButton = createButton(panel, "+",
            [&calc](wxCommandEvent &) { calc.PressOperation(Calculator::Operation::Add); });
        wxButton * subButton = createButton(panel, "-",
            [&calc](wxCommandEvent &) { calc.PressOperation(Calculator::Operation::Subtract); });
        wxButton * mulButton = createButton(panel, "*",
            [&calc](wxCommandEvent &) { calc.PressOperation(Calculator::Operation::Multiply); });
        wxButton * divButton = createButton(panel, "/",
            [&calc](wxCommandEvent &) { calc.PressOperation(Calculator::Operation::Divide); });
        wxButton * eqButton = createButton(panel, "=",
            [&calc](wxCommandEvent &) { calc.PressEquals(); });


        sizer->Add(addButton, wxGBPosition(1, 3), wxDefaultSpan, wxEXPAND);
        sizer->Add(subButton, wxGBPosition(2, 3), wxDefaultSpan, wxEXPAND);
        sizer->Add(mulButton, wxGBPosition(3, 3), wxDefaultSpan, wxEXPAND);
        sizer->Add(divButton, wxGBPosition(4, 3), wxDefaultSpan, wxEXPAND);
        sizer->Add(eqButton, wxGBPosition(4, 2), wxDefaultSpan, wxEXPAND);

        sizer->AddGrowableCol(0);
        sizer->AddGrowableCol(1);
        sizer->AddGrowableCol(2);
        sizer->AddGrowableCol(3);
        // The orientation is what prevents the display row from growing when
        // the window is resized.
        sizer->AddGrowableRow(0, 0),
        sizer->AddGrowableRow(1, 1);
        sizer->AddGrowableRow(2, 1);
        sizer->AddGrowableRow(3, 1);
        sizer->AddGrowableRow(4, 1);

        sizer->SetFlexibleDirection(wxBOTH);

        // Associates the sizer with the panel, fits the panel to the sizer's
        // contents, and prevents it from shrinking to smaller than that.
        panel->SetSizerAndFit(sizer);

        // Fits the window (wxFrame) to the sizer's contents, and prevents it
        // from shrinking smaller than that.
        sizer->SetSizeHints(this);
    }
};

/**
 * wxWidgets ToyCalcCpp application.
 */
class WxCalculator : public wxApp
{
public:
    virtual bool OnInit() override
    {
        WxCalcFrame *frame = new WxCalcFrame(calc);
        frame->Show(true);
        return true;
    }
private:
    Calculator calc;
};

} // namespace calc

// Expands to main(), etc.
wxIMPLEMENT_APP(calc::WxCalculator);
