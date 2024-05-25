#include "control/tray.hpp"

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
        auto item = tray.append();
        std::string icon_path = "";
        if(sni->has_property("org.kde.StatusNotifierItem", "IconThemePath")){
            icon_path = sni->IconThemePath();
        }
        item->set_icon(sni->IconName(), icon_path);
        item->signal_clicked().connect(sigc::mem_fun(*sni, &mcw::model::sni::activate));
    }

}  // namespace mcw::control
