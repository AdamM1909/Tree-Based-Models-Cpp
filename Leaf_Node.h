/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 12:08:45
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-12 18:54:32
 * @ Description: Header file for the Leaf_Node derived class.
 * 
 * This class sits at the bottom of a decsion tree structure and returns a 
 * label for a given data point which is used for prediction. 
 */

#ifndef LEAF_NODE_H
#define LEAF_NODE_H
#include "Node.h"
class Leaf_Node : public Node 
{
public:
    Leaf_Node(float label, int depth) : label_(label), depth_(depth) {}
    virtual ~Leaf_Node();
    float predict(const std::vector<float>& features) const;
    void print(std::ostream& os) const;
private:
    float label_;
    int depth_;
};
#endif