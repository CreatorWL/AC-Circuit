#include "component.hpp" // Include base class

#ifndef capacitor_hpp
#define capacitor_hpp

class capacitor: public component
{
private:
  double capacitance; // Characteristic value
public: 
  capacitor(); // Default constructor 
  capacitor(double _capacitance); // Parameterised constructor
  ~capacitor();
  // Setters for member variables
  void set_impedance();
  void set_value(double _capacitance);
  void set_frequency(double _frequency);
  // Getters for member variables
  double get_value(); 
  std::string get_symbol();
  auto clone() const -> std::shared_ptr<component> override;   // Create copy 'clone' of capacitor
};

#endif /*capacitor_hpp*/