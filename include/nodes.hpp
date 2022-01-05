#ifndef IMPLEMENTATION_NODES_HPP
#define IMPLEMENTATION_NODES_HPP
// Marcin Brzózka, nr 405499
// Stanisław Dudiak, nr 406903
// Adam Pękala, nr 405380
#include <map> 
class PackageSender{
public:
    RecieverPreferences reciever_preferences_;
    void send_package();
    
};

class RecieverPreferences{
public:
    RecieverPreferences(ProbabilityGenerator pg);
    using preferences_t = std::map<IPackageReciever*,double>;
    using const_iterator = preferences_t::const_iterator;
    preferences_t preferences_;
    const_iterator begin(){return preferences_.begin();}
    const_iterator end(){return preferences_.end();}
    const_iterator cbegin(){return preferences_.cbegin();}
    const_iterator cend(){return preferences_.cend();}
    void add_reciever(IpackageReciever* r);
    void remove_reciever(IpackageReciever* r);
    IpackageReciever* choose_reciever();
    preferences_t& get_preferences()

};


#endif //IMPLEMENTATION_NODES_HPP