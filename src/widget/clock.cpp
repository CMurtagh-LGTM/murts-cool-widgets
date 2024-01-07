#include "widget/clock.hpp"

#include <ctime>

namespace widget {

    struct clock_update {
        GtkWidget* widget;
        const char* format;
        int timeout;
    };

    void destroy_clock(GtkWidget*, gpointer _data) {
        clock_update* data = (clock_update*) _data;
        g_source_remove(data->timeout);
        delete data->format;
        delete data;
    }

    gboolean update_clock(gpointer _data) {
        clock_update* data = (clock_update*) _data;

        std::time_t t = std::time(nullptr);

        char buff[100];
        std::strftime(buff, sizeof(buff), data->format, std::localtime(&t));

        gtk_label_set_text(GTK_LABEL(data->widget), buff);

        return true;
    }

    GtkWidget* clock(const char* format) {
        GtkWidget* label = gtk_label_new("");

        clock_update* data = new clock_update{label, format, 0};
        update_clock(data);
        int timeout   = g_timeout_add(1000, update_clock, data);
        data->timeout = timeout;

        g_signal_connect(label, "destroy", G_CALLBACK(destroy_clock), data);

        // TODO clean this mess

        return label;
    }

}  // namespace widget
