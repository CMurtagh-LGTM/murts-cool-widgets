#include "window.hpp"

#include <gtk-layer-shell.h>

namespace window {

    GtkWindow* new_window(GtkApplication* app, Params& params) {
        // Create a normal GTK window however you like
        GtkWindow* gtk_window = GTK_WINDOW(gtk_application_window_new(app));

        // Before the window is first realized, set it up to be a layer surface
        gtk_layer_init_for_window(gtk_window);

        // Order below normal windows
        gtk_layer_set_layer(gtk_window, GTK_LAYER_SHELL_LAYER_BOTTOM);

        // Push other windows out of the way
        gtk_layer_auto_exclusive_zone_enable(gtk_window);

        // We don't need to get keyboard input
        // gtk_layer_set_keyboard_mode (gtk_window, GTK_LAYER_SHELL_KEYBOARD_MODE_NONE); // NONE is default

        // The margins are the gaps around the window's edges
        // Margins and anchors can be set like this...
        gtk_layer_set_margin(gtk_window, GTK_LAYER_SHELL_EDGE_LEFT, params.left_margin);
        gtk_layer_set_margin(gtk_window, GTK_LAYER_SHELL_EDGE_RIGHT, params.right_margin);
        gtk_layer_set_margin(gtk_window, GTK_LAYER_SHELL_EDGE_TOP, params.top_margin);
        gtk_layer_set_margin(gtk_window, GTK_LAYER_SHELL_EDGE_BOTTOM, params.bottom_margin);

        // ... or like this
        // Anchors are if the window is pinned to each edge of the output
        static const gboolean anchors[] = {TRUE, TRUE, TRUE, FALSE};
        for (int i = 0; i < GTK_LAYER_SHELL_EDGE_ENTRY_NUMBER; i++) {
            gtk_layer_set_anchor(gtk_window, (GtkLayerShellEdge) i, anchors[i]);
        }

        return gtk_window;
    }

}  // namespace window
