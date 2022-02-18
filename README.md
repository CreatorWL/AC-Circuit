# A.C. circuits Object-Oriented Programming in C++

# William Lloyd May 24, 2021

# Abstract

This paper details the structure and operation of an A.C. circuit program written in C++. The code contains classes for three ideal electrical components: resistors, capacitors and inductors. These classes derived from an abstract component base class. Circuits are constructed recursively by creating ’nodes’ where the user can either add a component, or create a set of parallel branches to new nodes. The circuit impedance is computed, along with the phase and magnitude of the impedance. A circuit diagram is printed to the console that displays the connections between components and their values. Smart pointers are used for objects to demonstrate effective memory management, and new components are instantiated using dynamic memory allocation.

# 1 Introduction

Object-orientated programming (OOP) is a way in which to structure a piece of code using classes. Each class acts as a blueprint to create individual instances of objects. OOP enables real life objects to be designed in terms of their attributes and behaviour[1]. For example, a class can be coded to define a specific electrical component. The class could contain blueprint information for its characteristic value, or its electrical impedance. OOP also extends the efficiency of a program by introducing features such as inheritance and polymorphism. These features essentially allow classes to share characteristics, such as the example of impedance[2].

The objective of this project is to create an interactive program that allows the user to build ideal components, and create an A.C. circuit. The code aims to demonstrate effective memory management using smart pointers, and polymorphism using inheritance. This report will first discuss the theory of A.C. circuits. It will then overview the circuit design and some of the key code. Finally, the report will close with an evaluation of the program, discussing the tests performed in order to validate the functionality.

# 2 A.C. circuit theory

An alternating-current (AC) circuit consists of an AC source that drives an electric current. The current oscillates over time, which periodically reverses the direction and alters its amplitude. An AC circuit’s resistance is described by the impedance. This is the effective resistance to the flow of current around the circuit. The impedance is given by Ohm’s Law:

<img src="https://render.githubusercontent.com/render/math?math=V=ZI"> (1)

where V is the voltage, Z is the impedance, and I is the current. The voltage and currents are sinusoidal, and are therefore typically expressed in complex exponential form. Thus, the impedance can be expressed as a complex number,


<img src="https://render.githubusercontent.com/render/math?math=Z = R + iX"> (2)

where R is the resistance, as experienced within a DC circuit, and X is the reactance, which arises from capacitance and inductance, causing the current to be out of phase with the the driving electromotive force of the circuit. Kirchhoff’s Law states that a circuit made up of N circuits in parallel or series, the impedance is given as


<img src="https://render.githubusercontent.com/render/math?math=Z_{\text {series }}=\sum_{i=0}^{n} Z_{i} \quad \text { and } \quad Z_{\text {parallel }}=\frac{1}{\sum_{i=0}^{n} \frac{1}{Z_{i}}}">


There are three types of ideal components used in AC circuits. These are resistors, capacitors and
 inductors.

All three have different properties, as shown in table 1. 



\[
  \begin{equation}
\begin{array}{l}
\text { Table 1: Caption }\\
\begin{array}{l|c|c|c|c}
\hline \hline \text { Component } & \text { Value (unit) } & \text { Differential } & \text { Impedance } & \text { Phase } \\
\hline \text { Resistor } & \text { Resistance - R - (ohms) } & V=I R & \mathrm{R} & 0 \\
\text { Capacitor } & \text { Capacitance - C - (farads) } & I=C \frac{d U}{d t} & -i \frac{1}{\omega C} & \frac{\pi}{2} \\
\text { Inductor } & \text { Inductance - L - (henrys) } & V=L \frac{d I}{d t} & i \omega L & -\pi 2 \\
\hline
\end{array}
\end{array}
\end{equation}
\]


 This project only concerns ideal-components, however, it should be known that in reality, components ware generally dissipate power[3].

# 3 Program design 3.1 File structure

The main.cpp file includes header files for a generic circuit class, a base component class, and derived classes for a resistor, conductor and capacitor. An interface class includes header files for the circuit class and each component class. The larger functions called in interface are stored in separate files for readability. The interface is called from main.cpp.

# 3.2 Classes
# 3.2.1 Component class

The component class is a virtual base class that prevents multiple instances of derived components. It is made up of protected member variables, and public member functions. These functions are either pure virtual or non-virtual. The most important of these variables and functions are highlighted below.

The component class contains the following set of protected member variables accessible to derived classes:
```cpp
std::string type{"component"};
std::string units{"units"};
double frequency {};
std::complex<double> impedance{std::complex<double>(0,0)}; // All
components rely on impedance
std::string symbol{"[~Component~]"}; std::deque<int> nest_levels;
```

  The integral member variable for the circuit calculations is the impedance, which uses the complex type from the standard numerical library. This variable stores the complex impedance for each component, and allows operations such as operator+ and operator/ between impedances. The nest levels container defines how many times a component is nested, in parallel or series, within a circuit. For example, if a component is added in series on the base wire between terminals, then (0) will be added to nest levels. For the first of two components added in parallel to the base wire, values of (1,1,0) and (1,2,0) will be added to the first and second component’s nest levels respectively. If the first component of this parallel pair is replaced by another two components nested in parallel, then the three components will be assigned nest levels of (1,1,1,0), (1,1,2,0), (1,2,0) respectively.

The base class provides pure virtual overridable member functions for specification in derived classes. The pure virtual functions include set impedance, for each components individual impedance, and a virtual destructor ∼component(){}, allowing each component to call its own destructor. Non-virtual member functions of component include

```cpp
double get_frequency() const; std::complex<double> get_impedance() const; double get_impedance_magnitude() const; double get_impedance_phase() const;
```

The trailing const keywords restrict the function from modifying the state of the object it is called upon.

# 3.2.2 Derived component classes

The component class is inherited by three classes: resistor, capacitor and inductor. Therefore, they inherit the member variables of component, including the complex impedance. Each derived component only has one new-defined private member corresponding to its value (i.e. resistance, capacitance or inductance). Each component contained a constructor that passes the value within

the initialiser list. The constructor also assigns string values to the type, units and symbol base class variables.

The private member variables are only accessible with setters and getters, demonstrating data encapsulation and data abstraction. The virtual function set impedance is overridden for each component according to the formulas in table 1. Once the impedance member variable has been assigned a value, polymorphism allows calling of the base-class functions get impedance magnitude and get impedance argument to get the magnitude and argument of the impedance respectively.

# 3.2.3 Circuit class

The circuit class is a generic class for storing components in series or parallel to form an A.C. circuit. It then calculates the impedance of the circuit, and prints the result to the console, along with other information about the circuit. The private members of circuit are

```cpp
double frequency {100};
std::complex<double> impedance{0,0}; std::vector<std::shared_ptr<component>> inner_components; std::string circuit_schematic{};
```

  The frequency variable is more relevant for the circuit class, for it factors in the impedance calculation of the circuit. It is user-defined and passed in the constructor initialiser list. The inner components variable is used to dynamically store shared ptr component objects. The impedance, similarly to the component classes, is of type std::complex<double>, and the circuit schematic is a string type variable that appends the symbols of the components in inner components, depending on whether they are stored in series or parallel.

The public member functions of circuit are mostly setters and getters for the private members. The notable function is set impedance, called when calculating the circuit impedance and assigning it to the impedance private member. First, it runs through two statements:

```cpp
if(inner_components.size() == 1) {
total_impedance = inner_components[0]->get_impedance();
} else if(inner_components.size() == 2) { if(inner_components[0]->get_nest_levels()[0] == 0) {
total_impedance = inner_components[0]->get_impedance() + inner_components[1]->get_impedance();
} else {
total_impedance = one_complex / ((one_complex /
}
inner_components[0]->get_impedance()) + (one_complex / inner_components[1]->get_impedance()));
```

The first of these statements checks if there is only one component in the circuit. If there is, then total impedance, defined earlier in the function, is set to the impedance of that component. The second statement checks if there are two components in the circuit. This either implies that there are two components added in series, or two components in parallel. In either case, total impedance is assigned to the corresponding summation of the two impedances given in equation 3. At the end of the function, total impedance is assigned to the private variables impedance.

The third possibility, where inner components is greater than two, requires a more complicated assessment. First, nest levels and impedance are stored within a std::multimap container for each component. Each component multimap is then stored within another multimap:

```cpp
std::multimap<int, std::multimap<std::deque<int>, std::complex< double>>, std::greater <int>> temp_impedance_map;
```

where each key is the size of the corresponding nest levels, and std::greater ensures that components are stored in the multimap from largest key to smallest key.

The function then enters a while loop with the condition temp impedace map.size() > 1. For each loop iteration, two iterators are initialised that compare each nest level against each other, without duplication, and without comparing one nest level against itself. For each comparison, there are three possibilities:

1. If each nest level is identical in length and values, then the two inner multimaps corre- sponding to iterator 1 and 2 are removed from temp impedace map. These are replaced with a new multimap where the impedance isthe sum of the two previous multimaps. This process reduces the size of temp impedace map by 1.

2. If each nest level is identical in length, and all values are the same apart from the second last value, this correspond to two components in parallel. The multimap corresponding to the second iterator is removed from temp impedace map. The first iterator will continue to compare against the rest of the multimaps. If there are other nest level keys corresponding to two components in parallel, then the second iterator is again removed. If there are no remaining parallel nest level keys, then the first iterator is replaced with a new multimap where the impedance is the parallel sum, according to equation 3, of all the matching keys. The nest level of the new multimap is equal to the nest level before it. If the nest level is first order (parallel connected to the main wire) then the new nest is (0), equal to a series component on the main wire. This reduces the size of temp impedace map by one less than the number of matching keys.

3. If the first iterator does not match to any second iterators, the first iterator is incremented.
For an example of this process, consider a circuit that contains one component in series, connected to two components in parallel. First, the while loop will compare the two parallel components against each other. These will be replaced with one component with impedance equal to inverse sum of the inverse impedances of each component, and a nest level of (0). The while loop will then compare this with the series component, and replace them with one component with an impedance equal to the sum of the two.
For any number of components, connected in any combination, the size of temp impedace map will eventually equal 1, the while loop will close, and the impedance of the final component is assigned to the circuit variable impedance.

# 3.3 Interface

The interface consists of functions that provide user interaction. The two primary functions are create component and create circuit.

# 3.3.1 Create component

The function create component passes a user defined characteristic value to the chosen component constructor. The component type can be any of the ideal components outlined above, or the user can create a random component with a random value. In the latter case, rand() is utilised to pick a random value from an array of standard values for a randomly selected component. Once a component is chosen manually or randomly, the function creates a shared ptr with ownership of the new component, and moves it into a vector components.

# 3.3.2 Create circuit

The function create circuit adds components to a circuit components library, adds nest levels to the components, sets the frequency of the circuit and its components, and calculates the impedance. The function closes after printing all of the circuit information to the console. Each circuit object is contained within the scope of the function, initiated by the following smart pointer:

```cpp
std::unique_ptr<circuit> user_circuit(new circuit());
```

Circuit components are added to ’nodes’. At each node, the user can either add a component in series, add components in parallel, or close the node. A while loop is set for each node until it is closed. Adding n components in parallel creates n ’branches’, and calls a function add to node. This function directs the user to the same set of options (series or parallel) for each branch. add to node will be called recursively if the user decides to add more components in parallel to the node of a parallel component. If the node is closed on a parallel component, then its nesting level is pushed into the component’s nest level container, as well as it’s position in the set of parallel components. This creates a nest level as described in section 3.2.1.

Once the node of the final component in parallel is closed, the program exits the while loop inside of add to node and returns either to the parallel node before it, or the base circuit line, depending on the nesting level. The function also creates the circuit diagram. For every component added to the circuit, the component symbol (private member) is appended to the circuit member circuit schematic using the addition assignment operator.

Once the circuit is complete, the function calls user circuit->set impedance() to set the impedance for the circuit, then calls user circuit->print circuit information() to print the circuit information to the console, including the diagram, the impedance, the impedance magni- tude and phase, and the components. Once the program exits create circuit, the memory is de-allocated (due to the unique ptr ownership), and the circuit destructor is called.

# 4 Program evaluation

The program was compiled with g++-8 and executed without warnings or errors. Following the introduction from the interface, the menu was presented:


============== Menu ============== Choose an item from the list by typing the preceding number. ================================== 1: Create component
2:  List components
3:  Modify components
4:  Create circuit
5:  Exit program
----------------------------------
->

In order to test the program, three components were made, and two circuits were constructed to test:

1. Components added in series 
2. Components added in parallel

This section will run through circuits 1 and 2. In the first, more information will be provided for the details that occur for every circuit.
First, three components were created: a resistor with R = 12 Ω, a capacitor with C = 100 μF and an inductor with L = 0.15 H. Next, a driving frequency of 50 (Hz) was input, which was followed by the menu:

=============================================================
Choose connection for this node by typing preceding number. -------------------------------------------------------------
1:  Add component in series
2:  Add component in parallel
3:  Complete circuit
-------------------------------------------------------------
For the first circuit, option (1) was selected and the components library was printed in the console. This was repeated three times, choosing the resistor, capacitor and inductor. After the final component was chosen, option (3) was selected to close the circuit. The following is a selection of the output:
===========================================
Circuit diagram: o---[∼R(12.0)∼]--[∼C(100000.0)∼]--[∼I(150000.0)∼]---o ===========================================
AC frequency: 50.00 Hz
Circuit impedance (R + Xi): (12.00 + 47.09i) Ohms Impedance magnitude: 48.60 Ohms
Impedance phase: 37.85 degrees ===========================================


The circuit diagram successfully displayed three components in series, connected between two A.C. nodes. It also correctly printed the circuit impedance, (12.00 + 47.09i) Ω, in accordance with the first part of equation 3. The magnitude and phase of the impedance were also correctly printed. The circuit information was followed by destructor messages for the three temporary components and the circuit, indicating that each object was successfully destroyed.

For the second circuit, the frequency was kept at 50 Hz. A resistor, capacitor and inductor were connected in parallel, with values of 1 kΩ, 160 μF and 140 mH respectively. The circuit produced the following diagram:

o---[∼R(1000.0) || C(160.0) || I(142000.0)∼]---o

successfully representing a parallel RCL circuit. The computed impedance was (1.29 - 35.86i) Ohms, in accordance with the second part of equation 3. Ending the program prompted six destructor messages for each component created, verifying that each object had been destroyed.

Overall, this evaluation of the program displayed effective results adhering to the design of code and the physics of A.C. circuits.

# 5 Conclusions

An object-orientated program was written for building an A.C. circuit. from components connected in series or parallel. The components (resistor, capacitor and inductor) were derived from a component base class and inherited its protected member variables. Each circuit was created using a generic class for storing component objects and calculating the total impedance. Components could also be nested in parallel with a recursion function. The program was tested with three circuits, connecting components in series, parallel and a combination of both. The total circuit impedance for each circuit was successfully computed. The ownership of each object was retained with a smart pointer. This ensured that dynamic memory was effectively managed. Additionally, destructors were called for each object, indicating no memory leaks. This program could be improved by including non-ideal components, which would provide more circuit information to the user. The program functionality could have been improved by including a vector for storing and editing circuits. Disregarding improvements, the code functioned correctly, and compiled without errors or warnings.

# 6 References

[1] Richard S Wiener and Lewis J Pinson. An introduction to object-oriented programming and C++. Addison-Wesley Longman Publishing Co., Inc., 1988.
[2] Polymorphism. https://www.cplusplus.com/doc/tutorial/polymorphism/. Accessed: 2021-05-20.
[3] R. Nave. Rlc series circuit. http://hyperphysics.phy-astr.gsu.edu/hbase/electric/ rlcser.html. Accessed: 2021-05-16.
8
