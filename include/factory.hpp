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


};


#endif //IMPLEMENTATION_FACTORY_HPP