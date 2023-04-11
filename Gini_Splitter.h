/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 11:29:08
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-11 15:19:32
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
    double calculate_node_score(const std::vector<std::pair<std::vector<float>, float>>& data, const std::vector<size_t> indexes) const;
};

#endif