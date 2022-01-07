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