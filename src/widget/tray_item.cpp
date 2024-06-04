#include "widget/tray_item.hpp"

#include "utils/icon.hpp"

namespace mcw::widget {

    tray_item::tray_item() : Glib::ObjectBase("MCWTrayItem"), WidgetName("mcw-tray-item") {
        icon.insert_at_end(*this);

        signal_destroy().connect(sigc::mem_fun(*this, &tray_item::on_container_destroy));
    }

    tray_item::~tray_item() {
        if (!gobj()) {
            return;  // already destroyed
        }

        on_container_destroy();
    }

    void tray_item::on_container_destroy() {
        icon.unparent();
    }

    void tray_item::set_icon(const std::string& icon_name, const std::string& icon_path) {
        if (!utils::has_icon(icon_name)) {
            utils::add_icon_path(icon_path);
        }
        icon.set_paintable(utils::lookup_icon(icon_name, 32));
    }

    Gtk::SizeRequestMode tray_item::get_request_mode_vfunc() const {
        return Gtk::SizeRequestMode::WIDTH_FOR_HEIGHT;
    }

    void tray_item::measure_vfunc(Gtk::Orientation orientation,
                                  int /*for_size*/,
                                  int& minimum,
                                  int& natural,
                                  int& minimum_baseline,
                                  int& natural_baseline) const {
        minimum_baseline = -1;
        natural_baseline = -1;

        if (orientation == Gtk::Orientation::HORIZONTAL) {
            int icon_min, icon_nat, ignore;
            icon.measure(Gtk::Orientation::HORIZONTAL, 30, icon_min, icon_nat, ignore, ignore);
            minimum = icon_min;
            natural = icon_nat;
        }
        else {
            minimum = 30;
            natural = 30;
        }
    }

    void tray_item::size_allocate_vfunc(int width, int height, int /*baseline*/) {
        Gtk::Allocation full_allocation;
        full_allocation.set_x(0);
        full_allocation.set_y(0);
        full_allocation.set_width(width);
        full_allocation.set_height(height);
        icon.size_allocate(full_allocation, 0);
    }

}  // namespace mcw::widget
