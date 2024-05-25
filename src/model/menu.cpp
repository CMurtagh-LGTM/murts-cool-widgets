#include "model/menu.hpp"

#include <iostream>  // TODO remove

namespace mcw::model {
    using item_t = sdbus::Struct<int32_t, std::map<std::string, sdbus::Variant>, std::vector<sdbus::Variant>>;

    menu_item::menu_item(const std::string& label_) : label(label_) {}

    const std::string& menu_item::get_label() const {
        return label;
    }

    menu::menu(const std::string& desitation, const std::string& object_path)
        : ProxyInterfaces(sdbus::ServiceName(desitation), sdbus::ObjectPath(object_path)) {
        registerProxy();
    }

    menu::~menu() {
        unregisterProxy();
    }

    std::vector<menu_item> menu::get_layout() {
        item_t layout = std::get<1>(GetLayout(0, -1, {}));

        std::vector<menu_item> items;

        for (const auto& sub_item_v : layout.get<2>()) {
            item_t sub_item = sub_item_v.get<item_t>();
            if(sub_item.get<1>().contains("label")){
                items.emplace_back(sub_item.get<1>()["label"].get<std::string>());
            }
        }

        return items;
    }

    void menu::onItemsPropertiesUpdated(
        const std::vector<sdbus::Struct<int32_t, std::map<std::string, sdbus::Variant>>>& updatedProps,
        const std::vector<sdbus::Struct<int32_t, std::vector<std::string>>>& removedProps) {}
    void menu::onLayoutUpdated(const uint32_t& revision, const int32_t& parent) {}
    void menu::onItemActivationRequested(const int32_t& id, const uint32_t& timestamp) {}

}  // namespace mcw::model
