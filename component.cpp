#include "headers/component.hpp"

//// Component member functions

// Default constructor
component::component() = default;

// Return the type of component
std::string component::get_type() const
{
  return type;
}

// Return the characteristic units 
std::string component::get_units() const
{
  return units;
}

// Return frequency of component
double component::get_frequency() const
{
  return frequency;
}

// Return impedance in form (R,X)
std::complex<double> component::get_impedance() const
{
  return impedance;
}

// Return the magnitude of the impedance
double component::get_impedance_magnitude() const
{
  return abs(impedance);
}

// Return phase of complex impedance
double component::get_impedance_phase() const
{
  return arg(impedance);
}

// Add a nest level to the front of the container
void component::add_to_nest(int _nest_level)
{
  nest_levels.push_front(_nest_level);
}

// Access an element in the nest levels
int component::access_nest_level(int index) const
{
  return nest_levels[index];
}

// Return entire nest level container
std::deque<int> component::get_nest_levels() const
{
  return nest_levels;
}

// Print out type, units, value and impedance of component
void component::component_information()
{
  std::cout << "Type: " << this->get_type() << "\n"
            << this->get_units() << ": " << this->get_value() << "\n";
  if(frequency != 0) {
    std::cout << "Impedance: " << impedance << "\n";
  }
}

