#include "control/mpris.hpp"

#include <iostream>

namespace mcw::control {

    mpris::mpris(model::dbus* dbus_) : dbus(dbus_) {
        music.set_track("Not");
        music.set_album("Connected");
        music.set_art(Glib::RefPtr<Gdk::Texture>());

        for (const auto& name : dbus->list_names()) {
            if (name == "org.mpris.MediaPlayer2.spotify") {
                new_player(name);
            }
        }
        dbus->new_name.connect(sigc::mem_fun(*this, &mcw::control::mpris::new_player));
        dbus->lost_name.connect(sigc::mem_fun(*this, &mcw::control::mpris::lost_player));
    }

    Gtk::Widget& mpris::get_widget() {
        return music;
    }

    void mpris::new_player(const std::string& name) {
        if (!name.starts_with("org.mpris.MediaPlayer2") || name == "org.mpris.MediaPlayer2.playerctld") {
            return;
        }
        assert(!mpris_source);

        mpris_source.emplace(name);

        std::cout << mpris_source->get_track() << std::endl;

        music.set_track(mpris_source->get_track());
        music.set_album(mpris_source->get_album());
        music.set_art(mpris_source->get_art());
        mpris_source->track_changed.connect(sigc::mem_fun(music, &mcw::widget::music::set_track));
        mpris_source->album_changed.connect(sigc::mem_fun(music, &mcw::widget::music::set_album));
        mpris_source->art_changed.connect(sigc::mem_fun(music, &mcw::widget::music::set_art));
    }

    void mpris::lost_player(const std::string& name) {
        if (name != "org.mpris.MediaPlayer2.spotify") {
            return;
        }
        assert(mpris_source);

        mpris_source.reset();

        music.set_track("Not");
        music.set_album("Connected");
        music.set_art(Glib::RefPtr<Gdk::Texture>());
    }

}  // namespace mcw::control
