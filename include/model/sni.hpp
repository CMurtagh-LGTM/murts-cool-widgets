#ifndef SNI_HPP
#define SNI_HPP

#include <sdbus-c++/sdbus-c++.h>
#include <sigc++/sigc++.h>
#include <vector>

#include "model/menu.hpp"
#include "org.kde.StatusNotifierItem.hpp"
#include "org.kde.StatusNotifierWatcher.hpp"
#include "utils/Introspectable_proxy.hpp"

namespace mcw::model {

    class sni : public sdbus::ProxyInterfaces<org::kde::StatusNotifierItem_proxy, mcw::utils::Introspectable_proxy> {
    public:
        enum class status { passive, active, needs_attention };

        sni(const std::string& destination, const std::string& object_path);
        virtual ~sni();

        sigc::signal<void(const std::string&)> icon_changed;
        sigc::signal<void(const status)> status_changed;

        menu get_menu();

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
        snw(const std::string& id);
        virtual ~snw();

        sigc::signal<void(std::shared_ptr<sni>)> item_registered;
        sigc::signal<void(const std::string&)> item_unregistered;

        std::vector<std::shared_ptr<sni>>& get_snis();

    private:
        void onStatusNotifierItemRegistered(const std::string& service) override;
        void onStatusNotifierItemUnregistered(const std::string& service) override;
        void onStatusNotifierHostRegistered() override;
        void onStatusNotifierHostUnregistered() override;

        std::string host_name;
        std::unique_ptr<sdbus::IConnection> host_connection;

        std::vector<std::shared_ptr<sni>> snis;
    };
}  // namespace mcw::model

#endif  // SNI_HPP
