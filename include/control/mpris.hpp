#pragma once

#include "model/dbus.hpp"
#include "model/mpris.hpp"
#include "widget/music.hpp"

#include <gtkmm/widget.h>
#include <optional>

namespace mcw::control {

    class mpris {
    public:
        mpris(model::dbus* dbus);
        Gtk::Widget& get_widget();

    private:
        model::dbus* dbus;
        std::optional<source::mpris> mpris_source;
        widget::music music;

        void new_player(const std::string& name);
        void lost_player(const std::string& name);
    };

}  // namespace mcw::control
