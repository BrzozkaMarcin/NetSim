// Marcin Brzózka, nr 405499
// Stanisław Dudiak, nr 406903
// Adam Pękala, nr 405380
#include <nodes.hpp>

void ReceiverPreferences::add_receiver(IPackageReceiver* r){
    preferences_t new_receiver{{std::move(r),1.0}};
    preferences_.merge(new_receiver);
    float probability = 1 / preferences_.size();
    int i = 1;
    for (auto& x : preferences_){
        x.second = probability * i;
        i++;
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r){
    preferences_.erase(r);
    float probability = 1 / preferences_.size();
    int i = 1;
    for (auto& x : preferences_){
        x.second = probability * i;
        i++;
    }
}

 IPackageReceiver* ReceiverPreferences::choose_receiver(){
     
}
