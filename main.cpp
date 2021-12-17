#include "package.hpp"
//#include "storage_types.hpp"
#include "types.hpp"
#include <iostream>
#include <set>
#include <stdexcept>

int main() {

    Package pack1;
    Package pack2;
    Package pack3(5);
    Package pack4;
    Package pack5;
    Package pack6(Package(12));

    return 0;
}
