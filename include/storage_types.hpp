#ifndef IMPLEMENTATION_STORAGE_TYPES_HPP
#define IMPLEMENTATION_STORAGE_TYPES_HPP

#include <list>
#include "package.hpp"
class IPackageStockPile{
    public:

    using const_iterator = std::list<Package>::const_iterator;
    
    virtual void push(const Package&& package);                            
    virtual bool empty() const;
    virtual std::size_t size() const;
    virtual ~IPackageStockPile();



    
};

class IPackageQueue{

};

class PackageQueue{

};

#endif //IMPLEMENTATION_STORAGE_TYPES_HPP