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

#include "CCalculator.h"

#include <gtk/gtk.h>

#include <stdio.h>


/**
 * Callback parameter for digit buttons.
 */
struct DigitCallbackData {
    struct Calculator * calculator;
    int digit;
};

/**
 * Callback parameter for operator buttons.
 */
struct OperatorCallbackData {
    struct Calculator * calculator;
    int op;
};


///////////////////////////////////////////////////////////////////////


// Here we define a new GObject type, GtkCalculator. This section is
// basically equivalent to defining a calculator window class in any of the
// C++ toolkit calculator implementations.

#define GTK_CALCULATOR_TYPE (gtk_calculator_get_type())
G_DECLARE_FINAL_TYPE(GtkCalculator, gtk_calculator, CALC, GTKCALCULATOR, GtkWindow)

/**
 * GtkCalculator is a subclass of GtkWindow.
 */
struct _GtkCalculator {

    GtkWindow parent;
    struct Calculator * calculator;
    struct DigitCallbackData digitCallbackData[10];
    struct OperatorCallbackData operatorCallbackData[4];
};

G_DEFINE_TYPE(GtkCalculator, gtk_calculator, GTK_TYPE_WINDOW);

/**
 * GtkCalculator instance initializer. Basically a constructor.
 */
static void gtk_calculator_init(GtkCalculator * calculator) {

    calculator->calculator = calculator_new();

    for (int i=0; i<=9; i++) {
        calculator->digitCallbackData[i].calculator = calculator->calculator;
        calculator->digitCallbackData[i].digit = i;
    }

    for (int i=0; i<=3; i++) {
        calculator->operatorCallbackData[i].calculator = calculator->calculator;
        calculator->operatorCallbackData[i].op = i;
    }
}

/**
 * GtkCalculator instance finalizer. Basically a destructor, except GObjects
 * have both "disposers" and "finalizers" which are called at different times
 * as part of the destruction of a GObject.  It's confusing; look it up if you
 * need to mess with this stuff.
 */
static void gtk_calculator_finalize(GObject * calculator) {

    calculator_delete(CALC_GTKCALCULATOR(calculator)->calculator);

    G_OBJECT_CLASS(gtk_calculator_parent_class)->finalize(calculator);
}

/**
 * GtkCalculator class initializer. We're basically overriding the virtual
 * method "finalize" here.  If we added any signals or properties, we would
 * define them here too.
 */
static void gtk_calculator_class_init(GtkCalculatorClass * klass) {

    GObjectClass * objectClass = G_OBJECT_CLASS(klass);
    objectClass->finalize = gtk_calculator_finalize;
}

/**
 * Allocates and initializes a GtkCalculator.
 */
GtkCalculator * gtk_calculator_new(GtkApplication * app) {

    return g_object_new(GTK_CALCULATOR_TYPE, "application", app, NULL);
}


///////////////////////////////////////////////////////////////////////


static void set_display_text(GtkLabel * displayLabel, const char * text, int fontSize) {

    const char * format = "<span font='%d'>\%s</span>";
    char * markup = g_markup_printf_escaped(format, fontSize, text);
    gtk_label_set_markup(displayLabel, markup);
    g_free(markup);
}

static GtkWidget * create_button(char * text) {

    GtkWidget * button = gtk_button_new_with_label("");
    GtkWidget * buttonLabel = gtk_bin_get_child(GTK_BIN(button));
    set_display_text(GTK_LABEL(buttonLabel), text, 24);

    // GTK lays out widgets according to their expand and size request
    // properties. I'm overriding the defaults here to cause them to expand
    // and to prevent them from being too small.
    gtk_widget_set_hexpand(button, 1);
    gtk_widget_set_vexpand(button, 1);
    gtk_widget_set_size_request(button, 50, 50);

    return button;
}

static void update_display(void * display, const char * text) {

    GtkWidget * displayLabel = (GtkWidget *)display;
    set_display_text(GTK_LABEL(displayLabel), text, 32);
}

static void press_digit_button(GtkWidget * button, gpointer data) {

    struct DigitCallbackData * callbackData = (struct DigitCallbackData *)data;
    calculator_press_digit(callbackData->calculator, callbackData->digit);
}

static void activate(GtkApplication * app, gpointer user_data) {

    GtkWidget * window = GTK_WIDGET(gtk_calculator_new(app));
    gtk_window_set_title(GTK_WINDOW(window), "GTK+ Calculator");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    GtkWidget * mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), mainBox);

    GtkWidget * displayLabel = gtk_label_new("");
    set_display_text(GTK_LABEL(displayLabel), "0", 32);
    gtk_label_set_xalign(GTK_LABEL(displayLabel), 1.0f);
    gtk_container_add(GTK_CONTAINER(mainBox), displayLabel);
    struct Calculator * calculator = CALC_GTKCALCULATOR(window)->calculator;
    calculator_add_display_listener(calculator, update_display, displayLabel);

    GtkWidget * buttonGrid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(mainBox), buttonGrid);

    GtkWidget * digitButtons[10];
    for (int i=0; i<=9; i++) {
        char digitStr[2];
        snprintf(digitStr, 2, "%d", i);
        digitButtons[i] = create_button(digitStr);

        g_signal_connect(digitButtons[i], "clicked", G_CALLBACK(press_digit_button), &(CALC_GTKCALCULATOR(window)->digitCallbackData[i]));
    }
    gtk_grid_attach(GTK_GRID(buttonGrid), digitButtons[0], 0, 3, 2, 1);
    gtk_grid_attach(GTK_GRID(buttonGrid), digitButtons[1], 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(buttonGrid), digitButtons[2], 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(buttonGrid), digitButtons[3], 2, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(buttonGrid), digitButtons[4], 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(buttonGrid), digitButtons[5], 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(buttonGrid), digitButtons[6], 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(buttonGrid), digitButtons[7], 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(buttonGrid), digitButtons[8], 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(buttonGrid), digitButtons[9], 2, 0, 1, 1);

    GtkWidget * addButton = create_button("+");
    GtkWidget * subButton = create_button("-");
    GtkWidget * mulButton = create_button("\xc3\x97");
    GtkWidget * divButton = create_button("\xc3\xb7");
    GtkWidget * eqButton = create_button("=");

    gtk_grid_attach(GTK_GRID(buttonGrid), addButton, 3, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(buttonGrid), subButton, 3, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(buttonGrid), mulButton, 3, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(buttonGrid), divButton, 3, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(buttonGrid), eqButton, 2, 3, 1, 1);

    gtk_widget_show_all(window);
}

int main(int argc, char ** argv) {

    // GtkApplications are normally single-process. If a second process is
    // launched, it will "activate" the first process's GtkApplication,
    // causing the first process to open a second window.  The second process
    // will then exit.
    GtkApplication * app = gtk_application_new("us.dholmes.gtk_calculator", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
