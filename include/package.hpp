#ifndef IMPLEMENTATION_PACKAGE_HPP
#define IMPLEMENTATION_PACKAGE_HPP

// Marcin Brzózka, nr 405499
// Stanisław Dudiak, nr 406903
// Adam Pękala, nr 405380

#include "types.hpp"
#include <set>

class Package {
public:
    Package();
    Package(ElementID el);
    Package(Package&& other) : _element(other._element) {};

    Package& operator=(Package&& other);
    ElementID get_id() const {return _element;}

    inline static std::set<ElementID> assigned_IDs;
    inline static std::set<ElementID> freed_IDs;

    ~Package();

private:
    ElementID _element{};
};

#endif //IMPLEMENTATION_PACKAGE_HPP