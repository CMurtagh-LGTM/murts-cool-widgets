#include "model/sni.hpp"

#include "sdbus-c++/ProxyInterfaces.h"

namespace mcw::model {

    sni::service_t split_service(const std::string& service) {
        size_t slash_index = service.find("/");

        if (slash_index == std::string::npos) {
            return {service, ""};
        }
        std::string destination = service.substr(0, slash_index);
        std::string object_path = service.substr(slash_index, service.size() - slash_index);

        return {destination, object_path};
    }

    sni::sni(const service_t& service)
        : ProxyInterfaces(sdbus::ServiceName(service.destination), sdbus::ObjectPath(service.object_path))
        , service_name(service.destination) {
        registerProxy();
    }

    sni::~sni() {
        unregisterProxy();
    }

    menu sni::get_menu() {
        return menu(service_name, Menu());
    }

    std::string sni::get_name() {
        return service_name;
    }

    // TODO
    void sni::onNewTitle() {};
    void sni::onNewIcon() {};
    void sni::onNewAttentionIcon() {};
    void sni::onNewOverlayIcon() {};
    void sni::onNewToolTip() {};
    void sni::onNewStatus(const std::string& /*status*/) {};

    snw::snw(const std::string& id, model::dbus* dbus_)
        : ProxyInterfaces(sdbus::ServiceName("org.kde.StatusNotifierWatcher"),
                          sdbus::ObjectPath("/StatusNotifierWatcher")), dbus(dbus_) {

        registerProxy();

        host_name       = "org.freedesktop.StatusNotifierHost-" + std::to_string(getpid()) + "-" + id;
        host_connection = sdbus::createBusConnection(sdbus::ServiceName(host_name));

        RegisterStatusNotifierHost(host_name);
    }

    snw::~snw() {
        unregisterProxy();
    }

    std::vector<sni::service_t> snw::get_sni_services() {
        std::vector<sni::service_t> services;
        for (auto& raw_service : RegisteredStatusNotifierItems()) {
            sni::service_t service = split_service(raw_service);
            if (service.object_path != "" && dbus->has_name(service.destination)) {
                services.push_back(service);
            }
        }
        return services;
    }

    void snw::onStatusNotifierItemRegistered(const std::string& raw_service) {
        auto service = split_service(raw_service);
        if (service.object_path != "") {
            item_registered.emit(service);
        }
    }

    void snw::onStatusNotifierItemUnregistered(const std::string& raw_service) {
        auto service = split_service(raw_service);
        if (service.object_path != "") {
            item_unregistered.emit(service);
        }
    }

    // We don't need these signals
    void snw::onStatusNotifierHostRegistered() {}
    void snw::onStatusNotifierHostUnregistered() {}

}  // namespace mcw::model
