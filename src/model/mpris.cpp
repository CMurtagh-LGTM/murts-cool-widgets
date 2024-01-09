#include "model/mpris.hpp"

#include "org.mpris.MediaPlayer2.hpp"

namespace mcw::source {

    mpris::mpris()
        : ProxyInterfaces(sdbus::createDefaultBusConnection(),
                          "org.mpris.MediaPlayer2.spotify",
                          "/org/mpris/MediaPlayer2") {}

    void mpris::onPropertiesChanged(const std::string& interface_name,
                                    const std::map<std::string, sdbus::Variant>& changed_properties,
                                    const std::vector<std::string>& invalidated_properties) {
        properties_changed.emit();
    }

    void mpris::onSeeked(const int64_t& position) {
        seek.emit(position);
    }

}  // namespace mcw::source
