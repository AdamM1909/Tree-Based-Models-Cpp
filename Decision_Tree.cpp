/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 15:04:53
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-05-13 11:58:48
 * @ Description: Implementation of the Decision_Tree class.
 */


#include "Decision_Tree.h"
#include "Node.h"
#include "Internal_Node.h"
#include "Leaf_Node.h"
#include <memory>

Decision_Tree::Decision_Tree(std::shared_ptr<Data_Loader> data_loader, const std::shared_ptr<Splitter> splitter, bool boostrapped_data,
                        const int max_tree_depth, const int min_samples_split) :
                        Tree_Model(data_loader, splitter, max_tree_depth, min_samples_split), 
                        root_(nullptr) {};
Decision_Tree::~Decision_Tree() {}
void Decision_Tree::fit() 
{
    root_ = boostrapped_data_ ? recursive_build_tree(data_loader_->bootstrapped_train_data(), 0) 
                              : recursive_build_tree(data_loader_->train_data(), 0);  
}
float Decision_Tree::predict(const std::vector<float>& features) const 
{
    // Check if the tree has been fit to the data yet
    if (root_ == nullptr) {
        std::cerr<<"Error: Cannot predict with a tree that has not been fit to the data yet."<<std::endl;
        throw std::runtime_error("Error: Cannot predict with a tree that has not been fit to the data yet.");
    } else {
        // Call the predict function on the root node of the tree
        return root_->predict(features);
    }
}

std::ostream& operator<<(std::ostream& os, const Decision_Tree& decision_tree) 
{
    if (decision_tree.root_!= nullptr) 
    {
        decision_tree.root_->print(os);
        return os;
    } else {
        os<<"Root is a null ptr so can't print";
        return os; 
    }
}
bool Decision_Tree::is_pure_node(const std::vector<std::pair<std::vector<float>, int>>& data) 
{
    int pure_class{data[0].second}; 
    for (const auto& data_point : data) 
    {
        // See if there's more than one class label type in this data set. 
        if (data_point.second != pure_class) {return false;}
    }
    return true; 
};
 std::unordered_map<int, std::size_t> Decision_Tree::label_counts(const std::vector<std::pair<std::vector<float>, int>>& data) const
{
    std::unordered_map<int, std::size_t> label_count_map;
    // Count the number of class labels in the data.
    std::for_each(data.begin(), data.end(), [&label_count_map](const std::pair<std::vector<float>, float>& pair) {
        label_count_map[pair.second]++;});
    return label_count_map;
};
float Decision_Tree::majority_vote_classify(const std::vector<std::pair<std::vector<float>, int>>& data)
{
    float majority_label{0};
    std::size_t max_count{0};
    std::unordered_map<int, std::size_t> count_map{label_counts(data)};
    // Find the largest number of label counts in a data set.
    for (auto& label_count : count_map) 
    {
        if (label_count.second > max_count) 
        {
            max_count = label_count.second;
            majority_label = label_count.first;
        }
    }
    return majority_label;
}
bool Decision_Tree::is_valid_leaf(const std::vector<std::pair<std::vector<float>, int>>& data, const int depth) 
{
    bool pure = is_pure_node(data);
    // Consider all the decision tree hyper-paramters.
    return (depth >= max_tree_depth_ || data.size() <= min_samples_split_ || pure) ? true : false;
}
std::unique_ptr<Node> Decision_Tree::recursive_build_tree(const std::vector<std::pair<std::vector<float>, int>>& data, int depth) 
{
    // First check if this data forms a leaf. 
    if (is_valid_leaf(data, depth)) {return std::unique_ptr<Node>(new Leaf_Node(majority_vote_classify(data), depth));}

    // If not start the recursive build by finding the best split for the data.
    std::pair<size_t, float> best_split = splitter_->find_best_split(data);
    size_t feature_idx = best_split.first;
    float threshold = best_split.second;
    
    // Split the data.
    std::vector<std::pair<std::vector<float>, int>> left_data;
    std::vector<std::pair<std::vector<float>, int>> right_data;
    for (const auto& data_point : data) 
    {
        (data_point.first[feature_idx] <= threshold) ? left_data.push_back(data_point) : right_data.push_back(data_point);
    }

    if (left_data.empty() || right_data.empty()) {
        // An additonal check for safety. 
        return std::unique_ptr<Node>(new Leaf_Node(majority_vote_classify(data), depth));
    } 

    // Use recursion to repeat the process for the left branches frist, then then right ranches. 
    std::unique_ptr<Node> left_child = recursive_build_tree(left_data, depth + 1);
    std::unique_ptr<Node> right_child = recursive_build_tree(right_data, depth + 1);
    // If we get here the above two lines returned two leaf nodes so must create the parent internal node for them.
    return std::unique_ptr<Node>(new Internal_Node(feature_idx, threshold, std::move(left_child), std::move(right_child), depth));
};