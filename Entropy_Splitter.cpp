/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 11:36:17
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-14 10:33:34
 * @ Description: Header file for the Entropy_Splitter derived class.
 * 
 * This class inherets all the utility functions of the Splitter base class 
 * and implements the "calculate_node_score" member function based on the Entropy metric.
 * See: https://scikit-learn.org/stable/modules/tree.html#tree-mathematical-formulation.
 */


#include "Entropy_Splitter.h"

Entropy_Splitter::~Entropy_Splitter() {};
double Entropy_Splitter::calculate_node_score_from_label_counts(const std::unordered_map<int, size_t>& label_counts_map, const size_t n_data_points) const
{
    double entropy = 0;
    for (const auto& count : label_counts_map) 
    {
        double p = static_cast<double>(count.second) / n_data_points;
        entropy += p*std::log(p);
    }
    return -entropy;
} 