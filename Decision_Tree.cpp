/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 15:04:53
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-13 19:16:06
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
Decision_Tree::~Decision_Tree() {}//delete root_;}
void Decision_Tree::fit() 
{
    root_ = boostrapped_data_ ? recursively_build_tree(data_loader_->bootstrapped_train_data(), 0) 
                              : recursively_build_tree(data_loader_->train_data(), 0);  
}
float Decision_Tree::predict(const std::vector<float>& features) const {return root_->predict(features);}
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
void Decision_Tree::evaluate_test_data()
{
    std::vector<std::vector<int>> confusion_matrix(data_loader_->n_labels(), std::vector<int>(data_loader_->n_labels(), 0));
    int num_correct{0};
    if (data_loader_->test_data().size() == 0)
    {
        std::cout << "There are no data points in the test set to evaluate."<<std::endl;
        return;
    }

    for (size_t i{0}; i < data_loader_->test_data().size(); ++i) 
    {
        const std::vector<float>& features = data_loader_->test_data()[i].first;
        int true_label = data_loader_->test_data()[i].second ;
        int predicted_label = predict(features);
        if (predicted_label == true_label) {num_correct++;}
        confusion_matrix[predicted_label][true_label]++;
    }

    double accuracy = static_cast<double>(num_correct) / static_cast<double>(data_loader_->test_data().size());
    // std::cout<<"- - - - - - - - - - - - - - -"<<std::endl;
    std::cout<<"Test Data Accuracy: "<<accuracy<<std::endl;
    std::cout<<"- - - - - - - - - - - - - - -"<<std::endl;
    std::cout<<"Test Data Confusion matrix:\n "<< std::endl;

    // Print out a nicely formatted confusion matrix.
    std::cout<<"\t\t\t"<<"True Labels"<<"\t\n\t\t\t";
    for (size_t i{0}; i < data_loader_->n_labels(); ++i) {std::cout<<i<<"\t";}
    std::cout << std::endl;

    for (size_t i{0}; i < data_loader_->n_labels(); ++i) 
    {    
        (i == 0) ? std::cout<<"Predicted Labels " : std::cout<<"\t\t ";
        std::cout<<i<<"\t";
        for (size_t j{0}; j < data_loader_->n_labels(); ++j) {std::cout<<confusion_matrix[i][j]<<"\t";}
        std::cout<<std::endl;
    }
    std::cout<<"- - - - - - - - - - - - - - -"<<std::endl;
}
bool Decision_Tree::is_pure_node(const std::vector<std::pair<std::vector<float>, int>>& data) 
{
    int pure_class{data[0].second}; 
    for (const auto& data_point : data) 
    {
        if (data_point.second != pure_class) {return false;}
    }
    return true; 
};
 std::unordered_map<int, std::size_t> Decision_Tree::label_counts(const std::vector<std::pair<std::vector<float>, int>>& data) const
{
    std::unordered_map<int, std::size_t> label_count_map;
    std::for_each(data.begin(), data.end(), [&label_count_map](const std::pair<std::vector<float>, float>& pair) {
        label_count_map[pair.second]++;});
    return label_count_map;
};
float Decision_Tree::majority_vote_classify(const std::vector<std::pair<std::vector<float>, int>>& data)
{
    float majority_label{0};
    std::size_t max_count{0};
    std::unordered_map<int, std::size_t> count_map{label_counts(data)};
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
    return (depth >= max_tree_depth_ || data.size() <= min_samples_split_ || pure) ? true : false;
}
std::unique_ptr<Node> Decision_Tree::recursively_build_tree(const std::vector<std::pair<std::vector<float>, int>>& data, int depth) 
{
    if (is_valid_leaf(data, depth)) {return std::unique_ptr<Node>(new Leaf_Node(majority_vote_classify(data), depth));}
    std::pair<size_t, float> best_split = splitter_->find_best_split(data);
    size_t feature_idx = best_split.first;
    float threshold = best_split.second;
    
    // Split data
    std::vector<std::pair<std::vector<float>, int>> left_data;
    std::vector<std::pair<std::vector<float>, int>> right_data;
    for (const auto& data_point : data) 
    {
        (data_point.first[feature_idx] <= threshold) ? left_data.push_back(data_point) : right_data.push_back(data_point);
    }

    // may have an issue here... or maybe weve already 
    if (left_data.empty() || right_data.empty()) {
        // Don't create empty child nodes
        return std::unique_ptr<Node>(new Leaf_Node(majority_vote_classify(data), depth));
    } 
    // Create split node with non-empty child nodes.
    std::unique_ptr<Node> left_child = recursively_build_tree(left_data, depth + 1);
    std::unique_ptr<Node> right_child = recursively_build_tree(right_data, depth + 1);
    // If we get here the above two lines returned two leaf nodes so must return a 
    // new split node so recursive tree build continues.
    return std::unique_ptr<Node>(new Internal_Node(feature_idx, threshold, std::move(left_child), std::move(right_child), depth));
};