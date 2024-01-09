#include <gtk4-layer-shell.h>
#include <gtkmm/application.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>

#include "model/clock.hpp"
#include "model/mpris.hpp"

class bar : public Gtk::Window {
public:
    bar() : clock(100, "%I:%M %p %a %e %b %y") {

        // Make this a bar using gtk4-layer-shell
        gtk_layer_init_for_window(gobj());
        gtk_layer_set_layer(gobj(), GTK_LAYER_SHELL_LAYER_BOTTOM);
        gtk_layer_auto_exclusive_zone_enable(gobj());
        gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_TOP, true);
        gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_LEFT, true);
        gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, true);

        set_child(clock_label);
        clock.tick.connect(sigc::mem_fun(clock_label, &Gtk::Label::set_text));
    }
    ~bar() override {}

private:
    mcw::source::clock clock;
    Gtk::Label clock_label;

    mcw::source::mpris mpris;
};

int main(int argc, char** argv) {
    auto app = Gtk::Application::create("murts.cool.widgets");

    return app->make_window_and_run<bar>(argc, argv);
}
