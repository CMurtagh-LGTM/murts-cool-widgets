#include "source/clock.hpp"

#include <ctime>
#include <glibmm/main.h>
#include <sigc++/sigc++.h>

namespace mcw::source {

    clock::clock(int interval, const std::string& format_) : format(format_) {
        Glib::signal_timeout().connect(sigc::mem_fun(*this, &clock::timeout_handler), interval);
    }

    bool clock::timeout_handler() {
        // Get current time and format it into a buffer
        std::time_t t = std::time(nullptr);
        char buff[100];
        std::strftime(buff, sizeof(buff), format.c_str(), std::localtime(&t));

        tick.emit(buff);

        return true;
    }

}  // namespace mcw::source
