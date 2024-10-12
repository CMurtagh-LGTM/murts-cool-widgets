#pragma once

#include <sdbus-c++/sdbus-c++.h>
#include <sigc++/sigc++.h>

#include "model/dbus.hpp"
#include "model/menu.hpp"
#include "org.kde.StatusNotifierItem.hpp"
#include "org.kde.StatusNotifierWatcher.hpp"
#include "utils/Introspectable_proxy.hpp"

namespace mcw::model {

    class sni : public sdbus::ProxyInterfaces<org::kde::StatusNotifierItem_proxy, mcw::utils::Introspectable_proxy> {
    public:
        enum class status { passive, active, needs_attention };

        struct service_t {
            std::string destination;
            std::string object_path;
        };

        sni(const service_t&);
        virtual ~sni();

        sigc::signal<void(const std::string&)> icon_changed;
        sigc::signal<void(const status)> status_changed;

        menu get_menu();
        std::string get_name();

    private:
        void onNewTitle() override;
        void onNewIcon() override;
        void onNewAttentionIcon() override;
        void onNewOverlayIcon() override;
        void onNewToolTip() override;
        void onNewStatus(const std::string& status) override;

        std::string service_name;
    };

    class snw : private sdbus::ProxyInterfaces<org::kde::StatusNotifierWatcher_proxy> {
    public:
        snw(const std::string& id, model::dbus* dbus);
        virtual ~snw();

        sigc::signal<void(const sni::service_t&)> item_registered;
        sigc::signal<void(const sni::service_t&)> item_unregistered;

        std::vector<sni::service_t> get_sni_services();

    private:
        void onStatusNotifierItemRegistered(const std::string& service) override;
        void onStatusNotifierItemUnregistered(const std::string& service) override;
        void onStatusNotifierHostRegistered() override;
        void onStatusNotifierHostUnregistered() override;

        std::string host_name;
        std::unique_ptr<sdbus::IConnection> host_connection;

        model::dbus* dbus;
    };
}  // namespace mcw::model
