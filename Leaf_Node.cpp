/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 12:08:40
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-11 15:17:48
 * @ Description: Implementaion of the Leaf_Node derived class.
 */
#include "Leaf_Node.h"
float Leaf_Node::predict(const std::vector<float>& features) const {return label_;}
Leaf_Node::~Leaf_Node() {};