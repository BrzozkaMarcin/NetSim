// Marcin Brzózka, nr 405499
// Stanisław Dudiak, nr 406903
// Adam Pękala, nr 405380

#include "storage_types.hpp"
#include "stdexcept"

Package PackageQueue::pop(){
    if (empty()) {
        throw std::logic_error("Empty queue");
    }
    switch (queue_type_) {
        case PackageQueueType::FIFO:{
            Package result = std::move(queue_.front());
            queue_.pop_front();
            return result;
        }
        case PackageQueueType::LIFO:{
            Package result = std::move(queue_.back());
            queue_.pop_back();
            return result;
        }
        default:
            throw std::logic_error("Wrong kind of queue");
    }
}