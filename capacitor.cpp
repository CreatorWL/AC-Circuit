#include "headers/capacitor.hpp"

// Default constructor
capacitor::capacitor() = default;

// Paramaterised constructor
capacitor::capacitor(double _capacitance) : capacitance(_capacitance)
{
  type = "capacitor";
  units = "capacitance (micro farads)";
}

// Destructor
capacitor::~capacitor()
{
  nest_levels.clear();
  // std::cout << "Capacitor destroyed" << std::endl; // For testing

}

// Set capacitor impedance in complex form (0, -j/wC)
void capacitor::set_impedance()
{
  // Capacitance input in m F so multiply by 0.000001
  impedance = std::complex<double>(0, -1 / (2 * pi * 0.000001 * capacitance * frequency));
}

// Set frequency once added to circuit
void capacitor::set_frequency(double _frequency)
{
  frequency = _frequency;
}

// Set value if component is modified
void capacitor::set_value(double _capacitance)
{
  capacitance = _capacitance; 
}

// Return capacitance
double capacitor::get_value()
{
  return capacitance;
}

// Return symbol with value for circuit diagram
std::string capacitor::get_symbol()
{
  // Stringstream used to format value
  std::ostringstream symbol_stream; 
  symbol_stream << std::fixed << std::setprecision(1) << capacitance;
  return "C(" + symbol_stream.str() + ")";
}

// Create a copy 'clone' of capacitor for calculating circuit impedance
auto capacitor::clone() const -> std::shared_ptr<component> 
{
  return std::shared_ptr<component>(new capacitor{*this});
}