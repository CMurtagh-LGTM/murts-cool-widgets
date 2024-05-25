#include "utils/Introspectable_proxy.hpp"

#include <libxml++/libxml++.h>

namespace mcw::utils {

    Introspectable_proxy::Introspectable_proxy(sdbus::IProxy& proxy) : sdbus::Introspectable_proxy(proxy) {}

    bool Introspectable_proxy::has_property(const std::string& interface, const std::string& property_name) {
        xmlpp::DomParser parser;
        parser.parse_memory(Introspect());

        xmlpp::Node::NodeSet property_decl = parser.get_document()->get_root_node()->find(
            "interface[@name='" + interface + "']/property[@name='" + property_name + "']");

        return !property_decl.empty();
    }

}  // namespace mcw::utils
