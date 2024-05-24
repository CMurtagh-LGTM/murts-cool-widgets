#include "model/mpris.hpp"

#include "utils/fetch_image.hpp"

// TODO use async versions
namespace mcw::source {

    mpris::mpris()
        : ProxyInterfaces(sdbus::ServiceName("org.mpris.MediaPlayer2.spotify"),
                          sdbus::ObjectPath("/org/mpris/MediaPlayer2")) {
        registerProxy();
    }

    mpris::~mpris() {
        unregisterProxy();
    }

    void mpris::onPropertiesChanged(const sdbus::InterfaceName&,
                                    const std::map<sdbus::PropertyName, sdbus::Variant>& changed_properties,
                                    const std::vector<sdbus::PropertyName>&) {
        if (changed_properties.contains(sdbus::PropertyName("Metadata"))) {
            auto metadata = changed_properties.at(sdbus::PropertyName("Metadata"))
                                .get<std::map<sdbus::PropertyName, sdbus::Variant>>();
            if (metadata.contains(sdbus::PropertyName("xesam:title"))) {
                track_changed.emit(metadata[sdbus::PropertyName("xesam:title")].get<std::string>());
            }
            if (metadata.contains(sdbus::PropertyName("xesam:album"))) {
                album_changed.emit(metadata[sdbus::PropertyName("xesam:album")].get<std::string>());
            }
            if (metadata.contains(sdbus::PropertyName("mpris:artUrl"))) {
                art_changed.emit(utils::fetch_image(metadata[sdbus::PropertyName("mpris:artUrl")].get<std::string>()));
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
        return utils::fetch_image(Metadata()["mpris:artUrl"].get<std::string>());
    }

}  // namespace mcw::source
