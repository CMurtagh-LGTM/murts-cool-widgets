#pragma once

#include "gtkmm/iconpaintable.h"

namespace mcw::utils {

    Glib::RefPtr<Gtk::IconPaintable> lookup_icon(const std::string& icon_name, int size);
    void add_icon_path(const std::string& icon_path);
    bool has_icon(const std::string& icon_name);

}  // namespace mcw::utils
