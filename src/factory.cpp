// Marcin Brzózka, nr 405499
// Stanisław Dudiak, nr 406903
// Adam Pękala, nr 405380

#include "factory.hpp"
#include <map>
#include <stdexcept>

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


bool Factory::has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors) const{
    if (node_colors[sender] == NodeColor::VERIFIED) {
        return true;
    }
    node_colors[sender] = NodeColor::VISITED;
    if (sender->receiver_preferences_.get_preferences().empty()) {
        throw std::logic_error("No recipients");
    }
    bool is_reachable = false;

    for (auto& ipr : sender->receiver_preferences_.get_preferences()) {
        if (ipr.first->get_receiver_type() == ReceiverType::STOREHOUSE) {
            is_reachable = true;
        }
        else {
            IPackageReceiver* receiver_ptr = ipr.first;
            auto worker_ptr = dynamic_cast<Worker*>(receiver_ptr);
            auto sendrecv_ptr = dynamic_cast<PackageSender*>(worker_ptr);
            if (sendrecv_ptr == sender) {
                continue;
            }
            is_reachable = true;
            if (node_colors[sendrecv_ptr] == NodeColor::UNVISITED) {
                has_reachable_storehouse(sendrecv_ptr, node_colors);
            }
        }
    }
    node_colors[sender] = NodeColor::VERIFIED;
    if (is_reachable) {
        return true;
    }
    else {
        throw std::logic_error("No access");
    }
}


bool Factory::is_consistent() const {
    std::map<const PackageSender*, NodeColor> colors;
    for (auto& ramp : ramps_) {
        colors.insert(std::pair<const PackageSender*, NodeColor>(&ramp, NodeColor::UNVISITED));
    }
    for (auto& worker : workers_) {
        colors.insert(std::pair<const PackageSender*, NodeColor>(&worker, NodeColor::UNVISITED));
    }

    for (auto& color : colors) {
        try {
            has_reachable_storehouse(color.first, colors);
        }
        catch (const std::exception& err) {
            return false;
        }
    }
    return true;
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