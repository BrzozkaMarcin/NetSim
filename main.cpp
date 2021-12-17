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
    pack2.~Package();
    Package pack7;

    std::cout << pack1.get_id() << "\n" << pack2.get_id() << "\n" << pack3.get_id() << "\n";
    std::cout << pack4.get_id() << "\n" << pack5.get_id() << "\n" << pack6.get_id() << "\n" << pack7.get_id() << "\n";
    return 0;
}
