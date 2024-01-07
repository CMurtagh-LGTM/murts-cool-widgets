#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <gtk/gtk.h>

namespace widget {

    // Takes ownership of the cstring
    GtkWidget* clock(const char* format);

}  // namespace widget

#endif  // CLOCK_HPP
