/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 13:59:34
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-13 17:35:28
 * @ Description: Header file for the Random_Forest class.
 * 
 * This class has access via a shared pointer to a Data_Loader and Splitter object
 * and builds a random forest model. Each decsion tree in the model is costructed on
 * a bootsrapepd verion of the train data set. Labels are chosen on a majority vote
 * from all decsion trees in the model.  
 */
#ifndef RANDOM_FOREST_H
#define RANDOM_FOREST_H

#include <memory>
#include <vector>
#include "Splitter.h"
#include "Data_Loader.h"
#include "Decision_Tree.h"
#include "Tree_Model.h"

class Random_Forest : public Tree_Model
{
public:
    Random_Forest(std::shared_ptr<Data_Loader> data_loader, const std::shared_ptr<Splitter> splitter, 
            const int num_trees, const int max_tree_depth, const int min_samples_split);
    ~Random_Forest();
    virtual void fit() override;
    virtual float predict(const std::vector<float>& features) const;
    int num_trees_;
private:
    std::vector<std::shared_ptr<Tree_Model>> trees_;
};
#endif