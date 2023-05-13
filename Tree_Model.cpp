
#include "Tree_Model.h"
#include "Data_Loader.h"
#include <memory>

Tree_Model::Tree_Model(std::shared_ptr<Data_Loader> data_loader, std::shared_ptr<Splitter> splitter, 
                    int max_tree_depth, int min_samples_split) :
                    data_loader_(data_loader), splitter_(splitter), max_tree_depth_(max_tree_depth), 
                    min_samples_split_(min_samples_split) {};
Tree_Model::~Tree_Model() {};
void Tree_Model::evaluate_test_data() const
{
    // Initilise the confusion matrix with all zeros.
    std::vector<std::vector<int>> confusion_matrix(data_loader_->n_labels(), std::vector<int>(data_loader_->n_labels(), 0));
    int num_correct{0};
    // Catch if there are no testing data points. 
    if (data_loader_->test_data().size() == 0)
    {
        std::cout<<"There are no data points in the test set to evaluate."<<std::endl;
        return;
    }
    // Loop over the testing data set and predict each point. 
    for (size_t i{0}; i < data_loader_->test_data().size(); ++i) 
    {
        const std::vector<float>& features = data_loader_->test_data()[i].first;
        int true_label = data_loader_->test_data()[i].second;
        int predicted_label = predict(features);
        if (predicted_label == true_label) {num_correct++;}
        confusion_matrix[predicted_label][true_label]++;
    }

    double accuracy = static_cast<double>(num_correct) / static_cast<double>(data_loader_->test_data().size());
    std::cout<<"---------------"<<std::endl;
    std::cout<<"Test Data Accuracy: "<<accuracy<<std::endl;
    std::cout<<"---------------"<<std::endl;
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
    std::cout<<"---------------"<<std::endl;
};
std::shared_ptr<Splitter> Tree_Model::get_splitter() const {return splitter_;}
std::shared_ptr<Data_Loader> Tree_Model::get_data_loader() const {return data_loader_;}
