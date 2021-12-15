#ifndef IMPLEMENTATION_PACKAGE_HPP
#define IMPLEMENTATION_PACKAGE_HPP

#include <set>
#include "types.hpp"

class Package {
public:
    Package() {};
    std::set<ElementID> assigned_IDs;
    std::set<ElementID> freed_IDs;


    ~Package() = default;
};

#endif //IMPLEMENTATION_PACKAGE_HPP