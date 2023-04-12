/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 12:07:04
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-12 19:27:39
 * @ Description: Header file for the Node base class. 
 * 
 * Node objects derived from this base class are sued to build decesion trees.
 * The pure virtual fuction "predict" defines how a data point is classified
 * by the node and hence the tree. This base class also inlcudes the output
 * stream overload definition which calls "print" on all node types.
 */

#ifndef NODE_H
#define NODE_H

#include <vector>
#include <iostream>
class Node 
{
public:
    virtual ~Node() {}
    virtual float predict(const std::vector<float>& features) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const Node& node);
    virtual void print(std::ostream& os) const = 0;
private:
    int depth_; 
};
#endif
