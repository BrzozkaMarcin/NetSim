#include "package.hpp"
#include <set>

Package::Package() {
    if (assigned_IDs.empty()) {
        element = 1;
        assigned_IDs.insert(element);
    } else if (freed_IDs.empty() and ...) {
        ...
    }

};


Package::~Package() {
    freed_IDs.insert(element);
    assigned_IDs.erase(element);
};


