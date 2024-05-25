#include "widget/menu.hpp"

namespace mcw::widget {

    menu_item::menu_item(const std::string& label_) : Gtk::Button(label_) {}

    Glib::RefPtr<menu_item> menu::add_item(const std::string& label) {
        Glib::RefPtr<menu_item> item = items.emplace_back(std::make_shared<menu_item>(label));
        append(*item);
        return item;
    }

}  // namespace mcw::widget
