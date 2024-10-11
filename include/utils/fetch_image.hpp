#pragma once

#include <gdkmm.h>

namespace mcw::utils {

    Glib::RefPtr<Gdk::Texture> fetch_image(const std::string& url);

}
