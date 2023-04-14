/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 11:36:25
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-14 10:33:45
 * @ Description: Implementation of the Entropy_Splitter derived class.
 */

#ifndef ENTROPY_SPLITTER_H
#define ENTROPY_SPLITTER_H

#include "Splitter.h"

class Entropy_Splitter : public Splitter
{
public:
    virtual ~Entropy_Splitter();
    double calculate_node_score_from_label_counts(const std::unordered_map<int, size_t> &label_counts_map, const size_t n_data_points) const;
};

#endif