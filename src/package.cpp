// Marcin Brzózka, nr 405499
// Stanisław Dudiak, nr 406903
// Adam Pękala, nr 405380

#include "package.hpp"
#include <set>
#include <stdexcept>

Package::Package() {
    if (assigned_IDs.empty() and freed_IDs.empty()) {
        _element = 1;
    } else if (not freed_IDs.empty()) {
        _element = *freed_IDs.begin();
        freed_IDs.erase(freed_IDs.begin());
    } else {
        ElementID assigned_IDs_size = (ElementID)assigned_IDs.size();
        for (ElementID i = 1; i < assigned_IDs_size + 1; i++) {
            if (assigned_IDs.find(i) == assigned_IDs.end()) {
                _element = i;
                break;
            }
        _element = *(assigned_IDs.rbegin()) + 1;
        }

    }
    assigned_IDs.insert(_element);
}


Package::Package(ElementID el) {
    if (assigned_IDs.find(el) != assigned_IDs.end()) {
//        try {
//            throw std::invalid_argument("Error: ID exists");
//        } catch (std::invalid_argument& ex) {
//            std::cout << ex.what() << std::endl;
//        }
        throw std::invalid_argument("ID exists");
    }
    else {
        _element = el;
        assigned_IDs.insert(_element);
    }
    if (freed_IDs.find(el) != freed_IDs.end()) {
        freed_IDs.erase(el);
    }
}


Package &Package::operator=(Package &&other) {
    _element = other._element;
    return *this;
}


Package::~Package() {
    freed_IDs.insert(_element);
    assigned_IDs.erase(_element);
}


