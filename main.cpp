#include "package.hpp"
#include "storage_types.hpp"
#include "types.hpp"
#include "factory.hpp"
#include "helpers.hpp"
#include "nodes.hpp"
#include <iostream>
#include <set>
#include <stdexcept>
#include <fstream>
#include <sstream>

int main() {
//    Package pack1;
//    Package pack2;
//    Package pack3(5);
//    Package pack4;
//    Package pack5;
//    Package pack6(Package(12));
//    pack2.~Package();
//    Package pack7;
//    std::cout << pack1.get_id() << "\n" << pack2.get_id() << "\n" << pack3.get_id() << "\n";
//    std::cout << pack4.get_id() << "\n" << pack5.get_id() << "\n" << pack6.get_id() << "\n" << pack7.get_id() << "\n";

//    PackageQueue fifo_queue(PackageQueueType::FIFO);
//    PackageQueue lifo_queue(PackageQueueType::LIFO);
//    std::cout<<fifo_queue.empty()<< "\n" << lifo_queue.empty() << "\n";
//    std::cout<<fifo_queue.size()<< "\n" << lifo_queue.size() << "\n";
//    fifo_queue.push(Package());
//    fifo_queue.push(Package());
//    fifo_queue.push(Package());
//    fifo_queue.push(Package());
//    fifo_queue.push(Package());
//
//    lifo_queue.push(Package());
//    lifo_queue.push(Package());
//    lifo_queue.push(Package());
//    lifo_queue.push(Package());
//    lifo_queue.push(Package());
//
//
//    Package fifo_pop;
//    Package lifo_pop;
//    fifo_pop = fifo_queue.pop();
//    lifo_pop = lifo_queue.pop();

    std::ostringstream oss;
    oss << "LOADING_RAMP id=1 delivery-interval=3" << "\n"
        << "STOREHOUSE id=1" << "\n"
        << "STOREHOUSE id=2" << "\n"
        << "LINK src=ramp-1 dest=store-1" << "\n"
        << "LINK src=ramp-1 dest=store-2" << "\n";

    std::istringstream iss(oss.str());

    Factory factory;
    factory = load_factory_structure(iss);


    return 0;
}
