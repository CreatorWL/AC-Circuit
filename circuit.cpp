#include "headers/circuit.hpp"

// Circuit member functions

// Default constructor
circuit::circuit() = default;

// Parameterised constructor
circuit::circuit(double _frequency) : frequency(_frequency) {}

// Set driving A.C. frequency
void circuit::set_frequency(double _frequency)
{
  frequency = _frequency;
}

// Return frequency of circuit
double circuit::get_frequency() const
{
  return frequency;
}

// Compare two nest levels and return true if parallel
bool circuit::quasi_equal_nests(const std::deque<int>& nest_1, const std::deque<int>& nest_2)
{
  // Parallel nests have same size and values apart from second last value
  // Second last value corresponds to the branch number
  return (nest_1.size() == nest_2.size()
          && std::equal(nest_1.begin(), nest_1.end() - 2, nest_2.begin())
          && (nest_1[nest_1.size() - 2] != nest_2[nest_2.size() - 2]));
}

void circuit::set_impedance()
{
  /* 
    This function returns the impedance of a circuit.
    For one component, function returns component impedance
    For two component, the function determines whether parallel or series, 
    then calculates and returns impedance.
    For three or more components, function replaces groups of components
    by one component with updated impedance (depending on series or parallel)
    until only one component is left. Function returns final component impedance.
  */

  std::complex<double> one_complex{1,0}; // Complex '1' to compute impedance reciprocals
  std::complex<double> total_impedance; // Define impedance for outer scope 

  if(inner_components.size() == 1) {
    total_impedance = inner_components[0]->get_impedance(); // Assign temp impedance to component impedance
    
  } else if(inner_components.size() == 2) { 
    if(inner_components[0]->get_nest_levels()[0] == 0) { // Check for two series components
      // Assign temp impedance to sum of components
      total_impedance = inner_components[0]->get_impedance() + inner_components[1]->get_impedance();
    } else {
      // Assign temp impedance to reciprocal of reciprocal sums of components
      total_impedance = one_complex / ((one_complex / inner_components[0]->get_impedance()) +
                       (one_complex / inner_components[1]->get_impedance())); 
    }
  } else { 
    // Create map to hold each components impedance and nest levels, and the size of the nest level (for sorting)
    std::multimap<int, std::multimap<std::deque<int>, std::complex<double>>, std::greater <int>> temp_impedance_map;

    // Add impedance and nest levels as pairs to map
    for(auto component_it = inner_components.begin(); component_it != inner_components.end(); ++component_it) {
      std::multimap<std::deque<int>, std::complex<double>> temp_multimap;
      temp_multimap.insert(std::pair<std::deque<int>, std::complex<double>>((*component_it)->get_nest_levels(), (*component_it)->get_impedance()));
      temp_impedance_map.insert(std::pair<int, std::multimap<std::deque<int>, std::complex<double>>>((*component_it)->get_nest_levels().size(), temp_multimap));
    }
    // Loop until only one multimap remains in temp_impedance_map
    while(temp_impedance_map.size() > 1) {

      // Iterate through temp_impedance_map and match nest levels based on series or parallel
      for(auto iterator_1 = temp_impedance_map.begin(); iterator_1 != temp_impedance_map.end();) {

        bool iterator_1_erased {false}; // If false, iterator must be incremented
        bool parallel{true}; // If two impedances added in series, this is false. 

        // Temporary parallel and series impedances for storing the new impedance inside of second iterator
        std::unique_ptr<std::complex<double>> reciprocal_impedance_pointer(new std::complex<double>(0,0));
        std::unique_ptr<std::complex<double>> series_impedance_pointer(new std::complex<double>(0,0));

        // Add iterator_1 multimap to pointer in case it matches to another parallel multimap
        *reciprocal_impedance_pointer += (one_complex / (*iterator_1).second.begin()->second);

        // Compare each element without duplication
        for(auto iterator_2 = std::next(iterator_1); iterator_2 != temp_impedance_map.end();) {

          // If nest levels are the same, these must be added in series.
          if((*iterator_1).second.begin()->first == (*iterator_2).second.begin()->first) {

            // Create new impedance by adding two component impedance together.
            *series_impedance_pointer = (*iterator_1).second.begin()->second + (*iterator_2).second.begin()->second;
            // Clear current iterator_2 and increment iterator_2 to next multiap
            iterator_2 = temp_impedance_map.erase(iterator_2);
            iterator_1_erased = true;
            parallel = false;
            break; // Exit iterator_2 and compare new iterator_1

          } else if(quasi_equal_nests((*iterator_1).second.begin()->first, (*iterator_2).second.begin()->first)) {

            // Add reciprocal impedance to the temporary parallel impedance
            *reciprocal_impedance_pointer += (one_complex / (*iterator_2).second.begin()->second); 
            // Clear current iterator_2 and increment iterator_2 to next multiap
            iterator_2 = temp_impedance_map.erase(iterator_2);
            // If iterator_1 has been compared to all other elements, progress
            if(iterator_2 == temp_impedance_map.end()) {
              iterator_1_erased = true;
            }
          } else {
            ++iterator_2;
            iterator_1_erased = true;
          }
        }
        if(!iterator_1_erased) {
          ++iterator_1;
        } else {
          if(parallel) {
            // Create new temporary map, impedance and nest
            std::multimap<std::deque<int>, std::complex<double>> temp_parallel_multimap;

            try {
              std::complex<double> new_parallel_impedance{one_complex / *reciprocal_impedance_pointer};
            }
            catch(...) {
              std::cout << "Error: cannot divide by zero." << std::endl;
              exit(-1);
            }
            std::complex<double> new_parallel_impedance{one_complex / *reciprocal_impedance_pointer};
            std::deque<int> new_parallel_nest;
            if((*iterator_1).second.begin()->first.size() > 3) {
              // If the nest is second order or larger (size > 3),
              // remove second last element 
              new_parallel_nest = (*iterator_1).second.begin()->first;
              new_parallel_nest.erase(new_parallel_nest.end() - 2);
            } else {
              // If the nest is first order (size = 3), new nest = 0 
              // (a series component on the main wire)
              new_parallel_nest = {0};
            }
            // Add updated multimap to temp_impedance_map and increment iterator_1
            int temp_int{(*iterator_1).first - 1};
            temp_parallel_multimap.insert(std::pair<std::deque<int>, std::complex<double>>(new_parallel_nest, new_parallel_impedance));
            iterator_1 = temp_impedance_map.erase(iterator_1);
            temp_impedance_map.insert(std::pair<int, std::multimap<std::deque<int>, std::complex<double>>>(temp_int, temp_parallel_multimap)); 
          } else {
            // Add updated multimap to temp_impedance_map and increment iterator_1
            int temp_nest_size{(*iterator_1).first};
            std::multimap<std::deque<int>, std::complex<double>> temp_multimap;
            temp_multimap.insert(std::pair<std::deque<int>, std::complex<double>>((*iterator_1).second.begin()->first, *series_impedance_pointer));
            iterator_1 = temp_impedance_map.erase(iterator_1);
            temp_impedance_map.insert(std::pair<int, std::multimap<std::deque<int>, std::complex<double>>>(temp_nest_size, temp_multimap));
          }
        }
      }
    }
    // Assign temp impedance to remaining component
    total_impedance = temp_impedance_map.begin()->second.begin()->second; 
    temp_impedance_map.clear();
  }
  // Set impedance of circuit
  impedance = total_impedance;
}

// Return circuit impedance in form (R,X)
std::complex<double> circuit::get_impedance() const
{
  return impedance;
}

// Return impedance magnitude
double circuit::get_impedance_magnitude() const
{
  return std::abs(impedance);
}

// Return impedance phase
double circuit::get_impedance_phase() const
{
  return std::arg(impedance);
}

// Overload outstream operator to print circuit
std::ostream& operator<<(std::ostream& out_stream, const circuit& circuit)
{
  // Find component with the largest impedance for the output information
  auto largest_impdance_component{std::max_element(circuit.inner_components.begin(), circuit.inner_components.end(),
                                                  [](const std::shared_ptr<component> lhs,const std::shared_ptr<component> rhs)
                                                  {
                                                    return lhs->get_impedance_magnitude() < rhs->get_impedance_magnitude();
                                                  })};
  // Format outputs 
  std::cout << std::fixed;
  std::cout << std::setprecision(2);

  // Print all of the circuit information to the console
  std::cout << "\n\n========== CIRCUIT - INFORMATION ==========\n\n"
            << "This circuit contains " << circuit.inner_components.size() << " components:\n"
            << "-------------------------------------------" << std::endl;
  int list_number{1};
  for(auto& component: circuit.inner_components) {
    std::cout << list_number << ":\n";
    component->component_information();
    std::cout << "===========================================\n" << std::endl;
    ++list_number;
  }
  std::cout << "===========================================\n"
            << "\nCircuit diagram: \n\n"
            << circuit.circuit_schematic << "\n\n"
            << "[Resistance in Ohms - Capacitance in micro Farads - Inductance in micro Henrys]\n"
            << "===========================================\n"
            << "AC frequency: " << circuit.get_frequency() << " Hz\n"
            << "-------------------------------------------\n"
            << "Circuit impedance (R + Xi):  (" << circuit.get_impedance().real() 
                                                << (circuit.get_impedance().imag() >= 0 ? " + " : " - " ) 
                                                << (circuit.get_impedance().imag() >= 0 ? circuit.get_impedance().imag() : (-1 * circuit.get_impedance().imag())) 
                                                << "i) Ohms\n"
            << "-------------------------------------------\n"
            << "Impedance magnitude: " << circuit.get_impedance_magnitude() << " Ohms\n"
            << "-------------------------------------------\n"
            << "Impedance phase: " << circuit.get_impedance_phase() * (180 / (2 * pi)) << " degrees\n"
            << "-------------------------------------------\n"
            << "Component with the largest impedance: \n"
            << "Type: " << (*largest_impdance_component)->get_type() << "\n"
            << "Value " << (*largest_impdance_component)->get_units() << ": " << (*largest_impdance_component)->get_value() << "\n"
            << "Impedance: " << (*largest_impdance_component)->get_impedance() << " Ohms\n" 
            << "-------------------------------------------" << std::endl;

  return out_stream;
}


// Print overloaded outstream operator
void circuit::print_circuit_information() const
{ 
  std::cout << (*this);
}

// Add symbol to circuit diagram
void circuit::set_circuit_schematic(std::string symbol)
{
  circuit_schematic += symbol;
}

void circuit::add_component(const std::shared_ptr<component>& component, int nest_level, double frequency)
{
  // Add a clone of the component to the circuit components library
  // This ensures that components aren't edited inside of the circuit
  inner_components.push_back(component);
  inner_components.back()->add_to_nest(nest_level);
  inner_components.back()->set_frequency(frequency);
  inner_components.back()->set_impedance();
}

// Return component container
std::vector<std::shared_ptr<component>> circuit::get_circuit_components()
{
  return inner_components;
}

// Copy constructor
circuit::circuit(circuit& circuit)
{
  frequency = circuit.frequency;
  impedance = circuit.impedance;
  if(circuit.inner_components.size() > 0) {
    for(int i{}; i < inner_components.size(); ++i) {
      inner_components[i] = circuit.inner_components[i];
    }
  }
} 