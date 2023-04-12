/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 12:15:44
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-12 20:42:04
 * @ Description: Header file for the Internal_Node derived class.  
 * 
 * This class classifies a data point based on its feature and a bianry threshold.
 * It has pointer attriutes "left_child_" and "right_child_" which point to the two 
 * nodes which define the binary split. The "predict" member function and the destructor
 * use these pointers to call themselves recusively down a decision tree object. 
 */


#ifndef INTERNAL_NODE_H
#define INTERNAL_NODE_H
#include "Node.h"
#include <memory>
class Internal_Node : public Node 
{
public:
    Internal_Node(int feature_index, float threshold, std::shared_ptr<Node> left_child, std::shared_ptr<Node> right_child, int depth)
        : feature_index_(feature_index), threshold_(threshold), depth_(depth), left_child_(left_child), right_child_(right_child) {};
    virtual ~Internal_Node();
    float predict(const std::vector<float>& features) const;
    void print(std::ostream& os) const override;
private:
    int feature_index_;
    float threshold_;
    int depth_;
    std::shared_ptr<Node> left_child_;
    std::shared_ptr<Node> right_child_;
};
#endif