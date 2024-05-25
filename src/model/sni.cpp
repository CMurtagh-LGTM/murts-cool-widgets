#include "model/sni.hpp"

#include <utility>

#include "model/menu.hpp"
#include "sdbus-c++/ProxyInterfaces.h"

namespace mcw::model {

    std::pair<std::string, std::string> split_service(const std::string& service) {
        int slash_index = service.find("/");

        std::string destination = service.substr(0, slash_index);
        std::string object_path = service.substr(slash_index, service.size() - slash_index);

        return std::make_pair(destination, object_path);
    }

    sni::sni(const std::string& destination, const std::string& object_path)
        : ProxyInterfaces(sdbus::ServiceName(destination), sdbus::ObjectPath(object_path)), service_name(destination) {
        registerProxy();
    }

    sni::~sni() {
        unregisterProxy();
    }

    void sni::activate() {
        menu m = menu(service_name, Menu());
        m.get_layout();
    }

    // TODO
    void sni::onNewTitle() {};
    void sni::onNewIcon() {};
    void sni::onNewAttentionIcon() {};
    void sni::onNewOverlayIcon() {};
    void sni::onNewToolTip() {};
    void sni::onNewStatus(const std::string& /*status*/) {};

    snw::snw(const std::string& id)
        : ProxyInterfaces(sdbus::ServiceName("org.kde.StatusNotifierWatcher"),
                          sdbus::ObjectPath("/StatusNotifierWatcher")) {

        registerProxy();

        host_name       = "org.freedesktop.StatusNotifierHost-" + std::to_string(getpid()) + "-" + id;
        host_connection = sdbus::createBusConnection(sdbus::ServiceName(host_name));

        RegisterStatusNotifierHost(host_name);

        for (auto& service : RegisteredStatusNotifierItems()) {
            auto [destination, object_path] = split_service(service);
            snis.push_back(std::make_shared<sni>(destination, object_path));
        }
    }

    snw::~snw() {
        unregisterProxy();
    }

    std::vector<std::shared_ptr<sni>>& snw::get_snis() {
        return snis;
    }

    void snw::onStatusNotifierItemRegistered(const std::string& service) {
        auto [destination, object_path] = split_service(service);
        snis.push_back(std::make_shared<sni>(destination, object_path));
        std::shared_ptr<sni>& s = snis.back();

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
