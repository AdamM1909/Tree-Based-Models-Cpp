/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 12:15:55
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-11 15:38:52
 * @ Description: Implementation of the Internal Node derived class.
 */

#include "Internal_Node.h"

Internal_Node::~Internal_Node() 
{
    delete left_child_;
    delete right_child_;
}
float Internal_Node::predict(const std::vector<float>& features) const 
{
    return (features[feature_index_] <= threshold_) ? left_child_->predict(features) : right_child_->predict(features);
}