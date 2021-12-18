#ifndef IMPLEMENTATION_STORAGE_TYPES_HPP
#define IMPLEMENTATION_STORAGE_TYPES_HPP

#include <list>
#include "package.hpp"

enum class PackageQueueType{
    FIFO, LIFO
};

class IPackageStockpile{
public:
    virtual void push(Package&& other) = 0;
    virtual bool empty() = 0;
    virtual std::size_t size() = 0;

    using const_iterator = std::list<Package>::const_iterator;

    virtual const_iterator begin() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator cend() const = 0;

    virtual ~IPackageStockpile() {}
};

class IPackageQueue : public IPackageStockpile {
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() = 0;

};

class PackageQueue : public IPackageQueue {
public:
    PackageQueue(PackageQueueType queue_type) : queue_type_(queue_type) {}
    void push(Package&& other) override;
    bool empty() override;
    std::size_t size() override;
    Package pop() override;
    PackageQueueType get_queue_type() override;

    const_iterator begin() const override {return queue_.begin();}
    const_iterator cbegin() const override {return queue_.cbegin();}
    const_iterator end() const override {return queue_.end();}
    const_iterator cend() const override {return queue_.cend();}

private:
    std::list<Package> queue_;
    PackageQueueType queue_type_;
};

#endif //IMPLEMENTATION_STORAGE_TYPES_HPP