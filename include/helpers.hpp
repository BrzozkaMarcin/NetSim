#ifndef IMPLEMENTATION_HELPERS_HPP
#define IMPLEMENTATION_HELPERS_HPP
// Marcin Brzózka, nr 405499
// Stanisław Dudiak, nr 406903
// Adam Pękala, nr 405380
#include <functional>
#include <random>

#include "types.hpp"

extern std::random_device rd;
extern std::mt19937 rng;

extern double default_probability_generator();

extern ProbabilityGenerator probability_generator;



#endif //IMPLEMENTATION_HELPERS_HPP