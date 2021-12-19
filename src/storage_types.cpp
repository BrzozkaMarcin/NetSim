#include "storage_types.hpp"


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

