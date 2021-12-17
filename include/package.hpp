#ifndef IMPLEMENTATION_PACKAGE_HPP
#define IMPLEMENTATION_PACKAGE_HPP

#include "types.hpp"
#include <set>

class Package {
public:
    explicit Package();
    explicit Package(ElementID el);
    Package(Package&& other);

    Package& operator=(Package&& other);
    ElementID get_id() const {return _element;}

    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;
    ElementID _element{};

    ~Package();
};

#endif //IMPLEMENTATION_PACKAGE_HPP