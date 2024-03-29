#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <sigc++/signal.h>
#include <string>

namespace mcw::source {

    class clock {
    public:
        clock(int interval, const std::string& format);
        sigc::signal<void(const std::string&)> tick;

    private:
        bool timeout_handler();
        std::string format;
    };

}  // namespace mcw::source

#endif  // CLOCK_HPP
