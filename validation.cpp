#include "headers/validation.hpp"

double valid_component_value()
{
  // Validate user input for component value
  double valid_value{};
  bool invalid{true};
  while(invalid) {
    std::cin >> valid_value;
    if(std::cin.fail() || valid_value < 0 || (std::cin.peek() != ' ' && std::cin.peek() != '\n')) {
      std::cout << "Value cannot contain letters\n"
                << "Value cannot contain symbols\n"
                << "Value must be larger than zero\n"
                << "Try again\n"
                << "-> ";
      // Clear fail bit and ignore invalid input
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin >> valid_value;
    } else {
      invalid = false;
    }
  }
  return valid_value;
}

int valid_integer(int lower_limit)
{
  // Validate user input for integer value
  int valid_integer{};
  bool invalid{true};
  while(invalid) {
    std::cin >> valid_integer;
    if(std::cin.fail() || valid_integer < lower_limit || (std::cin.peek() != ' ' && std::cin.peek() != '\n')) {
      std::cout << "Value cannot contain letters\n"
                << "Value cannot contain symbols\n"
                << "Value cannot be a floating point\n"
                << "A minimum of two components can be add in parallel\n"
                << "Try again\n"
                << "-> ";
      // Clear fail bit and ignore invalid input
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin >> valid_integer;
    } else {
      invalid = false;
    }
  }
  return valid_integer;
}

int valid_choice(int upper_value)
{
  int valid_choice{};
  bool invalid{true};
  while(invalid) {
    std::cin >> valid_choice;
    if(std::cin.fail() || valid_choice <= 0 || valid_choice > upper_value) {
      std::cout << "Input must be an integer from the list\n"
                << "Try again\n"
                << "-> ";
      // Clear fail bit and ignore invalid input
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin >> valid_choice;
    }
    invalid = false;
  }
  return valid_choice;
}

bool yes_no_query(std::string statement)
{
  // Validates user choice for 'yes or no'
  // Return true to 'yes'
  char query_choice;
  std::cout << statement << "\n"
            << "Type 'y' for yes and 'n' for no\n"
            << "-> ";
  std::cin >> query_choice;
  while(query_choice != 'y' && query_choice != 'n' || (std::cin.peek() == ' ' || std::cin.peek() != '\n')) {
    std::cout << "---------------------------------------------\n"
              << "Input must be character 'y' or 'n', try again\n"
              << "-> ";
    // Clear fail bit and ignore invalid input
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> query_choice;
  }
  return query_choice == 'y';
}
