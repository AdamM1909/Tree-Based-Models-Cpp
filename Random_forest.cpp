/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-10 14:58:54
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-11 16:51:03
 * @ Description: Implementation of the Random_Forest derived class.
 */

#include "Random_Forest.h"
#include "Tree_Model.h"

Random_Forest::Random_Forest(std::shared_ptr<Data_Loader> data_loader, std::shared_ptr<Splitter> splitter, 
                int num_trees, int max_tree_depth, int min_samples_split) :
                Tree_Model(data_loader, splitter, max_tree_depth, min_samples_split),
                num_trees_(num_trees) {}
Random_Forest::~Random_Forest() {};
void Random_Forest::fit() 
{
    trees_.reserve(num_trees_);
    for (size_t i{0}; i < num_trees_; i++) 
    {
        auto tree = std::make_shared<Tree_Model>(data_loader_, splitter_, true, max_tree_depth, min_samples_split);
        tree->fit();
        std::cout<<"Tree "<<i+1<<"/"<<num_trees_<<" built."<<std::endl;
        trees_.push_back(tree);
    }
};
float Random_Forest::predict(const std::vector<float>& features) const
{   
    std::unordered_map<float, int> label_votes;
    // Iterate over the decision trees and use each one to make a prediction
    for (auto& tree : trees_) 
    {
        float prediction = tree->predict(features);
        label_votes[prediction]++;
    }

    float best_label{0};
    int max_votes{0};
    for (const auto& pair : label_votes) 
    {
        if (pair.second > max_votes) 
        {
            best_label = pair.first;
            max_votes = pair.second;
        }
    }
    return best_label;
}

