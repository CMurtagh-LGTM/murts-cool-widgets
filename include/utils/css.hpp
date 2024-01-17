#ifndef CSS_HPP
#define CSS_HPP

#include <string>
#include <gtkmm.h>

namespace mcw::utils {
    
    Glib::RefPtr<Gtk::CssProvider> read_css(const std::string& path, const Glib::RefPtr<Gdk::Display>& display);

}

#endif // CSS_HPP
