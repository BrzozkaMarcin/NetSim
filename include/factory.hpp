#ifndef IMPLEMENTATION_FACTORY_HPP
#define IMPLEMENTATION_FACTORY_HPP
// Marcin Brzózka, nr 405499
// Stanisław Dudiak, nr 406903
// Adam Pękala, nr 405380
#include "nodes.hpp"

enum class NodeColor {
    UNVISITED, VISITED, VERIFIED
};

template <class Node>
class NodeCollection{
public:
    using list = typename std::list<Node>;
    using iterator = typename list::iterator;
    using const_iterator = typename list::const_iterator;

    void add(Node&& node) {
        nodes_list_.push_back(std::move(node));
    }

    iterator find_by_id(ElementID id) {
        for (auto it = nodes_list_.begin(); it != nodes_list_.end(); it++) {
            if (it->get_id() == id) {
                return it;
            }
        }
        return nodes_list_.end();
    }

    const_iterator find_by_id(ElementID id) const {
        for (auto it = nodes_list_.cbegin(); it != nodes_list_.cend(); it++) {
            if (it->get_id() == id) {
                return it;
            }
        }
        return nodes_list_.cend();
    }

    void remove_by_id(ElementID id) {
        auto it = find_by_id(id);
        if (it != nodes_list_.end()) {
            nodes_list_.erase(it);
        }
    }



private:
    list nodes_list_;
};


#endif //IMPLEMENTATION_FACTORY_HPP