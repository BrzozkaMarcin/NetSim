#ifndef IMPLEMENTATION_NODES_HPP
#define IMPLEMENTATION_NODES_HPP
// Marcin Brzózka, nr 405499
// Stanisław Dudiak, nr 406903
// Adam Pękala, nr 405380
#include <map>
#include "storage_types.hpp"
#include "helpers.hpp"
#include <memory>

enum class ReceiverType{
    WORKER, STOREHOUSE
};

#include "types.hpp"
#include "package.hpp"

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

class ReceiverPreferences{
public:
    ReceiverPreferences(ProbabilityGenerator pg = probability_generator) : pg_(pg){}

    using preferences_t = std::map<IPackageReceiver*,double>;
    using const_iterator = preferences_t::const_iterator;

    const_iterator begin(){return preferences_.begin();}
    const_iterator end(){return preferences_.end();}
    const_iterator cbegin(){return preferences_.cbegin();}
    const_iterator cend(){return preferences_.cend();}

    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();
    const preferences_t& get_preferences() const{return preferences_;}

private:
    preferences_t preferences_;
    ProbabilityGenerator pg_;
};

class PackageSender{
public:
    PackageSender(PackageSender&& other) = default;
    PackageSender() = default;
    void send_package();
    ReceiverPreferences receiver_preferences_;
    const std::optional<Package>& get_sending_buffer() const {return buffer_;}

protected:
    void push_package(Package&& package){buffer_.emplace(std::move(package));}
private:
    std::optional<Package> buffer_;
    
};


class Ramp : public PackageSender{
public:
    Ramp(ElementID id, TimeOffset di) : id_(id),di_(di) {}
    void deliver_goods(Time t);
    TimeOffset get_delivery_interval() const{return di_;}
    ElementID get_id() const{return id_;}
private:
    ElementID id_;
    TimeOffset di_;

};

class Worker : public IPackageReceiver , public PackageSender{
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) :  pd_(pd), worker_id_(id), q_(std::move(q)) {}

    void do_work(Time t);

    TimeOffset get_processing_duration() const { return pd_; }
    Time get_package_processing_start_time() const { return start_time_; }
    ElementID get_id() const override { return worker_id_; }

    void receive_package(Package&& p) override;

    ReceiverType get_receiver_type() const override { return ReceiverType::WORKER; }
    IPackageQueue* get_queue() const {return q_.get();}
    std::optional<Package> get_processing_buffer() {return processing_buffer_; }

    bool is_pbuffer() const { return processing_buffer_.has_value();}
    const std::optional<Package>& get_pbuffer() const {return processing_buffer_; }

    const_iterator begin() const override {return q_->begin();}
    const_iterator end() const override {return q_->end();}
    const_iterator cbegin() const override {return q_->cbegin();}
    const_iterator cend() const override {return q_->cend();}

private:
    TimeOffset pd_;
    ElementID worker_id_;
    Time start_time_ = 0;
    std::unique_ptr<IPackageQueue> q_;
    std::optional<Package> processing_buffer_;
};

class Storehouse : public IPackageReceiver {
public:
    explicit Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> ptr = std::make_unique<PackageQueue>(PackageQueueType::LIFO)) : storehouse_id_(id), ptr_(std::move(ptr)) {}
    ElementID get_id() const override { return storehouse_id_; }
    void receive_package(Package &&p) override { ptr_->push(std::move(p)); };
    ReceiverType get_receiver_type() const override { return ReceiverType::STOREHOUSE;}


    const_iterator begin() const override {return ptr_->begin();}
    const_iterator end() const override {return ptr_->end();}
    const_iterator cbegin() const override {return ptr_->cbegin();}
    const_iterator cend() const override {return ptr_->cend();}

private:
    ElementID storehouse_id_;
    std::unique_ptr<IPackageStockpile> ptr_;
};
#endif //IMPLEMENTATION_NODES_HPP