#ifndef IMPLEMENTATION_TYPES_HPP
#define IMPLEMENTATION_TYPES_HPP
//#include <iostream>
#include <functional>
// Marcin Brzózka, nr 405499
// Stanisław Dudiak, nr 406903
// Adam Pękala, nr 405380

//using ElementID = std::size_t;
using ElementID = int;

using ProbabilityGenerator = std::function<double(void)>;
using Time = int;
using TimeOffset = int;

#endif //IMPLEMENTATION_TYPES_HPP