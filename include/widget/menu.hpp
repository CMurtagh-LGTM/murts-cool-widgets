#pragma once

#include "gtkmm/box.h"
#include "gtkmm/button.h"

namespace mcw::widget {

    class menu_item : public Gtk::Button {
    public:
        menu_item(const std::string& label);
    };

    class menu : public Gtk::Box {
    public:
        Glib::RefPtr<menu_item> add_item(const std::string& label);

    private:
        std::vector<Glib::RefPtr<menu_item>> items;
    };

}  // namespace mcw::widget
