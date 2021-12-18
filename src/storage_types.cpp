#include "storage_types.hpp"


void PackageQueue::push(Package&& other){
queue_.emplace_back(std::move(other));
}

bool PackageQueue::empty(){
    return queue_.empty();
}

PackageQueueType PackageQueue::get_queue_type(){
    return queue_type_;
}

std::size_t PackageQueue::size(){
    return queue_.size();
}

Package PackageQueue::pop(){
    const_iterator it;
    switch (queue_type_)
    {
    case PackageQueueType::FIFO:
        it = end();
        return *it;
        queue_.pop_back();
        break;
    default:
        it = begin();
        return *it;
        queue_.pop_front();
        break;
    }
}

