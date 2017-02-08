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

#include "WxCalculator.hpp"

#include <wx/gbsizer.h>

using namespace toycalc;

wxIMPLEMENT_APP(WxCalculator);

bool WxCalculator::OnInit()
{
    WxCalcFrame *frame = new WxCalcFrame(calc);
    frame->Show(true);
    return true;
}

wxButton * createButton(wxWindow * const parent, const wxString label, const std::function<void(wxCommandEvent &)> action)
{
    wxButton * button = new wxButton(parent, wxID_ANY, label);
    wxFont buttonFont = button->GetFont();
    buttonFont.SetPointSize(24);
    button->SetFont(buttonFont);
    button->Bind(wxEVT_BUTTON, action);

    return button;
}

wxButton * createDigitButton(Calculator & calc, wxWindow * const parent, const int8_t digit)
{
    wxString label;
    label << digit;

    return createButton(parent, label, [&calc, digit](wxCommandEvent &) { calc.PressDigit(digit); });
}

WxCalcFrame::WxCalcFrame(Calculator & calc)
    : wxFrame(nullptr, wxID_ANY, _T("ToyCalcCpp"), wxDefaultPosition, wxSize(300, 300))
{
    wxPanel * panel = new wxPanel(this, wxID_ANY);

    wxGridBagSizer * sizer = new wxGridBagSizer();

    wxStaticText * display = new wxStaticText(panel, wxID_ANY, calc.GetDisplayString());
    wxFont displayFont = display->GetFont();
    displayFont.SetPointSize(32);
    display->SetWindowStyle(wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
    display->SetFont(displayFont);

    calc.AddDisplayListener([display](std::string s) { display->SetLabel(s); });

    sizer->Add(display, wxGBPosition(0, 0), wxGBSpan(1, 4), wxEXPAND);
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
    sizer->AddGrowableRow(0);
    sizer->AddGrowableRow(1);
    sizer->AddGrowableRow(2);
    sizer->AddGrowableRow(3);
    sizer->AddGrowableRow(4);

    sizer->SetFlexibleDirection(wxBOTH);
    sizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);

    panel->SetSizerAndFit(sizer);

    sizer->SetSizeHints(this);
}
