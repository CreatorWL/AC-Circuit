//
// Created by Will Lloyd on 06/05/2021.
//

#ifndef standard_values_hpp
#define standard_values_hpp

// Standard values chosen at random when creating a random component
const float resistor_standard_values [30] = {1, 1.2, 1.5, 1.8, 2.2,
                                              10, 12, 15, 18, 22,
                                              100, 120, 150, 180, 220,
                                              1000, 1200, 1500, 1800, 2200,
                                              10000, 12000, 15000, 18000, 22000,
                                              100000, 120000, 150000, 180000, 220000}; // In Ohms
const float capacitor_standard_values [30]= {0.00001, 0.000012, 0.000015, 0.000018, 0.000022,
                                              0.0001, 0.00012, 0.00015, 0.00018, 0.00022,
                                              0.001, 0.0012, 0.0015, 0.0018, 0.0022,
                                              0.01, 0.012, 0.015, 0.018, 0.022,
                                              0.1, 0.12, 0.15, 0.18, 0.22,
                                              1, 1.2, 1.5, 1.8, 2.2,}; // In microFarads
const float inductor_standard_values [30] = {0.001, 0.0012, 0.0015, 0.0018, 0.0022,
                                              0.01, 0.012, 0.015, 0.018, 0.022,
                                              0.1, 0.12, 0.15, 0.18, 0.22,
                                              1, 1.2, 1.5, 1.8, 2.2,
                                              10, 12, 15, 18, 22,
                                              100, 120, 150, 180, 220,}; // In microHenrys

#endif /*standard_values_hpp*/
