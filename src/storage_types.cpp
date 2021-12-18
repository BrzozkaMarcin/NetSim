#include "storage_types.hpp"


void PackageQueue::push(Package&& other){
queue_.emplace_back(other);
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
    switch (queue_type_)
    {
    case PackageQueueType::FIFO:{
        Package result = queue_.front();
        queue_.pop_back();
        return result;
        break;
    }
    default:
        Package result = queue_.back();
        queue_.pop_front();
        return result;
        break;
    }
}

