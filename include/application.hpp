#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <functional>
#include <gtk/gtk.h>

namespace application {

    struct Params {};

    int application(int argc, char** argv, Params& params, std::function<void(GtkApplication*)> callback);

}  // namespace application

#endif  // APPLICATION_HPP
