#ifndef IMPLEMENTATION_NODES_HPP
#define IMPLEMENTATION_NODES_HPP
// Marcin Brzózka, nr 405499
// Stanisław Dudiak, nr 406903
// Adam Pękala, nr 405380
#include <map> 
#include "types.hpp"
#include "package.hpp"
class PackageSender{
public:
    PackageSender(PackageSender&& other) = default;
    void send_package();
    ReceiverPreferences receiver_preferences_;
    const std::optional<Package>& get_sending_buffer() const {return buffer_;}

protected:
    void push_package(Package&& package){buffer_.emplace(std::move(package));}
private:
    std::optional<Package> buffer_;
    
};

class ReceiverPreferences{
public:
    ReceiverPreferences(ProbabilityGenerator pg) : pg_(pg){}

    using preferences_t = std::map<IPackageReceiver*,double>;
    using const_iterator = preferences_t::const_iterator;

    const_iterator begin(){return preferences_.begin();}
    const_iterator end(){return preferences_.end();}
    const_iterator cbegin(){return preferences_.cbegin();}
    const_iterator cend(){return preferences_.cend();}

    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();
    const preferences_t& get_preferences() const{return preferences_};
    
private:
    preferences_t preferences_;
    ProbabilityGenerator pg_;
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