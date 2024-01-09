#ifndef MPRIS_HPP
#define MPRIS_HPP

#include <sdbus-c++/sdbus-c++.h>
#include <sigc++/sigc++.h>

#include "org.mpris.MediaPlayer2.hpp"

namespace mcw::source {
    class mpris
        : public sdbus::ProxyInterfaces<org::mpris::MediaPlayer2_proxy, org::mpris::MediaPlayer2::Player_proxy> {
        virtual void onPropertiesChanged(const std::string& interface_name,
                                         const std::map<std::string, sdbus::Variant>& changed_properties,
                                         const std::vector<std::string>& invalidated_properties);
        virtual void onSeeked(const int64_t& position);

    public:
        mpris();
        sigc::signal<void(const int64_t&)> seek;
        sigc::signal<void()> properties_changed;  // TODO probs don't want this in api
    };
}  // namespace mcw::source

#endif  // MPRIS_HPP
