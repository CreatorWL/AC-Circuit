#include <complex>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <math.h>
#include <memory>
#include <sstream>
#include <vector>

#ifndef components_hpp
#define components_hpp

const double pi{3.141592654};

class component
{
protected:
  double frequency{}; 
  std::string units{"units"};
  std::string type{"component"};
  std::string symbol{"[~Component~]"}; // For visualsing circuit
  std::deque<int> nest_levels; 
  std::complex<double> impedance{std::complex<double>(0,0)}; // Impedance stored in complex form
public:
  component(); // Default constructor
  virtual ~component(){}; 
  // Virtual setters
  virtual void set_impedance() = 0;
  virtual void set_value(double) = 0;
  virtual void set_frequency(double) = 0;
  // Virtual getters
  virtual double get_value() = 0;
  virtual std::string get_symbol() = 0;
  virtual auto clone() const -> std::shared_ptr<component> = 0 ; // Create clone of component
  // Getters for members and impedance values
  std::string get_type() const;
  double get_frequency() const;
  std::string get_units() const;
  double get_impedance_phase() const;
  double get_impedance_magnitude() const;
  std::complex<double> get_impedance() const;
  // Additional functions
  void add_to_nest(int);
  std::deque<int> get_nest_levels() const;
  int access_nest_level(int _index) const;
  void component_information();
};

#endif /* components_hpp */