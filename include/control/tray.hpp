#pragma once

#include "gtkmm/popover.h"
#include "model/dbus.hpp"
#include "model/sni.hpp"
#include "widget/tray_item.hpp"

namespace mcw::control {

    class tray_sni {
    public:
        tray_sni(model::dbus* dbus);

        Gtk::Widget& get_widget();

    private:
        void add_sni(model::sni::service_t sni);
        void remove_sni(model::sni::service_t sni);

        void clicked(std::shared_ptr<model::sni>& sni);

        struct item_t {
            std::shared_ptr<model::sni> sni;
            Glib::RefPtr<widget::tray_item> item;
            item_t(const model::sni::service_t&);
        };

        std::vector<item_t> items;

        model::snw snw;
        Gtk::Box tray;

        Gtk::Popover popover;
    };

}  // namespace mcw::control
