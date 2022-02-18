#include "component.hpp"

#ifndef resistor_hpp
#define resistor_hpp

class resistor: public component
{ 
private:
  double resistance; // Characteristic value
public:
  resistor(); // Default constructor
  resistor(double _resistance); // Parameterised constructor
  ~resistor();
  // Setters for member variables
  void set_impedance();
  void set_frequency(double _frequency);
  void set_value(double _resistance);
  // Getters for member variables
  double get_value();
  std::string get_symbol();
  auto clone() const -> std::shared_ptr<component>; // Create copy 'clone' of resistor
};

#endif /* components_hpp */