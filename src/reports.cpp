// Marcin Brzózka, nr 405499
// Stanisław Dudiak, nr 406903
// Adam Pękala, nr 405380

#include "reports.hpp"
#include "nodes.hpp"
#include <sstream>
#include <iostream>
#include <algorithm>


std::string type_to_string(PackageQueueType type){
    if(type == PackageQueueType::FIFO){
        return("FIFO");
    }
    else
    {
        return("LIFO");
    }
}

void generate_structure_report(const Factory& f, std::ostream& os){
    // RAMPS
    os << "\n== LOADING RAMPS ==\n" << std::endl;
    std::vector<const Ramp*> ramps;
    for(auto ramp_i = f.ramp_cbegin(); ramp_i != f.ramp_cend();ramp_i++){
        ramps.push_back(&(*ramp_i));
    }
    std::sort(ramps.begin(),ramps.end(),[](const Ramp*& a, const Ramp*& b){return a -> get_id() < b -> get_id();});

    for(auto i = ramps.begin();i != ramps.end(); i++){
        os <<"LOADING RAMP #"<< (*i)-> get_id() << std::endl;
        os <<"  Delivery interval: " << (*i) -> get_delivery_interval() << std::endl;
        os <<"  Receivers:" << std::endl;
        std::vector<const IPackageReceiver*> workers;
        std::vector<const IPackageReceiver*> storehouses;
        for(auto receiver : (*i)->receiver_preferences_.get_preferences()){
            if(receiver.first->get_receiver_type() == ReceiverType::WORKER){
                workers.push_back(receiver.first);
            }
            if(receiver.first->get_receiver_type() == ReceiverType::STOREHOUSE){
                storehouses.push_back(receiver.first);
            }
        }
        std::sort(workers.begin(),workers.end(),[](const IPackageReceiver*& a, const IPackageReceiver*& b){return a -> get_id() < b -> get_id();});
        std::sort(storehouses.begin(),storehouses.end(),[](const IPackageReceiver*& a, const IPackageReceiver*& b){return a -> get_id() < b -> get_id();});

        for(auto receiver : storehouses){
            os <<"    storehouse #" << receiver->get_id() << std::endl;
        }
        for(auto receiver : workers){
            os <<"    worker #" << receiver->get_id() << std::endl;
        }
        os << std::endl;
    }
    // WORKERS
    os << "\n== WORKERS ==\n" << std::endl;
    std::vector<const Worker*> workers_;
    for(auto worker_i = f.worker_cbegin(); worker_i != f.worker_cend();worker_i++){
        workers_.push_back(&(*worker_i));
    }
    std::sort(workers_.begin(), workers_.end(), [](const Worker*& a, const Worker*& b){
        return a->get_id() < b->get_id();
    });
    for(auto i = workers_.begin();i != workers_.end(); i++){
        os <<"WORKER #"<< (*i)-> get_id() << std::endl;
        os <<"  Processing time: " << (*i) -> get_processing_duration() << std::endl;
        os <<"  Queue type: " << type_to_string((*i) ->get_queue()->get_queue_type()) << std::endl;
        os <<"  Receivers:" << std::endl;
        std::vector<const IPackageReceiver*> workers;
        std::vector<const IPackageReceiver*> storehouses;
        for(auto receiver : (*i)->receiver_preferences_.get_preferences()){
            if(receiver.first->get_receiver_type() == ReceiverType::WORKER){
                workers.push_back(receiver.first);
            }
            if(receiver.first->get_receiver_type() == ReceiverType::STOREHOUSE){
                storehouses.push_back(receiver.first);
            }
        }
        std::sort(workers.begin(),workers.end(),[](const IPackageReceiver*& a, const IPackageReceiver*& b){return a -> get_id() < b -> get_id();});
        std::sort(storehouses.begin(),storehouses.end(),[](const IPackageReceiver*& a, const IPackageReceiver*& b){return a -> get_id() < b -> get_id();});

        for(auto receiver : storehouses){
            os <<"    storehouse #" << receiver->get_id() << std::endl;
        }
        for(auto receiver : workers){
            os <<"    worker #" << receiver->get_id() << std::endl;
        }
        os << std::endl;
    }
    // STOREHOUSES
    os << "\n== STOREHOUSES ==\n" << std::endl;
    std::vector<const Storehouse*> storehouses_;
    for(auto storehouse_i = f.storehouse_cbegin(); storehouse_i != f.storehouse_cend();storehouse_i++){
        storehouses_.push_back(&(*storehouse_i));
    }
    std::sort(storehouses_.begin(), storehouses_.end(), [](const Storehouse*& a, const Storehouse*& b){
        return a->get_id() < b->get_id();
    });
    for(auto i = storehouses_.begin();i != storehouses_.end(); i++){
        os <<"STOREHOUSE #"<< (*i)-> get_id() << std::endl;
        os<<std::endl;
    }
}

void generate_simulation_turn_report(const Factory& f,std::ostream& os,Time t){
    os << "=== [ Turn: " << t << " ] ===" << std::endl;
    os << "\n== WORKERS ==\n" << std::endl;
    std::vector<const Worker*> workers_;
    for(auto worker_i = f.worker_cbegin(); worker_i != f.worker_cend();worker_i++){
        workers_.push_back(&(*worker_i));
    }
    std::sort(workers_.begin(), workers_.end(), [](const Worker*& a, const Worker*& b){
        return a->get_id() < b->get_id();
    });
    for (auto i = workers_.cbegin(); i != workers_.cend();i++){
        os << "WORKER #" << (*i) -> get_id() << std::endl;
        // MOZE BYC BLAD
        if((*i) -> get_pbuffer().has_value()){
            os << "  PBuffer: #" << (*i) -> get_pbuffer() -> get_id() << " (pt = " << (*i) -> get_package_processing_start_time() << ")" << std::endl;
        }else{
            os << "  PBuffer: (empty)" << std::endl;
        }
        os << "  Queue:";
        if((*i) -> get_queue() -> empty()){
            os <<" (empty)"<<std::endl;
        }else{
            bool first = true;
            for(auto j  =  (*i) -> get_queue() -> begin(); j != (*i) -> get_queue() -> end(); j++){
                if(first){
                    os << " #" << (*j).get_id();
                    first = false;
                }else{
                    os << ", #" << (*j).get_id();
                }
            }
            os << std::endl;
        }
        if((*i) -> get_sending_buffer().has_value()){
            os <<"  SBuffer: #" << (*i) -> get_sending_buffer() -> get_id() << std::endl;
        }else{
            os <<"  SBuffer: (empty)"<< std::endl;
        }
        os << std::endl;
    }
    os << std::endl;
    os << "== STOREHOUSES =="<< std::endl;
    os << std::endl;
    std::vector<const Storehouse*> storehouses_;
    for(auto storehouse_i = f.storehouse_cbegin(); storehouse_i != f.storehouse_cend();storehouse_i++){
        storehouses_.push_back(&(*storehouse_i));
    }
    std::sort(storehouses_.begin(), storehouses_.end(), [](const Storehouse*& a, const Storehouse*& b){
        return a->get_id() < b->get_id();
    });
    for(auto i = storehouses_.begin(); i != storehouses_.end(); i++){
        os << "STOREHOUSE #" << (*i) -> get_id() << std::endl;
        os << "  Stock:";
        if((*i) -> begin() == (*i) -> end()){
            os << " (empty)" << std::endl;
        }else{
            bool first = true;
            for(auto j = (*i) -> begin(); j != (*i) -> end(); j++){
                if(first){
                    os << " #" << (*j).get_id();
                    first = false;
                }else{
                    os << ", #" << (*j).get_id();
                }
            }
            os << std::endl;
        }
    }
    os << std::endl;
}