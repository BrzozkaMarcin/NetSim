#include "package.hpp"
#include "storage_types.hpp"
#include "types.hpp"
#include <iostream>
#include <set>
#include <stdexcept>

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

    PackageQueue fifo_queue(PackageQueueType::FIFO);
    PackageQueue lifo_queue(PackageQueueType::LIFO);
    std::cout<<fifo_queue.empty()<< "\n" << lifo_queue.empty() << "\n";
    std::cout<<fifo_queue.size()<< "\n" << lifo_queue.size() << "\n";
    fifo_queue.push(Package(1));
    fifo_queue.push(Package(2));
    fifo_queue.push(Package(3));
    fifo_queue.push(Package(4));
    fifo_queue.push(Package(5));

    lifo_queue.push(Package(6));
    lifo_queue.push(Package(7));
    lifo_queue.push(Package(8));
    lifo_queue.push(Package(9));
    lifo_queue.push(Package(11));

    
    Package fifo_pop;
    Package lifo_pop;
    fifo_pop = fifo_queue.pop();
    lifo_pop = lifo_queue.pop();
    PackageQueueType tp = fifo_queue.get_queue_type();
    return 0;
}
