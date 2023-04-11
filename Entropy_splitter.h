/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 11:36:25
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-11 15:19:38
 * @ Description: Implementation of the Entropy_Splitter derived class.
 */

#ifndef ENTROPY_SPLITTER_H
#define ENTROPY_SPLITTER_H

#include "Splitter.h"

class Entropy_Splitter : public Splitter
{
public:
    virtual ~Entropy_Splitter();
    double calculate_node_score(const std::vector<std::pair<std::vector<float>, float>>& data, const std::vector<size_t> indexes) const;
};

#endif