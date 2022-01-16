// Marcin Brzózka, nr 405499
// Stanisław Dudiak, nr 406903
// Adam Pękala, nr 405380

#include "simulation.hpp"
#include <stdexcept>

void simulate(Factory& f, TimeOffset d){
    if(f.is_consistent()) {
        for (Time i = 0; i <= d; i++ ) {
            f.do_package_passing();
            f.do_work(i);
            f.do_deliveries(i);
        }
    }
    else{
            throw std::logic_error("Siec jest niespójna");
    }
}


