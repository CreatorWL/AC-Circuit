#include <algorithm>
#include <chrono>
#include <cmath>
#include <complex>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <thread>
#include <vector>

#include "circuit.hpp"
#include "component.hpp"
#include "create_circuit.hpp"
#include "create_component.hpp"
#include "standard_values.hpp"
#include "validation.hpp"

#ifndef interface_hpp
#define interface_hpp

void interface();
void list_components(const std::vector<std::shared_ptr<component>>& components); // Used in multiple functions to view components
void modify_components(std::vector<std::shared_ptr<component>>& components); // Modify existing components by value
void list_standard_values(std::string type); // List arrays of standard values for each component
void sort_by_component(std::vector<std::shared_ptr<component>>& components); // Sort the components vector
bool compare_by_name(const std::shared_ptr<component>& a, const std::shared_ptr<component>& b); // Called in sort_by_component
void slow_print(std::string message); // Slow print a string to console

#endif /*interface_hpp*/