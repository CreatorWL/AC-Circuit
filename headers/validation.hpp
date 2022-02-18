#include <cmath>
#include <iostream>
#include <limits>

#ifndef validation_hpp
#define validation_hpp

// Functions for validating input values.
double valid_component_value();
int valid_integer(int lower_limit);
int valid_choice(int upper_value);
bool yes_no_query(std::string statement);

#endif /*validation_hpp*/