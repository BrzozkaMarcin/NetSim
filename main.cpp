#include "package.hpp"
//#include "storage_types.hpp"
#include "types.hpp"
#include <iostream>
#include <set>
#include <stdexcept>

int main() {

    Package pack1;
    Package pack2;
    Package pack3(4);
    ElementID ID_1 = pack1.get_id();
    ElementID ID_2 = pack2.get_id();
    ElementID ID_3 = pack3.get_id();

    std::cout << ID_1 << " " << ID_2 << " " << ID_3 << "\n";
    return 0;
}
