#include "component.hpp"

#ifndef inductor_hpp
#define inductor_hpp

class inductor: public component 
{
private:
  double inductance; // Characteristic value
public:
  inductor(); // Default constructor
  inductor(double _inductance); // Parameterised constructor
  ~inductor();
  // Setters for member variables
  void set_impedance();
  void set_frequency(double _frequency);
  void set_value(double _inductance);
  // Getters for member variables
  double get_value();
  std::string get_symbol();
  auto clone() const -> std::shared_ptr<component>; // Create copy 'clone' of inductor

};

#endif /*inductor_hpp*/ 