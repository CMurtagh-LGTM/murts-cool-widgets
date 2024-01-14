#ifndef FETCH_IMAGE
#define FETCH_IMAGE

#include <gdkmm.h>

Glib::RefPtr<Gdk::Texture> fetch_image(const std::string& url);

#endif // FETCH_IMAGE
