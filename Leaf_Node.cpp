/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 12:08:40
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-12 19:54:02
 * @ Description: Implementaion of the Leaf_Node derived class.
 */
#include "Leaf_Node.h"
float Leaf_Node::predict(const std::vector<float>& features) const {return label_;}
Leaf_Node::~Leaf_Node() {};
void Leaf_Node::print(std::ostream& os) const{os<<"Leaf node (depth = "<<depth_<< "): Label = " << label_;}