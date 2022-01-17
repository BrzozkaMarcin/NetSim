// Marcin Brzózka, nr 405499
// Stanisław Dudiak, nr 406903
// Adam Pękala, nr 405380

#include "simulation.hpp"
#include <stdexcept>

void simulate(Factory& f, TimeOffset d, std::function<void (Factory&, Time)> rf){
    if(f.is_consistent()) {
        for (Time i = 1; i <= d; i++ ) {
            f.do_package_passing();
            f.do_work(i);
            f.do_deliveries(i);
            rf(f,i);
        }
    }
    else{
            throw std::logic_error("Siec jest niespójna");
    }
}


