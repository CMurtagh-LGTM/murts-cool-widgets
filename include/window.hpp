#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <gtk/gtk.h>

namespace window {

    struct Params {
        int left_margin   = 0;
        int right_margin  = 0;
        int top_margin    = 0;
        int bottom_margin = 0;
    };

    GtkWindow* new_window(GtkApplication* app, Params& params);

}  // namespace window

#endif  // WINDOW_HPP
