// Marcin Brzózka, nr 405499
// Stanisław Dudiak, nr 406903
// Adam Pękala, nr 405380

#include "factory.hpp"
#include <map>
#include <stdexcept>
#include <string>
#include <istream>
#include <sstream>
#include <vector>

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



enum ElementType {
    RAMP, WORKER, STOREHOUSE, LINK
};
struct ParsedLineData {
    ElementType element_type;
    std::map<std::string, std::string> parameters;
};


std::vector<std::string> ParsedLineDataHelper(std::string line, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream token_stream(line);
    while (std::getline(token_stream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}


ParsedLineData parse_line(std::string line) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream token_stream(line);
    char delimiter = ' ';
    while (std::getline(token_stream, token, delimiter)) {
        tokens.push_back(token);
    }

    ElementType element_type;
    if (tokens[0] == "WORKER") {
        element_type = ElementType::WORKER;
    }
    else if (tokens[0] == "LOADING_RAMP") {
        element_type = ElementType::RAMP;
    }
    else if (tokens[0] == "STOREHOUSE") {
        element_type = ElementType::STOREHOUSE;
    }
    else if (tokens[0] == "LINK") {
        element_type = ElementType::LINK;
    }
    else {
        throw std::runtime_error("Unknown input type");
    }

    std::map<std::string, std::string> parameters;
    for (std::size_t t = 1; t < tokens.size(); t++) {
        std::vector<std::string> par = ParsedLineDataHelper(tokens[t], '=');
        parameters.insert(std::pair<std::string, std::string>(par[0], par[1]));
    }
    ParsedLineData parsed_line_data {element_type, parameters};
    return parsed_line_data;
}


Factory load_factory_structure(std::istream& is) {
    Factory factory;
    std::string line;
    std::string::size_type size_type;

    while (std::getline(is, line)) {
        if (line.empty() or line[0] == ';')  {
            continue;
        }
        ParsedLineData parsed_line_data = parse_line(line);

        if (parsed_line_data.element_type == ElementType::RAMP) {
            ElementID ramp_id = std::stoi(parsed_line_data.parameters["id"], &size_type);
            Time delivery_interval = std::stoi(parsed_line_data.parameters["delivery-interval"], &size_type);
            Ramp ramp {ramp_id, delivery_interval};
            factory.add_ramp(std::move(ramp));

        } else if (parsed_line_data.element_type == ElementType::WORKER) {
            ElementID worker_id = std::stoi(parsed_line_data.parameters["id"], &size_type);
            TimeOffset processing_time = std::stoi(parsed_line_data.parameters["processing-time"], &size_type);
            PackageQueueType queue_type = parsed_line_data.parameters["queue-type"] == "FIFO" ? PackageQueueType::FIFO : PackageQueueType::LIFO;
            Worker worker {worker_id, processing_time, std::make_unique<PackageQueue> (queue_type)};
            factory.add_worker(std::move(worker));

        } else if (parsed_line_data.element_type == ElementType::STOREHOUSE) {
            ElementID storehouse_id = std::stoi(parsed_line_data.parameters["id"], &size_type);
            Storehouse storehouse {storehouse_id};
            factory.add_storehouse(std::move(storehouse));

        } else if (parsed_line_data.element_type == ElementType::LINK) {
            std::string src = parsed_line_data.parameters["src"];
            std::string dest = parsed_line_data.parameters["dest"];
            std::vector<std::string> src_tokens = ParsedLineDataHelper(src, '-');
            std::vector<std::string> dest_tokens = ParsedLineDataHelper(dest, '-');
            ElementID src_id = std::stoi(src_tokens[1]);
            ElementID dest_id = std::stoi(dest_tokens[1]);

            if (src_tokens[0] == "worker") {
                auto worker = factory.find_worker_by_id(src_id);
                if (dest_tokens[0] == "store") {
                    auto storehouse = factory.find_storehouse_by_id(dest_id);
                    worker->receiver_preferences_.add_receiver(&(*storehouse));
                } else if (dest_tokens[0] == "worker") {
                    auto second_worker = factory.find_worker_by_id(dest_id);
                    worker->receiver_preferences_.add_receiver(&(*second_worker));
                } else { throw std::logic_error("Unknown data"); }

            } else if (src_tokens[0] == "store") {
                auto ramp = factory.find_ramp_by_id(src_id);
                if (dest_tokens[0] == "worker") {
                    auto worker = factory.find_worker_by_id(dest_id);
                    ramp->receiver_preferences_.add_receiver(&(*worker));
                } else if (dest_tokens[0] == "store") {
                    auto storehouse = factory.find_storehouse_by_id(dest_id);
                    ramp->receiver_preferences_.add_receiver(&(*storehouse));
                } else { throw std::logic_error("Unknown data"); }

            } else if (src_tokens[0] == "ramp") {
                throw std::logic_error("...");

            } else { throw std::logic_error("Unknown data"); }

        } else { throw std::logic_error("Unknown input type"); }
    }
    return factory;
}


std::vector<std::string> LinksHelper(Factory& factory){
    std::vector<std::string> links;
    for(auto it = factory.ramp_begin(); it!=factory.ramp_end(); it++){
        for (auto& ipr : it->receiver_preferences_.get_preferences()) {
            std::stringstream link;
            link << "src=ramp-" << it->get_id();
            switch (ipr.first->get_receiver_type()) {
                case (ReceiverType::WORKER) :
                    link << " dest=worker-" << ipr.first->get_id();
                    break;
                case (ReceiverType::STOREHOUSE) :
                    link << " dest=store-" << ipr.first->get_id();
                    break;
                default:
                    throw std::logic_error("Unknown data");
            }
            links.push_back(link.str());
        }
    }

    for(auto it = factory.worker_begin();it!=factory.worker_end();it++) {
        for (auto& ipr : it->receiver_preferences_.get_preferences()) {
            std::stringstream link;
            link << "src=worker-" << it->get_id();
            switch (ipr.first->get_receiver_type()) {
                case (ReceiverType::WORKER) :
                    link << " dest=worker-" << ipr.first->get_id();
                    break;
                case (ReceiverType::STOREHOUSE) :
                    link << " dest=store-" << ipr.first->get_id();
                    break;
                default:
                    throw std::logic_error("Unknown data");;
            }
            links.push_back(link.str());
        }
    }
    return links;
}


void save_factory_structure(Factory& factory,std::ostream& os) {
    std::stringstream structure;
    structure<<"; == LOADING RAMPS ==\n\n";
    for (auto it = factory.ramp_cbegin(); it !=factory.ramp_cend() ; ++it) {
        structure<<"LOADING_RAMP id="<<it->get_id()<<" delivery-interval="<<it->get_delivery_interval()<<"\n";
    }
    structure<<"\n; == WORKERS ==\n\n";
    for(auto it = factory.worker_cbegin();it!=factory.worker_cend();++it){
        structure<<"WORKER id="<<it->get_id()<<" processing-time="<<it->get_processing_duration()<<" queue-type="<<((it->get_queue()->get_queue_type()==PackageQueueType::LIFO) ? "LIFO" : "FIFO")<<"\n";
    }
    structure<<"\n; == STOREHOUSES ==\n\n";
    for (auto it = factory.storehouse_cbegin(); it != factory.storehouse_cend(); ++it) {
        structure<<"STOREHOUSE id="<<it->get_id()<<"\n";
    }
    structure<<"\n; == LINKS ==\n\n";
    std::vector<std::string> links = LinksHelper(factory);
    for(const auto& s:links){
        structure<<"LINK "<< s <<"\n";
        structure<<"\n";
    }

    os<<structure.str();
}