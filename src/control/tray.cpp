#include "control/tray.hpp"

#include "widget/menu.hpp"

namespace mcw::control {

    tray_sni::tray_sni() : snw("mcw") {
        for (auto& service : snw.get_sni_services()) {
            add_sni(service);
        }

        snw.item_registered.connect(sigc::mem_fun(*this, &mcw::control::tray_sni::add_sni));
    }


    tray_sni::item_t::item_t(const model::sni::service_t& service) : sni(std::make_shared<model::sni>(service)), item(std::make_shared<widget::tray_item>()) {}

    Gtk::Widget& tray_sni::get_widget() {
        return tray;
    }

    void tray_sni::add_sni(model::sni::service_t service) {
        items.emplace_back(service);
        auto& [sni, item]     = items.back();

        tray.append(*item);

        std::string icon_path = "";
        if (sni->has_property("org.kde.StatusNotifierItem", "IconThemePath")) {
            icon_path = sni->IconThemePath();
        }
        item->set_icon(sni->IconName(), icon_path);

        item->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &mcw::control::tray_sni::clicked), sni));
    }

    void tray_sni::clicked(std::shared_ptr<model::sni>& sni) {
        model::menu m_menu                  = sni->get_menu();
        std::vector<model::menu_item> items = m_menu.get_layout();

        widget::menu w_menu;

        for (const model::menu_item& item : items) {
            w_menu.add_item(item.get_label());
        }

        popover.set_child(w_menu);
        popover.set_parent(tray);  // TODO assertion
        popover.popup();
    }

}  // namespace mcw::control
