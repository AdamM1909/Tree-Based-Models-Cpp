/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 12:15:55
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-14 14:07:13
 * @ Description: Implementation of the Internal Node derived class.
 */

#include "Internal_Node.h"
Internal_Node::Internal_Node(int feature_index, float threshold, std::unique_ptr<Node> left_child, std::unique_ptr<Node> right_child, int depth)
        : feature_index_(feature_index), threshold_(threshold), depth_(depth), left_child_(std::move(left_child)), 
          right_child_(std::move(right_child)) {};
Internal_Node::~Internal_Node() {}
float Internal_Node::predict(const std::vector<float>& features) const 
{
    return (features[feature_index_] <= threshold_) ? left_child_->predict(features) : right_child_->predict(features);
}
void Internal_Node::print(std::ostream& os) const 
{
    // Print out layer data and use recursion to put children nodes into the output stream. 
    os<<"Internal node (depth="<<depth_<<"): Feature Index = "<<feature_index_<<", Threshold = "<<threshold_<<"\n";
    os<<"(<)  " <<*(left_child_)<<"\n"<< "(>)  " <<*(right_child_);
}