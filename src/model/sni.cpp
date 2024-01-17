#include "model/sni.hpp"

#include <utility>

#include "sdbus-c++/ProxyInterfaces.h"

namespace mcw::model {

    sni::sni(const std::string& destination, const std::string& object_path)
        : ProxyInterfaces(sdbus::createDefaultBusConnection(), destination, object_path) {
        registerProxy();
    }

    sni::~sni() {
        if (hasProxy()) {
            unregisterProxy();
        }
    }

    // TODO
    void sni::onNewTitle(){};
    void sni::onNewIcon(){};
    void sni::onNewAttentionIcon(){};
    void sni::onNewOverlayIcon(){};
    void sni::onNewToolTip(){};
    void sni::onNewStatus(const std::string& status){};

    std::pair<std::string, std::string> split_service(const std::string& service) {
        int slash_index = service.find("/");

        std::string destination = service.substr(0, slash_index);
        std::string object_path = service.substr(slash_index, service.size() - slash_index);

        return std::make_pair(destination, object_path);
    }

    snw::snw(const std::string& id)
        : ProxyInterfaces(sdbus::createDefaultBusConnection(),
                          "org.kde.StatusNotifierWatcher",
                          "/StatusNotifierWatcher") {

        registerProxy();

        host_name       = "org.freedesktop.StatusNotifierHost-" + std::to_string(getpid()) + "-" + id;
        host_connection = sdbus::createDefaultBusConnection(host_name);

        RegisterStatusNotifierHost(host_name);

        for (auto& service : RegisteredStatusNotifierItems()) {
            auto [destination, object_path] = split_service(service);
            snis.emplace_back(destination, object_path);
        }
    }

    snw::~snw() {
        unregisterProxy();
    }

    std::vector<sni>& snw::get_snis() {
        return snis;
    }

    void snw::onStatusNotifierItemRegistered(const std::string& service) {
        auto [destination, object_path] = split_service(service);
        sni& s                          = snis.emplace_back(destination, object_path);

        item_registered.emit(s);
    }

    void snw::onStatusNotifierItemUnregistered(const std::string& service) {
        // TODO find and remove item from snis
        item_unregistered.emit(service);
    }

    // We don't need these signals
    void snw::onStatusNotifierHostRegistered() {}
    void snw::onStatusNotifierHostUnregistered() {}

}  // namespace mcw::model
