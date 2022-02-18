#include "headers/create_component.hpp"
#include "headers/interface.hpp"


void create_component(std::vector<std::shared_ptr<component>>& components)
{
  // Called within interface
  // Allows user to create a resistor, capacitor or inductor manually or randomly.
  bool make_component{true};
  while(make_component) {
    int component_choice{};
    std::cout << "================== CREATE - COMPONENTS ================\n"
              << "Choose which type of component you would like to create by\n"
              << "typing the preceding number.\n"
              << "-------------------------------------------------------\n"
              << "1: resistor\n"
              << "2: capacitor\n"
              << "3: inductor\n"
              << "4: random component\n"
              << "-------------------------------------------------------\n"
              << "-> ";
    component_choice = valid_choice(4);

    switch(component_choice) {
      case 1: {
        std::cout << "================== CREATE - RESISTOR ==================\n"
                  << "Enter a value for the resistance in ohms\n"
                  << "-> ";
        double component_value{valid_component_value()};
        // Move new resistor into components library
        components.push_back(std::move(std::shared_ptr<resistor>(new resistor(component_value))));
        std::cout << "-------------------------------------------------------\n"
                  << "A new resistor with resistance = " << component_value << " Ohms\n"
                  << "has been stored in the component library.\n"
                  << "-------------------------------------------------------" << std::endl;
        // Each time, sort components by name to keep grouped by type
        sort_by_component(components); 
       break;
      }
      case 2: {
        std::cout << "================== CREATE - CAPACITOR =================\n"
                  << "Enter a value for the capacitance in micro farads\n"
                  << "-> ";
        double component_value{valid_component_value()};
        // Move new capacitor into components library
        components.push_back(std::move(std::shared_ptr<capacitor>(new capacitor(component_value))));
        std::cout << "-------------------------------------------------------\n"
                  << "A new capacitor with capacitance = " << component_value << " micro Farads\n"
                  << "has been stored in the component library.\n"
                  << "-------------------------------------------------------" << std::endl;
        sort_by_component(components);
        break;
      }
      case 3: {
        std::cout << "================== CREATE - INDUCTOR ==================\n"
                  << "Enter a value for the inductance in micro henrys\n"
                  << "-> ";
        double component_value{valid_component_value()};
        // Move new inductor into components library
        components.push_back(std::move(std::shared_ptr<inductor>(new inductor(component_value))));
        std::cout << "-------------------------------------------------------\n"
                  << "A new inductor with inductance = " << component_value << " micro Henrys\n"
                  << "has been stored in the component library.\n"
                  << "-------------------------------------------------------" << std::endl;
        sort_by_component(components);
        break;
      }
      case 4: {
        std::cin.clear(); // Flush in stream
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');   
        std::cout << "================== RANDOM - COMPONENT =================\n"
                  << "> A random value will be taken from a list of standard\n"
                  << "  values, corresponding to the randomly selected component.\n"
                  << "-------------------------------------------------------\n"
                  << "Press enter to continue: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        slow_print("\nRandomising...randomising...randomising...randomising..");
        std::cout << std::endl;

        
        int random_component_choice{rand() % 3}, // Random component selection
            random_value_choice{rand() % 30}; //  Random value selection

        switch (random_component_choice) {
          case 0: {
            double component_value{resistor_standard_values[random_value_choice]};
            // Add new randomised resistor to components library
            components.push_back(std::move(std::shared_ptr<resistor>(new resistor(component_value))));
            std::cout << "-------------------------------------------------------\n"
                      << "A new resistor with resistance = " << component_value << " ohms\n"
                      << "has been stored in the component library.\n"
                      << "-------------------------------------------------------" << std::endl;
            sort_by_component(components);
            break;
          }
          case 1: {
            double component_value{capacitor_standard_values[random_value_choice]};
            // Add new randomised capacitor to components library
            components.push_back(std::move(std::shared_ptr<capacitor>(new capacitor(component_value))));
            std::cout << "-------------------------------------------------------\n"
                      << "A new capacitor with capacitance = " << component_value << " micro farads\n"
                      << "has been created and stored in the component library.\n"
                      << "-------------------------------------------------------" << std::endl;
            sort_by_component(components);
            break;
          }
          case 2: {
            double component_value{inductor_standard_values[random_value_choice]};
            // Add new randomised inductor to components library
            components.push_back(std::move(std::shared_ptr<inductor>(new inductor(component_value))));
            std::cout << "-------------------------------------------------------\n"
                      << "A new inductor with inductance = " << component_value << " micro henrys\n"
                      << "has been created and stored in the component library.\n"
                      << "-------------------------------------------------------" << std::endl;
            sort_by_component(components);
            break;
          }
          default:
            std::cout << "Error" << std::endl;
        }
        break;
      }
      default:
        std::cout << "Input must be a 1, 2 or 3." << std::endl;
    }
    if(!(yes_no_query("Build another component?"))) {
      make_component = false; // Exit back to main menu 
    }
  }
}