// Marcin Brzózka, nr 405499
// Stanisław Dudiak, nr 406903
// Adam Pękala, nr 405380

#include "factory.hpp"
#include <map>

void Factory::remove_worker(ElementID id) {
    for (auto& ramp : ramps_) {
        for (auto p : ramp.receiver_preferences_.get_preferences()) {
            if (p.first->get_id() == id && p.first->get_receiver_type() == ReceiverType::WORKER) {
                ramp.receiver_preferences_.remove_receiver(p.first);
                break;
            }
        }
    }
    workers_.remove_by_id(id);
}


void Factory::do_deliveries(Time time) {
    for(auto& ramp : ramps_) {
        ramp.deliver_goods(time);
    }
}


void Factory::do_package_passing() {
    for(auto& ramp : ramps_) {
        ramp.send_package();
    }
    for(auto& worker : workers_) {
        worker.send_package();
    }
}


void Factory::do_work(Time time) {
    for(auto& worker : workers_){
        worker.do_work(time);
    }
}