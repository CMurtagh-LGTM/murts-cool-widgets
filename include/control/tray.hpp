#ifndef CONTROL_TRAY_HPP
#define CONTROL_TRAY_HPP

#include "model/sni.hpp"
#include "widget/tray_item.hpp"

namespace mcw::control {

    class tray_sni {
    public:
        tray_sni();

        Gtk::Widget& get_widget();

    private:
        void add_sni(std::shared_ptr<model::sni> sni);

        model::snw snw;
        widget::tray tray;
    };

}  // namespace mcw::control

#endif  // CONTROL_TRAY_HPP
