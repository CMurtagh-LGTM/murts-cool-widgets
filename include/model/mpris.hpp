#ifndef MPRIS_HPP
#define MPRIS_HPP

#include <sdbus-c++/sdbus-c++.h>
#include <sigc++/sigc++.h>

#include "org.mpris.MediaPlayer2.hpp"

namespace mcw::source {
    class mpris
        : public sdbus::ProxyInterfaces<org::mpris::MediaPlayer2_proxy,
                                        org::mpris::MediaPlayer2::Player_proxy,
                                        sdbus::Properties_proxy> {
        void onPropertiesChanged(const std::string& interface_name,
                                 const std::map<std::string, sdbus::Variant>& changed_properties,
                                 const std::vector<std::string>& invalidated_properties) override;
        void onSeeked(const int64_t& position) override;

    public:
        mpris();
        ~mpris();
        sigc::signal<void(const int64_t&)> seek;
        sigc::signal<void(const std::string&)> track_changed;
        sigc::signal<void(const std::string&)> album_changed;

        std::string get_track();
        std::string get_album();
    };
}  // namespace mcw::source

#endif  // MPRIS_HPP
