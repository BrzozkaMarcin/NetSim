#include "package.hpp"
#include <iostream>
#include <set>
#include <stdexcept>

Package::Package() {
    if (assigned_IDs.empty() and freed_IDs.empty()) {
        _element = 1;
    } else if (not freed_IDs.empty()) {
        _element = *freed_IDs.begin();
        freed_IDs.erase(freed_IDs.begin());
    } else {
        _element = *(assigned_IDs.rbegin()) + 1;
    }
    assigned_IDs.insert(_element);
}


Package::Package(ElementID el) {
    if (assigned_IDs.find(el) == assigned_IDs.end()) {
        try {
            throw std::invalid_argument("ID exists");
        } catch (std::invalid_argument& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    else {
        _element = el;
        assigned_IDs.insert(_element);
    }
    if (freed_IDs.find(el) != freed_IDs.end()) {
        freed_IDs.erase(el);
    }
}


Package::Package(Package&& other) {
    _element = other._element;
}


Package &Package::operator=(Package &&other) {
    _element = other._element;
    return *this;
}


Package::~Package() {
    freed_IDs.insert(_element);
    assigned_IDs.erase(_element);
}


