// Marcin Brzózka, nr 405499
// Stanisław Dudiak, nr 406903
// Adam Pękala, nr 405380
#include <nodes.hpp>
#include "helpers.hpp"

void ReceiverPreferences::add_receiver(IPackageReceiver* r){
    preferences_t new_receiver{{std::move(r),1.0}};
    preferences_.merge(new_receiver);
    if(!preferences_.empty()){
        float probability = 1 / static_cast<float>(preferences_.size());
        for (auto& x : preferences_){
            x.second = probability;
        }
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r){
    preferences_.erase(r);
    if(!preferences_.empty()){
        float probability = 1 / static_cast<float>(preferences_.size());
        for (auto& x : preferences_){
            x.second = probability;
        }
    }
}

 IPackageReceiver* ReceiverPreferences::choose_receiver(){
    double p_sum = 0;
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

void Worker::do_work(Time t) {
    if (!q_->empty() and !processing_buffer_.has_value()) {
        start_time_ = t;
        processing_buffer_.emplace(q_->pop());
    }
    if (t - start_time_ + 1 == pd_) {
        push_package(std::move(*processing_buffer_));
        processing_buffer_.reset();
        start_time_ = 0;
    }

}

void Worker::receive_package(Package&& p) {
    q_->push(std::move(p));

}