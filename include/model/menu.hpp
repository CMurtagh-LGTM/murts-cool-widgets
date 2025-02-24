#pragma once

#include <sdbus-c++/sdbus-c++.h>

#include "com.canonical.dbusmenu.hpp"

namespace mcw::model {

    class menu_item {
    public:
        menu_item(const std::string& label);

        const std::string& get_label() const;

    private:
        std::string label;
    };

    class menu : public sdbus::ProxyInterfaces<com::canonical::dbusmenu_proxy> {
    public:
        menu(const std::string& destination, const std::string& object_path);
        virtual ~menu();

        std::vector<menu_item> get_layout();

        virtual void onItemsPropertiesUpdated(
            const std::vector<sdbus::Struct<int32_t, std::map<std::string, sdbus::Variant>>>& updatedProps,
            const std::vector<sdbus::Struct<int32_t, std::vector<std::string>>>& removedProps) override;
        virtual void onLayoutUpdated(const uint32_t& revision, const int32_t& parent) override;
        virtual void onItemActivationRequested(const int32_t& id, const uint32_t& timestamp) override;
    };

}  // namespace mcw::model
