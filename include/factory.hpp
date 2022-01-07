#ifndef IMPLEMENTATION_FACTORY_HPP
#define IMPLEMENTATION_FACTORY_HPP
// Marcin Brzózka, nr 405499
// Stanisław Dudiak, nr 406903
// Adam Pękala, nr 405380
#include "nodes.hpp"
#include "types.hpp"
#include <list>

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

    list get_nodes_list() const { return nodes_list_; }
    const_iterator cbegin() const { return nodes_list_.cbegin(); }
    const_iterator cend() const { return nodes_list_.cend(); }
    iterator begin() { return nodes_list_.begin(); }
    const_iterator begin() const { return nodes_list_.cbegin(); }
    iterator end() { return nodes_list_.end(); }
    const_iterator end() const { return nodes_list_.cend(); }

private:
    list nodes_list_;
};


class Ramps : public NodeCollection<Ramp> {};
class Workers : public NodeCollection<Worker> {};
class Storehouses : public NodeCollection<Storehouse> {};


class Factory{
public:
    void add_ramp(Ramp&& other) { ramps_.add(std::move(other)); };
    void remove_ramp(ElementID id) { ramps_.remove_by_id(id); };
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id) { return ramps_.find_by_id(id); };
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const { return ramps_.find_by_id(id); };
    std::list<Ramp>::const_iterator ramp_cend() const { return ramps_.cend();}
    std::list<Ramp>::const_iterator ramp_cbegin() const { return ramps_.cbegin();}
    std::list<Ramp>::iterator ramp_end() { return ramps_.end();}
    std::list<Ramp>::iterator ramp_begin() { return ramps_.begin();}

    void add_worker(Worker&& other) { workers_.add(std::move(other)); };
    void remove_worker(ElementID id);
    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id) { return workers_.find_by_id(id); };
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const { return workers_.find_by_id(id); };
    std::list<Worker>::const_iterator worker_cbegin() const {return workers_.cbegin();}
    std::list<Worker>::const_iterator worker_cend() const {return workers_.cend();}
    std::list<Worker>::iterator worker_begin() {return workers_.begin();}
    std::list<Worker>::iterator worker_end() {return workers_.end();}

    void add_storehouse(Storehouse&& other) { storehouses_.add(std::move(other)); };
    void remove_storehouse(ElementID id) { storehouses_.remove_by_id(id); };
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id) { return storehouses_.find_by_id(id); };
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const { return storehouses_.find_by_id(id); };
    std::list<Storehouse>::const_iterator storehouse_cbegin() const { return storehouses_.cbegin();}
    std::list<Storehouse>::const_iterator storehouse_cend() const { return storehouses_.cend();}
    std::list<Storehouse>::iterator storehouse_begin() { return storehouses_.begin();}
    std::list<Storehouse>::iterator storehouse_end() { return storehouses_.end();}

    bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors) const;
    bool is_consistent() const;

    void do_deliveries(Time time);
    void do_package_passing();
    void do_work(Time time);

private:
    NodeCollection <Worker> workers_;
    NodeCollection <Storehouse> storehouses_;
    NodeCollection <Ramp> ramps_;
    template<class Node>
    void remove_receiver(NodeCollection<Node>& collection, ElementID id) {collection.remove_by_id(id);}
};

#endif //IMPLEMENTATION_FACTORY_HPP