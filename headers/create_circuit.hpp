#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <thread>
#include <vector>

#include "circuit.hpp"
#include "component.hpp"
#include "validation.hpp"

#ifndef create_circuit_hpp
#define create_circuit_hpp

// Two functions called within the interface for constructing a circuit
void create_circuit(std::vector<std::shared_ptr<component>>& components, bool first_circuit);
void add_to_node(std::unique_ptr<circuit>& circuit, 
                 const std::vector<std::shared_ptr<component>>& components, 
                 int nest_level, int parallel_level, int branch, int max_branch);


#endif /*create_circuit_hpp*/