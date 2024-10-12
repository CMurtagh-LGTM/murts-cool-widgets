#pragma once

#include <sdbus-c++/sdbus-c++.h>
#include <sigc++/sigc++.h>

#include "org.freedesktop.DBus.hpp"

namespace mcw::model {

    class dbus : private sdbus::ProxyInterfaces<org::freedesktop::DBus_proxy> {
    private:
        void onNameOwnerChanged(const std::string& name, const std::string& old_owner, const std::string& new_owner) override;
        void onNameLost(const std::string& name) override;
        void onNameAcquired(const std::string& name) override;

    public:
        dbus();
        ~dbus();

        std::vector<std::string> list_names();
        sigc::signal<void(std::string)> new_name;
        sigc::signal<void(std::string)> lost_name;

        bool has_name(const std::string& name);
    };

}  // namespace mcw::model
