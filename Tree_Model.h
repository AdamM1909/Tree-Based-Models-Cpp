#ifndef TREE_MODEL_H
#define TREE_MODEL_H

#include "Data_Loader.h"
#include "Splitter.h"
#include <memory>

class Tree_Model
{
public:
    Tree_Model(std::shared_ptr<Data_Loader> data_loader, std::shared_ptr<Splitter> splitter,
            int max_tree_depth, int min_samples_split);
    virtual ~Tree_Model();
    virtual void fit() = 0;
    virtual float predict(const std::vector<float>& features) const=0;
    virtual void evaluate_test_data();
    std::shared_ptr<Splitter> get_splitter() const;
    std::shared_ptr<Data_Loader> get_data_loader() const;
protected:
    std::shared_ptr<Data_Loader> data_loader_;
    std::shared_ptr<Splitter> splitter_;
    int max_tree_depth_;
    int min_samples_split_;
};
#endif