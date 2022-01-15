#ifndef IMPLEMENTATION_REPORTS_HPP
#define IMPLEMENTATION_REPORTS_HPP
// Marcin Brzózka, nr 405499
// Stanisław Dudiak, nr 406903
// Adam Pękala, nr 405380

#include "factory.hpp"


void generate_structure_report(const Factory& f, std::ostream& os);

void generate_simulation_turn_report(const Factory& f,std::ostream& os,Time t);


#endif //IMPLEMENTATION_REPORTS_HPP