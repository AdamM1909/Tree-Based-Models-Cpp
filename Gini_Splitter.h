/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 11:29:08
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-14 10:29:10
 * @ Description: Header file for the Gini_Splitter derived class.
 * 
 * This class inherets all the utility functions of the Splitter base class 
 * and implements the "calculate_node_score" member function based on the Gini Impurity metric.
 * See: https://en.wikipedia.org/wiki/Decision_tree_learning#Gini_impurity.
 */


#ifndef GINI_SPLITTER_H
#define GINI_SPLITTER_H

#include "Splitter.h"

class Gini_Splitter : public Splitter
{
public:
    virtual ~Gini_Splitter();
    double calculate_node_score_from_label_counts(const std::unordered_map<int, size_t> &label_counts_map, const size_t n_data_points) const;
};

#endif