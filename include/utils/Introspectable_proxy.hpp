#ifndef INTROSPECTABLE_PROXY_HPP
#define INTROSPECTABLE_PROXY_HPP

#include "sdbus-c++/StandardInterfaces.h"

namespace mcw::utils {

    class Introspectable_proxy : public sdbus::Introspectable_proxy {
    public:
        bool has_property(const std::string& interface, const std::string& property_name);

    protected:
        Introspectable_proxy(sdbus::IProxy& proxy);
    };

}  // namespace mcw::utils

#endif  // INTROSPECTABLE_PROXY_HPP
