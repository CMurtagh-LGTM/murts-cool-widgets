#include "model/menu.hpp"

#include <iostream>  // TODO remove

namespace mcw::model {
    using item_t = sdbus::Struct<int32_t, std::map<std::string, sdbus::Variant>, std::vector<sdbus::Variant>>;

    menu::menu(const std::string& desitation, const std::string& object_path)
        : ProxyInterfaces(sdbus::ServiceName(desitation), sdbus::ObjectPath(object_path)) {
        registerProxy();
    }

    menu::~menu() {
        unregisterProxy();
    }

    void print_layout_rec(item_t item) {
        if (item.get<1>().contains("label")) {
            std::cout << item.get<1>()["label"].get<std::string>() << std::endl;
        }

        if (item.get<1>().contains("children-display")) {
            for (const auto& sub_item : item.get<2>()) {
                print_layout_rec(sub_item.get<item_t>());
            }
        }
    }

    void menu::get_layout() {
        item_t layout = std::get<1>(GetLayout(0, -1, {}));

        for (const auto& sub_item : layout.get<2>()) {
            print_layout_rec(sub_item.get<item_t>());
        }
    }

    void menu::onItemsPropertiesUpdated(
        const std::vector<sdbus::Struct<int32_t, std::map<std::string, sdbus::Variant>>>& updatedProps,
        const std::vector<sdbus::Struct<int32_t, std::vector<std::string>>>& removedProps) {}
    void menu::onLayoutUpdated(const uint32_t& revision, const int32_t& parent) {}
    void menu::onItemActivationRequested(const int32_t& id, const uint32_t& timestamp) {}

}  // namespace mcw::model
