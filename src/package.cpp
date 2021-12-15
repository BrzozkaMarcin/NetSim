#include "package.hpp"
#include <set>

Package::Package() {
    if (1) {
        element = 1;
    }

};


Package::~Package() {
    freed_IDs.insert(element);
    assigned_IDs.erase(element);
};


