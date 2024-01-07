#include "application.hpp"
#include "widget/clock.hpp"
#include "window.hpp"

int main(int argc, char** argv) {
    application::Params params = {};
    return application::application(argc, argv, params, [](GtkApplication* app) {
        window::Params params = {};
        auto gtk_window       = window::new_window(app, params);
        gtk_container_add(GTK_CONTAINER(gtk_window), widget::clock("%I:%M %p %a %e %b %y"));
        gtk_widget_show_all(GTK_WIDGET(gtk_window));
    });
}
