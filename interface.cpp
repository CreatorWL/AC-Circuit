#include "headers/interface.hpp"

void interface()
{
  bool first_circuit{true}; // Print circuit build instructions for first circuit
  std::vector<std::shared_ptr<component>> components; // Create vector for storing new components

  std::cout << "\n"
            << "=============================================================\n"
            << "========================== Welcome ==========================\n"
            << "=============================================================\n"
            << "> In this program, you can build electrical components and \n"
            << "  construct AC circuits with them. \n\n"
            << "> There are three available components to choose from:\n"
            << "  resistors, capacitors and inductors.\n\n"
            << "> Circuits can be constructed in series, parallel, or both.\n\n"
            << "> Specific details on how to construct the circuit will be\n"
            << "  provided when a new circuit is initiated.\n\n"
            << "> You are also given the option to create randomly generated\n"
            << "  components.\n\n"
            << "> The impedance is calculated for every constructed component\n"
            << " and circuit (for a given frequency). This will be stored\n"
            << " and listed with other properties of each component or circuit.\n\n"
            << "> Note: make sure you have full screened your terminal!\n"
            << "-------------------------------------------------------------\n"
            << "Press enter to continue: ";
  std::cin.ignore();
  std::cout << "-------------------------------------------------------------" << std::endl;

  bool running{true};
  // Start program
  while (running) {
    int option_choice;
    std::cout << "============== Menu ==============\n"
              << "Choose an item from the list by\n"
              << "typing the preceding number.\n"
              << "==================================\n"
              << "1: Create component\n"
              << "2: List components\n"
              << "3: Modify components\n"
              << "4: Create circuit\n"
              << "5: Exit program\n"
              << "----------------------------------\n"
              << "-> ";
    option_choice = valid_choice(5);
    switch (option_choice) {
      case 1: {
        create_component(components);
        break;
      }
      case 2: {
        list_components(components);
        break;
      }
      case 3: {
        modify_components(components);
        break;
      }
      case 4: {
        create_circuit(components, first_circuit);
        break;
      }
      case 5: {
        std::cout << "==================================" << std::endl;
        if(yes_no_query("Are you sure you want to quit?")) {
          running = false;
          std::cout << "Goodbye" << std::endl;
        }
        components.clear(); // Empty components library
        break;
      }
      default: std::cout << "This number is not on the list!" << std::endl;
    }
  }
}

void list_components(const std::vector<std::shared_ptr<component>>& components)
{
  // Print information for existing components
  std::cout << "================ COMPONENTS - LIBRARY ================" << std::endl;
  int list_number{};
  for(auto& comps: components) {
    std::cout << list_number + 1 << ":\n";
    comps->component_information();
    std::cout << "---------------------------------" << std::endl;
    ++list_number;
  }
}

void modify_components(std::vector<std::shared_ptr<component>>& components)
{
  // Allow user to define a new value to an existing component
  std::cout << "================= MODIFY - COMPONENTS =================\n"
            << "Choose a component from the list to modify:" << std::endl;

  list_components(components);
  std::cout << "-> ";
  int component_choice{valid_choice(components.size())};

  std::cout << "-------------------------------------------------------\n"
            << "Enter a new value for this component:\n"
            << "-> ";
  double new_value{valid_component_value()};
  components[component_choice - 1]->set_value(new_value); // Set new value
  // Print process to console for user
  std::cout << "-------------------------------------------------------\n"
            << "The " << components[component_choice - 1]->get_units() 
            << " of " << components[component_choice - 1]->get_type()
            << "\nhas been updated to: " << components[component_choice - 1]->get_value()
            << std::endl;
}

void list_standard_values(std::string type)
{
  // Print out the standard values with enumeration
  if(type == "resistor") {
    for(int i{}; i < 30; ++i) {
      std::cout << (i + 1) << ": " << resistor_standard_values[i] << std::endl;
    } 
  } else if(type == "capacitor") {
    for(int i{}; i < 30; ++i) {
      std::cout << (i + 1) << ": " << capacitor_standard_values[i] << std::endl;
    }
  } else if(type == "inductor") {
    for(int i{}; i < 30; ++i) {
      std::cout << (i + 1) << ": " << capacitor_standard_values[i] << std::endl;
    }
  }
}

void sort_by_component(std::vector<std::shared_ptr<component>>& components)
{
  // Sort by the name of the component to group component types together
  std::sort(components.begin(), components.end(), compare_by_name);
}

bool compare_by_name(const std::shared_ptr<component>& a, const std::shared_ptr<component>& b)
{
  // Truth statement for sort_by_components
  // Compare by type 
  return a->get_type() < b->get_type();
}

void slow_print(std::string message)
{
  // Output with delays between each character in str to add dyanmism to code
  for(char character: message) {
    // Pause for specified time
    std::this_thread::sleep_for(std::chrono::milliseconds(15));
    // Print character
    std::cout << character << std::flush;
  }
}