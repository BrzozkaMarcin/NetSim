#ifndef IMPLEMENTATION_SIMULATION_HPP
#define IMPLEMENTATION_SIMULATION_HPP
// Marcin Brzózka, nr 405499
// Stanisław Dudiak, nr 406903
// Adam Pękala, nr 405380

#include "factory.hpp"
#include "reports.hpp"
#include <functional>
#include "types.hpp"

void simulate(Factory& f, TimeOffset d, std::function<void (Factory&, Time)> rf);


#endif //IMPLEMENTATION_SIMULATION_HPP