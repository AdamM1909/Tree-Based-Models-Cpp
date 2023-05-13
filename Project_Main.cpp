/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 15:04:53
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-05-13 12:08:48
 * @ Description: 
 * Demonsatrtes the splitter public interface with a toy data set. 
 *  
 * Fits a decision tree and a random forest to a data set printing out the test accuracy and the confusion matricies.
 * 
 * Compile with with:  g++ -o Project Data_Loader.cpp, Splitter.cpp, Gini_Splitter.cpp, Entropy_Splitter.cpp, Node.cpp, Internal_Node.cpp, Leaf_Node.cpp, Tree_Model.cpp, Decision_Tree.cpp, Random_Forest.cpp, Project_Main.cpp
 * Run with: ./Project
 */



#include "Data_Loader.h"
#include "Splitter.h"
#include "Gini_Splitter.h"
#include "Entropy_splitter.h"
#include "Node.h"
#include "Internal_Node.h"
#include "Leaf_Node.h"
#include "Tree_Model.h"
#include "Decision_Tree.h"
#include "Random_Forest.h"

int main() 
{
    // Toy example to show Splitter public interface. 
    std::string example_1_file_name{"test_data_set.txt"};
    float example_1_train_fraction{1.0};
    bool example_1_exclude_first_row{false};
    Data_Loader example_1_data_loader(example_1_file_name, example_1_exclude_first_row, example_1_train_fraction);
    Gini_Splitter example_1_gini_splitter;
    example_1_gini_splitter.calculate_split_scores(example_1_data_loader.train_data(), 0, true);
    example_1_gini_splitter.find_best_split(example_1_data_loader.train_data(), true);
    
    // Breast cancer classification data set example. This fits a decsion tree and a random forest. 
    std::string file_name{"breast_cancer_data_set.csv"};
    float example_2_train_fraction{0.8};
    bool example_2_exclude_first_row{true};
    std::shared_ptr<Data_Loader> data_loader = std::make_shared<Data_Loader>(file_name, example_2_exclude_first_row, example_2_train_fraction);
    std::shared_ptr<Splitter> gini_splitter = std::make_shared<Gini_Splitter>();


    // Fitting the decision tree.
    int max_tree_depth{3};
    int min_split_num{2};
    bool train_DT_on_bootsrapped_data{false};
    Decision_Tree dt1(data_loader, gini_splitter, train_DT_on_bootsrapped_data, max_tree_depth, min_split_num);
    dt1.fit();
    std::cout<<"Decsion Tree:"<<std::endl;
    std::cout<<dt1<<std::endl;
    dt1.evaluate_test_data();

    
    // Fitting the random forest 
    int num_trees{200};
    std::cout<<"\n\nRandom Forest with "<<num_trees<<" trees:"<<std::endl;
    Random_Forest rf1(data_loader, gini_splitter, num_trees, max_tree_depth, min_split_num);
    rf1.fit();
    rf1.evaluate_test_data();

    return 0; 
}
