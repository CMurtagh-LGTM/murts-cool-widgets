#ifndef SNI_HPP
#define SNI_HPP

#include <sdbus-c++/sdbus-c++.h>
#include <sigc++/sigc++.h>
#include <vector>

#include "org.kde.StatusNotifierItem.hpp"
#include "org.kde.StatusNotifierWatcher.hpp"

namespace mcw::model {

    class sni : public sdbus::ProxyInterfaces<org::kde::StatusNotifierItem_proxy> {
    public:
        sni(const std::string& destination, const std::string& object_path);
        sni(sni&&) = default;

        ~sni();

    private:
        void onNewTitle() override;
        void onNewIcon() override;
        void onNewAttentionIcon() override;
        void onNewOverlayIcon() override;
        void onNewToolTip() override;
        void onNewStatus(const std::string& status) override;
    };

    class snw : private sdbus::ProxyInterfaces<org::kde::StatusNotifierWatcher_proxy> {
    public:
        snw(const std::string& id);
        ~snw();

        sigc::signal<void(sni&)> item_registered;
        sigc::signal<void(const std::string&)> item_unregistered;

        std::vector<sni>& get_snis();

    private:
        void onStatusNotifierItemRegistered(const std::string& service) override;
        void onStatusNotifierItemUnregistered(const std::string& service) override;
        void onStatusNotifierHostRegistered() override;
        void onStatusNotifierHostUnregistered() override;

        std::string host_name;
        std::unique_ptr<sdbus::IConnection> host_connection;

        std::vector<sni> snis;
    };
}  // namespace mcw::model

#endif  // SNI_HPP
