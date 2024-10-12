#include "model/dbus.hpp"

namespace mcw::model {

    dbus::dbus()
        : ProxyInterfaces(sdbus::ServiceName("org.freedesktop.DBus"), sdbus::ObjectPath("/org/freedesktop/DBus")) {
        registerProxy();
    }

    dbus::~dbus() {
        unregisterProxy();
    }

    void dbus::onNameOwnerChanged(const std::string& name, const std::string& old_owner, const std::string& new_owner) {
        if (!new_owner.empty() && old_owner.empty()) {
            new_name.emit(name);
        } else if (new_owner.empty() && !old_owner.empty()) {
            lost_name.emit(name);
        }
    }

    void dbus::onNameLost(const std::string&) {}
    void dbus::onNameAcquired(const std::string&) {}

    std::vector<std::string> dbus::list_names() {
        return ListNames();
    }

    bool dbus::has_name(const std::string& name) {
        const std::vector<std::string> names = ListNames();
        return std::find(names.begin(), names.end(), name) != names.end();
    }
}  // namespace mcw::model
