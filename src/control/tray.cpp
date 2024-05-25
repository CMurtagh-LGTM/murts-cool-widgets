#include "control/tray.hpp"
#include <iostream> // remove
#include "widget/menu.hpp"

namespace mcw::control {

    tray_sni::tray_sni() : snw("mcw") {
        for (auto& sni : snw.get_snis()) {
            add_sni(sni);
        }

        snw.item_registered.connect(sigc::mem_fun(*this, &mcw::control::tray_sni::add_sni));
    }

    Gtk::Widget& tray_sni::get_widget() {
        return tray;
    }

    void tray_sni::add_sni(std::shared_ptr<model::sni> sni) {
        auto item             = tray.append();
        std::string icon_path = "";
        if (sni->has_property("org.kde.StatusNotifierItem", "IconThemePath")) {
            icon_path = sni->IconThemePath();
        }
        item->set_icon(sni->IconName(), icon_path);
        item->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &mcw::control::tray_sni::clicked), sni));
    }

    void tray_sni::clicked(std::shared_ptr<model::sni> sni) {
        model::menu m_menu                    = sni->get_menu();
        std::vector<model::menu_item> items = m_menu.get_layout();

        widget::menu w_menu;

        for(const model::menu_item& item: items){
            w_menu.add_item(item.get_label());
        }

        popover.set_child(w_menu);
        popover.set_parent(tray); // TODO assertion
        popover.popup();
    }

}  // namespace mcw::control
