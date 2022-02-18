#include "headers/inductor.hpp"

// Default constructor
inductor::inductor() = default;

// Paramaterised constructor
inductor::inductor(double _inductance) : inductance(_inductance)
{
  type = "inductor";
  units = "inductance (micro henrys)";
}

// Destructor
inductor::~inductor()
{
  nest_levels.clear();
  // std::cout << "Inductor destroyed" << std::endl; // For testing
}

// Set inductor impedance in complex form (0,jwL)
void inductor::set_impedance()
{
  // Inductance input in m H so multiply by 0.000001
  impedance = std::complex<double>(0, 2 * pi * 0.000001 * inductance * frequency);
}

// Set frequency once added to circuit
void inductor::set_frequency(double _frequency)
{
  frequency = _frequency;
}

// Set value if component is modified
void inductor::set_value(double _inductance)
{
  inductance = _inductance;
}

// Return inductance
double inductor::get_value()
{
  return inductance;
}

// Return symbol with value for circuit diagram
std::string inductor::get_symbol()
{
  // Stringstream used to format value
  std::ostringstream symbol_stream;
  symbol_stream << std::fixed <<  std::setprecision(1) << inductance;
  return "I(" + symbol_stream.str() + ")";
}

// Create a copy 'clone' of inductor for calculating circuit impedance
auto inductor::clone() const -> std::shared_ptr<component> 
{
  return std::shared_ptr<component>(new inductor{*this});
}

