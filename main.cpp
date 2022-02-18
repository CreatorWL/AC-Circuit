/*
  PHYS30762 OOP in C++
  Final Project
  A.C. Circuit simulation

  William Lloyd
  Student ID: 10199593
  23/05/2021

  This program allows a user to create resistors, capacitors and inductors
  The user can then construct a circuit by connecting existing components
  in series, parallel or a combination of the two.
  Once the circuit is complete, the program computes prints information
  to the user, including a linear circuit diagram, the components involved,
  the impedance, the impedance magnitude and the impedance phase. 

  This program is object-oriented:
  There is a base component class with three derived classes for each component. 
  There is also a unique class for the circuit.
  Class members are implemented in the interface.

  Smart pointers are used for object ownership to automate memory management
  and avoid leaks.
*/

#include "headers/interface.hpp"
#include "headers/component.hpp"
#include "headers/circuit.hpp"

int main()
{
  interface();
  return 0;
}