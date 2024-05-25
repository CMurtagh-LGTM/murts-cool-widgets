#include "utils/icon.hpp"

#include <algorithm>

#include "gtkmm/icontheme.h"

namespace mcw::utils {

    Glib::RefPtr<Gtk::IconTheme> static icon_theme = Gtk::IconTheme::create();

    Glib::RefPtr<Gtk::IconPaintable> lookup_icon(const std::string& icon_name, int size) {
        return icon_theme->lookup_icon(icon_name, size);
    }

    void add_icon_path(const std::string& icon_path) {
        if (icon_path == "") {
            return;
        }

        std::vector<std::string> search_path = icon_theme->get_search_path();
        if (std::find(search_path.begin(), search_path.end(), icon_path) < search_path.end()) {
            return;
        }

        icon_theme->add_search_path(icon_path);
    }

    bool has_icon(const std::string& icon_name) {
        return icon_theme->has_icon(icon_name);
    }

}  // namespace mcw::utils
