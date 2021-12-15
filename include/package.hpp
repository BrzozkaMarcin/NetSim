#ifndef IMPLEMENTATION_PACKAGE_HPP
#define IMPLEMENTATION_PACKAGE_HPP

#include <set>
#include "types.hpp"

class Package {
public:
    Package();
    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;
    ElementID element;

    ~Package();
};

#endif //IMPLEMENTATION_PACKAGE_HPP