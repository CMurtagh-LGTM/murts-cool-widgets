#include "utils/icon.hpp"


#include "gtkmm/icontheme.h"

namespace mcw::utils {

    Glib::RefPtr<Gtk::IconPaintable> lookup_icon(const Glib::ustring& icon_name, int size) {
        Glib::RefPtr<Gtk::IconTheme> static icon_theme = Gtk::IconTheme::create();
        return icon_theme->lookup_icon(icon_name, size);
    }

}  // namespace mcw::utils
