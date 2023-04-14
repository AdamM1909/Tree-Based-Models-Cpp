/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 11:29:14
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-14 10:19:18
 * @ Description: Implementation of the Gini_Splitter derived class.
 */


#include "Gini_Splitter.h"

Gini_Splitter::~Gini_Splitter() {};
double Gini_Splitter::calculate_node_score(const std::vector<std::pair<std::vector<float>, int>>& data, const std::vector<size_t> indexes) const
{
    std::unordered_map<int, std::size_t> label_counts_map = label_counts(data, indexes);
    double n_data_points = indexes.size();
    double impurity = 1.0;
    for (const auto count : label_counts_map) 
        {
            double p = count.second / n_data_points;
            impurity -= p * p;
        }
    return impurity;
} 

double Gini_Splitter::calculate_node_score_from_label_counts(const std::unordered_map<int, size_t>& label_counts_map, const size_t n_data_points) const
{
    double impurity = 1.0;
    for (const auto& count : label_counts_map) 
    {
        double p = static_cast<double>(count.second) / n_data_points;
        impurity -= p * p;
    }
    return impurity;
}