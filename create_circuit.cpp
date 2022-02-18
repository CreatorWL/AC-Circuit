#include "headers/create_circuit.hpp"
#include "headers/interface.hpp"



void create_circuit(std::vector<std::shared_ptr<component>>& components, bool first_circuit)
{
  if(components.size() == 0) {
    std::cout << "You need to create at least one component first!" <<std::endl;
  } else {
    std::cout << "====================== CREATE - CIRCUIT ======================\n";
    if(first_circuit) {
      std::cout << "------------------------ INSTRUCTIONS -----------------------\n"
                << "> Circuits are constructed so that components are separated\n"
                << "  by nodes.\n\n"
                << "> At each node you are asked if you want to add a\n"
                << "  component in series, add multiple components in parallel,\n"
                << "  or complete the circuit.\n\n"
                << "> If components are added in parallel, e.g. two, then\n"
                << "  two branches are created that lead to two new nodes.\n\n"
                << "> At each of these nodes you can again add components in\n"
                << "  series or parallel, or you can CLOSE the branch.\n"
                << "  This allows for parallel or series circuits to be nested.\n\n"
                << "> You cannot complete the circuit within a branch.\n"
                << "  I.e. all branches need to be closed up to the first parallel\n"
                << "  branch to complete the circuit.\n"
                << "> When you have complete the circuit, the impedance will be\n"
                << "  calculated, along with other properties.\n"
                << "> This is an AC circuit, so you will need to input the driving\n"
                << "  frequency before any properties are calculated.\n"
                << "----------------------- VISUALISATION -----------------------\n"
                << "> A schematic will be printed when the circuit is complete.\n"
                << "> The AC source connections are represented by:\n"
                << "  > o-- and --o\n\n"
                << "> Components with value 'v' are represented by:\n"
                << "  > [C(v)]  for a capacitor\n"
                << "  > [I(v)]  for an inductor\n"
                << "  > [R(v)]  for a resistor\n\n"
                << "> Components connected in series are represented by:\n"
                << "  > o--[~C(v)~]--[~C(v)~]--o for two capacitors.\n\n"
                << "> Components connected in parallel are represented by:\n"
                << "  > o--[~C(v) || C(v)~]--o for two capacitors.\n\n"
                << "> A nested parallel circuit is represented by:\n"
                << "  > o--[~[~R(v) || R(v)~] || I(v)~]--o\n"
                << "  > o--[~[~R(v) || R(v)~] || I(v)~]--o\n"
                << "    for two parallel resistors, connected in\n"
                << "    parallel to an inductor." << std::endl;
    }
    std::cout << "----------------------- LETS  BEGIN! -----------------------" << std::endl;
    // Create shared pointer with ownership of new circuit
    std::unique_ptr<circuit> user_circuit(new circuit());

    // Add first terminal to the circuit diagram
    user_circuit->set_circuit_schematic("o--");
  
    // Set the A.C. frequency
    double frequency_input{};
    std::cout << "Enter the driving frequency of your circuit (Hz)\n"
              << "-> ";
    frequency_input = valid_component_value();
    user_circuit->set_frequency(frequency_input);

    std::cout << "-------------------------------------------------------------\n"
              << "The frequency has been set to " << frequency_input << " Hz\n"
              <<"=============================================================" << std::endl;

    int parallel_level{1}; // The parallel circuit index added to the main wire
    bool incomplete_circuit{true}; // While loop condition
    bool not_first_connection{false};
    while(incomplete_circuit) {
      std::cout << "Choose connection for this node by typing preceding number.\n"
                << "-------------------------------------------------------------\n"
                << "1: Add component in series\n"
                << "2: Add component in parallel" << std::endl;
      if(not_first_connection == true) {
        // User must add a component before closing the branch
        std::cout << "3: Complete circuit" << std::endl; 
      }
      std::cout << "-------------------------------------------------------------\n"
                << "-> ";
      int connection_choice;
      if(not_first_connection == true) {
        connection_choice = valid_choice(3); 
      } else {
        connection_choice = valid_choice(2); 
      }
      switch (connection_choice) {
        case 1: {
          std::cout << "--------------------------------------------------------------\n"
                    << "Choose a component from the components library to add in series\n"
                    << "by typing the preceding number.\n"
                    << "--------------------------------------------------------------" << std::endl;
          list_components(components);
          std::cout << "-> ";
          int component_choice{valid_choice(components.size())};

          // Create a cloned copy of the chosen component to avoid editing original
          std::shared_ptr<component> component_copy = components[component_choice - 1]->clone();
          // Add CLONE to circuit components and symbol to schematic
          user_circuit->add_component(component_copy, 0, user_circuit->get_frequency());
          user_circuit->set_circuit_schematic(("-[~" + components[component_choice - 1]->get_symbol() + "~]-"));
          not_first_connection = true;
          break;
        }
        case 2: {
          int nest_level{1}; // Keep track of nest level 
          std::cout << "How many components do you want to add in parallel?\n"
                    << "-> ";
          int branches{valid_integer(2)};
          std::cout << "--------------------------------------------------------------\n"
                    << "You have chosen to add " << branches << " components in parallel.\n"
                    << "==============================================================\n" << std::endl;
          user_circuit->set_circuit_schematic("-[~");
          for(int i{}; i != branches; ++i) {
            std::cout << "==============================================================\n"
                      << "You are in BRANCH " << (i + 1) << " at NEST LEVEL " << nest_level << std::endl;

            // Repeat choices for new components inside parallel branches
            add_to_node(user_circuit, components, nest_level, parallel_level, i+1, branches); // Recursion

            // Push nest level and parallel number into component nest container
            user_circuit->get_circuit_components().back()->add_to_nest(i + 1); 
            user_circuit->get_circuit_components().back()->add_to_nest(parallel_level);
            if(i != branches - 1) {
              user_circuit->set_circuit_schematic( " || "); // Parallel connection
            } else {
              user_circuit->set_circuit_schematic( "~]-"); // End of parallel connection
            }
          }
          parallel_level += 1; // Increment for next parallel circuit on main wire
          not_first_connection = true;
          break;
        }
        case 3: {
          std::cout << "The circuit has been closed." << std::endl;
          user_circuit->set_circuit_schematic("--o"); // Close terminal in diagrams
          incomplete_circuit = false;
          break;
        }
        default:
          std::cout << "Select a valid option from list" << std::endl; // sort out
          break;
      }
    }
    user_circuit->set_impedance(); // Compute the impedance
    slow_print("creating...rendering...building...constructing...mapping...");
    user_circuit->print_circuit_information(); // Print the circuit information to console
  }
  first_circuit = false;
}

void add_to_node(std::unique_ptr<circuit>& circuit, const std::vector<std::shared_ptr<component>>& components, int nest_level, int parallel_level, int branch, int max_branch)
{
  // This function is similar to the original
  // Passes the nest level and increments for every recursion
  nest_level += 1;
  bool open_branch{true};
  bool not_first_connection{false};
  while(open_branch) {
    if(not_first_connection == true) {
      std::cout << "==============================================================\n"
                << "You are STILL in BRANCH " << (branch) << " at NEST LEVEL " << nest_level - 1 << std::endl;
    }
    std::cout << "--------------------------------------------------------------\n"
              << "Choose the connection for this node by typing preceding number.\n"
              << "--------------------------------------------------------------\n"
              << "1: Add component (nest in series)\n"
              << "2: Nest components in parallel" << std::endl;
    if(not_first_connection == true) {
      std::cout << "3: Close branch" << std::endl;
    }
    std::cout << "-> ";
    int connection_choice;
    if(not_first_connection == true) {
      connection_choice = valid_choice(3); 
    } else {
      connection_choice = valid_choice(2); 
    }

    switch (connection_choice) {
      case 1: {
        int component_choice;
        std::cout << "Choose a component from the components library to add to parallel branch\n"
                  << "by typing the preceding number.\n"
                  << "--------------------------------------------------------------" << std::endl;
        list_components(components);
        std::cout << "-> ";
        component_choice = valid_choice(components.size());

        std::complex<double> new_impedance{components[component_choice - 1]->get_impedance()};
        std::shared_ptr<component> component_copy = components[component_choice - 1]->clone();
        circuit->add_component(component_copy, 0, circuit->get_frequency());
        if(not_first_connection == true) {
          circuit->set_circuit_schematic("--");
        }
        circuit->set_circuit_schematic(components[component_choice - 1]->get_symbol());
        not_first_connection = true;
        break;
      }
      case 2: {
        std::cout << "How many components do you want to add in parallel?\n"
                  << "-> ";
        int branches{valid_integer(2)};
        std::cout << "--------------------------------------------------------------\n"
                  << "You have chosen to add " << branches << " components in parallel.\n"
                  << "--------------------------------------------------------------" << std::endl;
        circuit->set_circuit_schematic("[~");
        for(int i{}; i != branches; ++i) {
          std::cout << "==============================================================\n"
                    << "You are in BRANCH " << (i + 1) << " at NEST LEVEL " << nest_level << std::endl;

          add_to_node(circuit, components, nest_level, parallel_level, i+1, branches); // Recursion
          circuit->get_circuit_components().back()->add_to_nest(i + 1);

          if(i != branches - 1) {
            // For all but the last branches, the nest level must be added manually
            circuit->get_circuit_components().back()->add_to_nest(branch);
            if(nest_level < 3) {
              circuit->get_circuit_components().back()->add_to_nest(parallel_level);
            }
            circuit->set_circuit_schematic(" || ");
          } else {
            circuit->set_circuit_schematic("~]");
          }
        }
        not_first_connection = true;
        break;
      }
      case 3: {
        std::cout << "This branch has been closed" << std::endl;
        if(branch == max_branch) {
          std::cout << "==============================================================\n"
                    << "You are BACK in BRANCH " << branch - 1<< " at NEST LEVEL " << nest_level - 2 << std::endl; 
        }

        open_branch = false;
        break;
      }
      default:
        std::cout << "Select a valid option from the list" << std::endl; 
        break;
    }
  }
}
