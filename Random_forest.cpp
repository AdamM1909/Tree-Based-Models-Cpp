/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-10 14:58:54
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-11 16:15:49
 * @ Description: Implementation of the Random_Forest class.
 */

#include "Random_Forest.h"

Random_Forest::Random_Forest(std::shared_ptr<Data_Loader> data_loader, std::shared_ptr<Splitter> splitter, 
                int num_trees, int max_tree_depth, int min_samples_split) :
        data_loader_(data_loader),splitter_(splitter), num_trees_(num_trees), max_tree_depth(max_tree_depth), 
        min_samples_split(min_samples_split) {}
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
void Random_Forest::evaluate_test_data()
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
        const std::vector<float>& features{data_loader_->test_data()[i].first};
        int true_label = data_loader_->test_data()[i].second;
        int predicted_label = predict(features);
        if (predicted_label == true_label) {num_correct++;}
        confusion_matrix[predicted_label][true_label]++;
    }
    double accuracy = static_cast<double>(num_correct) / static_cast<double>(data_loader_->test_data().size());
    std::cout<<"Test Data Accuracy: "<<accuracy<<std::endl;
    std::cout<<"- - - - - - - - - - - - - - -"<<std::endl;
    std::cout<<"Test Data Confusion matrix:\n "<< std::endl;

    // Print out a nicely formatted confusion matrix.
    std::cout<<"\t\t\t"<<"True Labels"<<"\t\n\t\t\t";
    for (size_t i{0}; i < data_loader_->n_labels(); ++i) {std::cout<<i<<"\t";}
    std::cout << std::endl;

    // Print rows and row labels
    for (size_t i{0}; i < data_loader_->n_labels(); ++i) 
    {    
        (i == 0) ? std::cout<<"Predicted Labels " : std::cout<<"\t\t ";
        std::cout<<i<<"\t";
        for (size_t j{0}; j < data_loader_->n_labels(); ++j) {std::cout<<confusion_matrix[i][j]<<"\t";}
        std::cout<<std::endl;
    }
    std::cout<<"- - - - - - - - - - - - - - -"<<std::endl;
}
std::shared_ptr<Splitter> Random_Forest::get_splitter() const {return splitter_;}
std::shared_ptr<Data_Loader> Random_Forest::get_data_loader() const {return data_loader_;}


