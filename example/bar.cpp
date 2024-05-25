#include <curl/curl.h>
#include <gtk4-layer-shell.h>
#include <gtkmm.h>
#include <iostream>

#include "control/tray.hpp"
#include "model/clock.hpp"
#include "model/mpris.hpp"
#include "model/sni.hpp"
#include "utils/css.hpp"
#include "widget/music.hpp"
#include "widget/tray_item.hpp"

class bar : public Gtk::Window {
    // TODO put this somewhere else

public:
    bar() : clock(100, "%I:%M %p %a %e %b %y") {

        // Make this a bar using gtk4-layer-shell
        gtk_layer_init_for_window(gobj());
        gtk_layer_set_layer(gobj(), GTK_LAYER_SHELL_LAYER_BOTTOM);
        gtk_layer_auto_exclusive_zone_enable(gobj());
        gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_TOP, true);
        gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_LEFT, true);
        gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, true);

        box.set_center_widget(clock_label);
        end.append(music);
        end.append(tray_sni.get_widget());
        box.set_end_widget(end);
        set_child(box);

        clock.tick.connect(sigc::mem_fun(clock_label, &Gtk::Label::set_text));
        music.set_track(mpris.get_track());
        music.set_album(mpris.get_album());
        music.set_art(mpris.get_art());
        mpris.track_changed.connect(sigc::mem_fun(music, &mcw::widget::music::set_track));
        mpris.album_changed.connect(sigc::mem_fun(music, &mcw::widget::music::set_album));
        mpris.art_changed.connect(sigc::mem_fun(music, &mcw::widget::music::set_art));

        m_refCssProvider = mcw::utils::read_css("bar.css", get_display());

        // testing
    }
    ~bar() override {}

private:
    mcw::source::clock clock;
    Gtk::Label clock_label;

    Gtk::CenterBox box;
    Gtk::Box end;

    mcw::source::mpris mpris;
    mcw::widget::music music;

    mcw::control::tray_sni tray_sni;

    Glib::RefPtr<Gtk::CssProvider> m_refCssProvider;
};

int main(int argc, char** argv) {
    curl_global_init(CURL_GLOBAL_ALL);
    auto app = Gtk::Application::create("murts.cool.widgets");
    auto r   = app->make_window_and_run<bar>(argc, argv);
    curl_global_cleanup();
    return r;
}
