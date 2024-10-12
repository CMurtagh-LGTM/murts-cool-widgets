#include <curl/curl.h>
#include <gtk4-layer-shell.h>
#include <gtkmm.h>

#include "control/tray.hpp"
#include "control/mpris.hpp"
#include "model/clock.hpp"
#include "model/dbus.hpp"
#include "utils/css.hpp"


class bar : public Gtk::Window {
    // TODO put this somewhere else

public:
    bar() : clock(100, "%I:%M %p %a %e %b %y"), tray_sni(&dbus), mpris(&dbus)  {

        // Make this a bar using gtk4-layer-shell
        gtk_layer_init_for_window(gobj());
        gtk_layer_set_layer(gobj(), GTK_LAYER_SHELL_LAYER_BOTTOM);
        gtk_layer_auto_exclusive_zone_enable(gobj());
        gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_TOP, true);
        gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_LEFT, true);
        gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, true);

        box.set_center_widget(clock_label);
        end.append(mpris.get_widget());
        end.append(tray_sni.get_widget());
        box.set_end_widget(end);
        set_child(box);

        clock.tick.connect(sigc::mem_fun(clock_label, &Gtk::Label::set_text));

        m_refCssProvider = mcw::utils::read_css("bar.css", get_display());
    }
    ~bar() override {}

private:
    mcw::model::clock clock;
    Gtk::Label clock_label;

    Gtk::CenterBox box;
    Gtk::Box end;

    mcw::model::dbus dbus;
    mcw::control::tray_sni tray_sni;
    mcw::control::mpris mpris;

    Glib::RefPtr<Gtk::CssProvider> m_refCssProvider;
};

int main(int argc, char** argv) {
    curl_global_init(CURL_GLOBAL_ALL);
    auto app = Gtk::Application::create("murts.cool.widgets");
    auto r   = app->make_window_and_run<bar>(argc, argv);
    curl_global_cleanup();
    return r;
}
