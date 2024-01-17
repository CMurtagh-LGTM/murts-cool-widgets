#include "utils/css.hpp"

#include <iostream>

namespace mcw::utils {

static void on_parsing_error(const Glib::RefPtr<const Gtk::CssSection>& section, const Glib::Error& error) {
    std::cerr << "on_parsing_error(): " << error.what() << std::endl;
    if (section) {
        const auto file = section->get_file();
        if (file) {
            std::cerr << "  URI = " << file->get_uri() << std::endl;
        }

        auto start_location = section->get_start_location();
        auto end_location   = section->get_end_location();
        std::cerr << "  start_line = " << start_location.get_lines() + 1
                  << ", end_line = " << end_location.get_lines() + 1 << std::endl;
        std::cerr << "  start_position = " << start_location.get_line_chars()
                  << ", end_position = " << end_location.get_line_chars() << std::endl;
    }
}

Glib::RefPtr<Gtk::CssProvider> read_css(const std::string& path, const Glib::RefPtr<Gdk::Display>& display){
    auto m_refCssProvider = Gtk::CssProvider::create();
    Gtk::StyleProvider::add_provider_for_display(display,
                                                 m_refCssProvider,
                                                 GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    m_refCssProvider->signal_parsing_error().connect(
        [](const auto& section, const auto& error) { on_parsing_error(section, error); });
    m_refCssProvider->load_from_path(path);
    return m_refCssProvider;
}

}
