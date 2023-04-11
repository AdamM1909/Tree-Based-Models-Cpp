/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 11:36:17
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-11 15:17:29
 * @ Description: Header file for the Entropy_Splitter derived class.
 * 
 * This class inherets all the utility functions of the Splitter base class 
 * and implements the "calculate_node_score" member function based on the Entropy metric.
 * See: https://scikit-learn.org/stable/modules/tree.html#tree-mathematical-formulation.
 */


#include "Entropy_Splitter.h"

Entropy_Splitter::~Entropy_Splitter() {};
double Entropy_Splitter::calculate_node_score(const std::vector<std::pair<std::vector<float>, float>>& data, const std::vector<size_t> indexes) const
    {
            std::unordered_map<int, std::size_t> label_counts_map = label_counts(data, indexes);
            double n_data_points = indexes.size();
            double entropy = 0;
            for (auto count : label_counts_map) 
            {
                double p = count.second / n_data_points;
                entropy += p*std::log(p);
            }
            return -entropy;
    }  