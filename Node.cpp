#include "Node.h"

std::ostream& operator<<(std::ostream& os, const Node& node) 
{
    node.print(os);
    return os;
}
