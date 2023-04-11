#ifndef TREE_MODEL_H
#define TREE_MODEL_H

#include "Data_Loader.h"
#include "Splitter.h"
#include <memory>

class Tree_Model
{
public:
    virtual ~Tree_Model();
    virtual void fit() const=0;
    virtual float predict(const std::vector<float>& features) const=0;
    virtual void evaluate_test_data();
private:
    std::shared_ptr<Data_Loader> data_loader_;
    std::shared_ptr<Splitter> splitter_;
};
#endif