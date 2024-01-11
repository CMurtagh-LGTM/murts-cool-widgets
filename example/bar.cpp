#include <gtk4-layer-shell.h>
#include <gtkmm.h>
#include <iostream>

#include "model/clock.hpp"
#include "model/mpris.hpp"
#include "widget/music.hpp"

class bar : public Gtk::Window {
    // TODO put this somewhere else
    void on_parsing_error(const Glib::RefPtr<const Gtk::CssSection>& section, const Glib::Error& error) {
        std::cerr << "on_parsing_error(): " << error.what() << std::endl;
        if (section) {
            const auto file = section->get_file();
            if (file) {
                std::cerr << "  URI = " << file->get_uri() << std::endl;
            }

            auto start_location = section->get_start_location();
            auto end_location   = section->get_end_location();
            std::cerr << "  start_line = " << start_location.get_lines() + 1
                      << ", end_line = " << end_location.get_lines() + 1 << std::endl;
            std::cerr << "  start_position = " << start_location.get_line_chars()
                      << ", end_position = " << end_location.get_line_chars() << std::endl;
        }
    }

public:
    bar() : clock(100, "%I:%M %p %a %e %b %y") {

        // Make this a bar using gtk4-layer-shell
        gtk_layer_init_for_window(gobj());
        gtk_layer_set_layer(gobj(), GTK_LAYER_SHELL_LAYER_BOTTOM);
        gtk_layer_auto_exclusive_zone_enable(gobj());
        gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_TOP, true);
        gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_LEFT, true);
        gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, true);

        box.append(clock_label);
        box.append(music);
        set_child(box);

        clock.tick.connect(sigc::mem_fun(clock_label, &Gtk::Label::set_text));
        music.set_track(mpris.get_track());
        music.set_album(mpris.get_album());
        mpris.track_changed.connect(sigc::mem_fun(music, &mcw::widget::music::set_track));
        mpris.album_changed.connect(sigc::mem_fun(music, &mcw::widget::music::set_album));

        // Load extra CSS file.
        m_refCssProvider = Gtk::CssProvider::create();
#if HAS_STYLE_PROVIDER_ADD_PROVIDER_FOR_DISPLAY
        Gtk::StyleProvider::add_provider_for_display(get_display(),
                                                     m_refCssProvider,
                                                     GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
#else
        Gtk::StyleContext::add_provider_for_display(get_display(),
                                                    m_refCssProvider,
                                                    GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
#endif

        m_refCssProvider->signal_parsing_error().connect(
            [this](const auto& section, const auto& error) { on_parsing_error(section, error); });
        m_refCssProvider->load_from_path("bar.css");
    }
    ~bar() override {}

private:
    mcw::source::clock clock;
    Gtk::Label clock_label;

    Gtk::Box box;

    mcw::source::mpris mpris;
    mcw::widget::music music;

    Glib::RefPtr<Gtk::CssProvider> m_refCssProvider;
};

int main(int argc, char** argv) {
    auto app = Gtk::Application::create("murts.cool.widgets");

    return app->make_window_and_run<bar>(argc, argv);
}
