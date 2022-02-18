#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <thread>
#include <vector>

#include "component.hpp"
#include "validation.hpp"

#ifndef create_component_hpp
#define create_component_hpp

void create_component(std::vector<std::shared_ptr<component>>& components);

#endif /*create_component_hpp*/