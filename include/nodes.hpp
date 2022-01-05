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

class IPackageReceiver {
public:
    virtual void receive_package(Package&& p) = 0;
    virtual ElementID get_id() const = 0;
    virtual ReceiverType get_receiver_type() const = 0;

    using const_iterator = IPackageStockpile::const_iterator;

    virtual const_iterator begin() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator end() const = 0 ;
    virtual const_iterator cend() const = 0;

    virtual ~IPackageReceiver() = default;
};

#endif //IMPLEMENTATION_NODES_HPP