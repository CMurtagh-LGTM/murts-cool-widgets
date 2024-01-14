#include "model/mpris.hpp"

#include "utils/fetch_image.hpp"

#include "org.mpris.MediaPlayer2.hpp"

// TODO use async versions
namespace mcw::source {

    mpris::mpris()
        : ProxyInterfaces(sdbus::createDefaultBusConnection(),
                          "org.mpris.MediaPlayer2.spotify",
                          "/org/mpris/MediaPlayer2") {
        registerProxy();
    }

    mpris::~mpris() {
        unregisterProxy();
    }

    void mpris::onPropertiesChanged(const std::string&,
                                    const std::map<std::string, sdbus::Variant>& changed_properties,
                                    const std::vector<std::string>&) {
        if(changed_properties.contains("Metadata")){
            auto metadata = changed_properties.at("Metadata").get<std::map<std::string, sdbus::Variant>>();
            if (metadata.contains("xesam:title")) {
                track_changed.emit(metadata["xesam:title"].get<std::string>());
            }
            if (metadata.contains("xesam:album")) {
                album_changed.emit(metadata["xesam:album"].get<std::string>());
            }
            if (metadata.contains("mpris:artUrl")) {
                art_changed.emit(fetch_image(metadata["mpris:artUrl"].get<std::string>()));
            }
        }
    }

    void mpris::onSeeked(const int64_t& position) {
        seek.emit(position);
    }

    std::string mpris::get_track() {
        return Metadata()["xesam:title"].get<std::string>();
    }

    std::string mpris::get_album() {
        return Metadata()["xesam:album"].get<std::string>();
    }

    Glib::RefPtr<Gdk::Texture> mpris::get_art() {
        return fetch_image(Metadata()["mpris:artUrl"].get<std::string>());
    }

}  // namespace mcw::source
