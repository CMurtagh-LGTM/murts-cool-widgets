#ifndef TRAY_ITEM_HPP
#define TRAY_ITEM_HPP

#include "gtkmm/box.h"
#include "gtkmm/picture.h"
#include "gtkmm/button.h"
#include "utils/WidgetName.hpp"

namespace mcw::widget {
    class tray_item
        : public utils::WidgetName
        , public Gtk::Button {
    public:
        tray_item();
        ~tray_item() override;

        void set_icon(const std::string& new_icon, const std::string& icon_path = "");

    protected:
        Gtk::SizeRequestMode get_request_mode_vfunc() const override;
        void measure_vfunc(Gtk::Orientation orientation,
                           int for_size,
                           int& minimum,
                           int& natural,
                           int& minimum_baseline,
                           int& natural_baseline) const override;
        void size_allocate_vfunc(int width, int height, int baseline) override;

        // Signal handler:
        void on_container_destroy();

    private:
        Gtk::Picture icon;
    };

    class tray : public Gtk::Box {
    public:
        Glib::RefPtr<tray_item> append();

    private:
        std::vector<Glib::RefPtr<tray_item>> items;
    };
}  // namespace mcw::widget

#endif  // TRAY_ITEM_HPP
