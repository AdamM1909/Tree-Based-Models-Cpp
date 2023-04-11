/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 13:59:34
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-11 15:18:51
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

class Random_Forest 
{
public:
    Random_Forest(std::shared_ptr<Data_Loader> data_loader, std::shared_ptr<Splitter> splitter, 
                int num_trees, int max_tree_depth, int min_samples_split);
    ~Random_Forest();
    void fit();
    float predict(const std::vector<float>& features) const;
    void evaluate_test_data();
    std::shared_ptr<Splitter> get_splitter() const;
    std::shared_ptr<Data_Loader> get_data_loader() const;
    int max_tree_depth;
    int min_samples_split;
    int num_trees_;
private:
    std::vector<std::shared_ptr<Decision_Tree>> trees_;
    std::shared_ptr<Data_Loader> data_loader_;
    std::shared_ptr<Splitter> splitter_;
};
#endif