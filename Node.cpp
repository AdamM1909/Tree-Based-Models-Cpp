#include "Node.h"

std::ostream& operator<<(std::ostream& os, const Node& node) 
{
    // This returns the output stream which the concrete classes add to. 
    node.print(os);
    return os;
}
