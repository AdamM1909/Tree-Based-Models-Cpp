/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 12:07:04
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-11 12:33:09
 * @ Description: Header file for the Node base class. 
 * 
 * Node objects derived from this base class are sued to build decesion trees.
 * The pure virtual fuction "predict" defines how a data point is classified
 * by the node and hence the tree.
 * 
 * There is no implmentation of this class as all memember fucntions are pure
 * virtual functions. 
 */

#ifndef NODE_H
#define NODE_H

#include <vector>
class Node 
{
public:
    virtual ~Node() {}
    virtual float predict(const std::vector<float>& features) const = 0;
private:
    int depth_; 
};
#endif
