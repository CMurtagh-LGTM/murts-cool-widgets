#include "application.hpp"
#include "widget/clock.hpp"
#include "window.hpp"

#include <iostream>

int main(int argc, char** argv) {
    application::Params params = {};
    return application::application(argc, argv, params, [](GtkApplication* app) {
        window::Params params = {};
        auto gtk_window       = window::new_window(app, params);
        gtk_window_set_child(gtk_window, widget::clock("%I:%M %p %a %e %b %y"));
        gtk_window_present(gtk_window);
    });
}
