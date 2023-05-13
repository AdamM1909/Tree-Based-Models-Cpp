/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-10 14:58:54
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-05-13 12:02:55
 * @ Description: Implementation of the Random_Forest derived class.
 */

#include "Random_Forest.h"
#include "Tree_Model.h"

Random_Forest::Random_Forest(std::shared_ptr<Data_Loader> data_loader,const std::shared_ptr<Splitter> splitter, 
                const int num_trees, const int max_tree_depth, const int min_samples_split) :
                Tree_Model(data_loader, splitter, max_tree_depth, min_samples_split),
                num_trees_(num_trees) {}
Random_Forest::~Random_Forest() {};
void Random_Forest::fit() 
{
    // Reserve the ememory. 
    trees_.reserve(num_trees_);
    // A loop to fit all the trees on different bootstrap samples.
    for (size_t i{0}; i < num_trees_; i++) 
    {
        std::shared_ptr<Decision_Tree> tree = std::make_shared<Decision_Tree>(data_loader_, splitter_, true, max_tree_depth_, min_samples_split_);
        tree->fit();
        std::cout<<"Tree "<<i+1<<"/"<<num_trees_<<" built."<<std::endl;
        trees_.push_back(tree);
    }
};
float Random_Forest::predict(const std::vector<float>& features) const
{   
    std::unordered_map<float, int> label_votes;
    // Iterate over the decision trees and use each one to make a prediction.
    for (auto& tree : trees_) 
    {
        float prediction = tree->predict(features);
        label_votes[prediction]++;
    }

    float best_label{0};
    int max_votes{0};
    // Aggregate in a majority. 
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

