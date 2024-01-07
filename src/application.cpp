#include "application.hpp"

#include <gtk/gtk.h>

namespace application {

    void activate(GtkApplication* app, void* _data) {
        std::function<void(GtkApplication*)>* callback = (std::function<void(GtkApplication*)>*) _data;
        callback->operator()(app);
    }

    int application(int argc, char** argv, Params& params, std::function<void(GtkApplication*)> callback) {
        GtkApplication* app = gtk_application_new("murts.cool.widgets", G_APPLICATION_DEFAULT_FLAGS);  // TODO service?
        g_signal_connect(app, "activate", G_CALLBACK(activate), &callback);
        int status = g_application_run(G_APPLICATION(app), argc, argv);
        g_object_unref(app);
        return status;
    }
}  // namespace application
