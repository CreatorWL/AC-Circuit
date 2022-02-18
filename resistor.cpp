#include "headers/resistor.hpp"

// Default constructor
resistor::resistor() = default;

// Paramaterised constructor
resistor::resistor(double _resistance) : resistance(_resistance)
{
  type = "resistor";
  units = "resistance (ohms)";
  impedance = std::complex<double>(resistance, 0);
}
 // Destructor
resistor::~resistor()
{
  nest_levels.clear();
  // std::cout << "Resistor destroyed" << std::endl; // For testing
}

// Set resistance impedance in complex form (R,0)
void resistor::set_impedance()
{
  impedance = std::complex<double>(resistance, 0);
}

// Set frequency once added to circuit
void resistor::set_frequency(double _frequency)
{
  frequency = _frequency;
}

// Set value if component is modified
void resistor::set_value(double _resistance)
{
  resistance = _resistance;
}

// Return resistance
double resistor::get_value()
{
  return resistance;
}
// Return symbol with value for circuit diagram
std::string resistor::get_symbol()
{
  // Stringstream used to format value
  std::ostringstream symbol_stream;
  symbol_stream << std::fixed << std::setprecision(1) << resistance;
  return "R(" + symbol_stream.str() + ")";
}
// Create a copy 'clone' of resistor for calculating circuit impedance
auto resistor::clone() const -> std::shared_ptr<component> 
{
  return std::shared_ptr<component>(new resistor{*this});
}
