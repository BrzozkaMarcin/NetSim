// Marcin Brzózka, nr 405499
// Stanisław Dudiak, nr 406903
// Adam Pękala, nr 405380
#include <nodes.hpp>

void ReceiverPreferences::add_receiver(IPackageReceiver* r){
    preferences_t new_receiver{{std::move(r),1.0}};
    preferences_.merge(new_receiver);
    float probability = 1 / preferences_.size();
    for (auto& x : preferences_){
        x.second = probability;
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r){
    preferences_.erase(r);
    float probability = 1 / preferences_.size();
    for (auto& x : preferences_){
        x.second = probability;
    }
}

 IPackageReceiver* ReceiverPreferences::choose_receiver(){
    int p_sum = 0;
    auto rand_value = pg_();
    for(const auto& x : preferences_){
        p_sum += x.second;
        if (p_sum >= rand_value){
            return x.first;
        }
    }
    return nullptr;
}

void PackageSender::send_package(){
    if (buffer_.has_value()){
        auto receiver = receiver_preferences_.choose_receiver();
        if (receiver != nullptr){
            receiver->receive_package(std::move(*buffer_));
            buffer_.reset();
        }
    }
    
}

void Ramp::deliver_goods(Time t){
    if(t % di_ == 1){
        push_package(Package());
    }
}