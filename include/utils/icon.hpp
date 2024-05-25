#ifndef ICON_HPP
#define ICON_HPP

#include "gtkmm/iconpaintable.h"

namespace mcw::utils {

    Glib::RefPtr<Gtk::IconPaintable> lookup_icon(const Glib::ustring& icon_name, int size);

}  // namespace mcw::utils

#endif  // ICON_HPP
