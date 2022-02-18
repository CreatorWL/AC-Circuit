#include <algorithm>
#include <iostream>
#include <cmath>
#include <complex>
#include <cstring>
#include <limits>
#include <map>
#include <math.h>
#include <memory>
#include <vector>

// Include base class component and derived components
#include "component.hpp"
#include "capacitor.hpp"
#include "inductor.hpp"
#include "resistor.hpp"

#ifndef circuit_hpp
#define circuit_hpp

class circuit
{
  // Friend for overloading outstream to print a circuit
  friend std::ostream& operator<<(std::ostream& out_stream, const circuit& _circuit);
private:
  double frequency{100};
  std::complex<double> impedance{0,0};
  std::vector<std::shared_ptr<component>> inner_components{}; // Container for circuit components
  std::string circuit_schematic{}; // Visualisation of circuit
public:
  circuit(); // Default constructor
  circuit(double _frequency); // Parameterised constructor
  circuit(circuit& circuit); // Copy constructor
  ~circuit(){/*std::cout << "Circuit destructor called." << std::endl;*/}; // Destructor message for testing.
  // Setters for member variables
  void set_impedance();
  void set_frequency(double _frequency);
  void set_circuit_schematic(std::string diagram);
  // Getters for frequency and impedance values
  double get_frequency() const;
  double get_impedance_phase() const;
  double get_impedance_magnitude() const;
  std::vector<std::shared_ptr<component>> get_circuit_components();
  // Additional functions
  void print_circuit_information() const;
  std::complex<double> get_impedance() const;
  bool quasi_equal_nests(const std::deque<int>& nest_1, const std::deque<int>& nest_2);
  void add_component(const std::shared_ptr<component>& component, int nest_level, double frequency); 
};

#endif /* circuit_hpp */