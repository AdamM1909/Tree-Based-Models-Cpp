/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 15:04:53
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-12 16:46:36
 * @ Description: Fits a decision tree and a radnom forest to a data set printing out the test accuracy and the confusion matricies.
 * 
 * Run with g++ -o Project Data_Loader.cpp, Splitter.cpp, Gini_Splitter.cpp, Entropy_Splitter.cpp, Internal_Node.cpp, Leaf_Node.cpp, Tree_Model.cpp, Decision_Tree.cpp, Random_Forest.cpp, Project_Main.cpp
 * ./Project
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
    // Hyper-parameters 
    std::string file_name{"breast_cancer_data_set.csv"};
    // std::string file_name{"test_data_set.txt"};
    float train_fraction{0.5};
    bool exclude_first_row{true};
    std::shared_ptr<Data_Loader> data_loader = std::make_shared<Data_Loader>(file_name, exclude_first_row, train_fraction);
    std::shared_ptr<Splitter> gini_splitter = std::make_shared<Gini_Splitter>();

    // for (size_t i = 0; i < data_loader->train_data().size(); i++)
    // {
    //     std::cout<<data_loader->train_data()[i].first[0]<<"|"<<data_loader->train_data()[i].second<<std::endl;
    // }
    // std::cout<<"------"<<std::endl;
    // auto bs = data_loader->bootstrapped_train_data();
    
    // for (size_t i = 0; i < bs.size(); i++)
    // {
    //     std::cout<<bs[i].first[0]<<"|"<<bs[i].second<<std::endl;
    // }
    // std::cout<<"------"<<std::endl;
    
    // gini_splitter->find_best_split(bs);
    // std::cout<<"------"<<std::endl;
    // gini_splitter->find_best_split(data_loader->train_data());

    // Decision Tree
    int max_tree_depth{1000};
    int min_split_num{2};
    bool train_DT_on_bootsrapped_data{false};
    std::cout<<"Decision tree: \n"<<std::endl;
    Decision_Tree dt1(data_loader, gini_splitter, train_DT_on_bootsrapped_data, max_tree_depth, min_split_num);
    dt1.fit();
    dt1.evaluate_test_data();

    // Random Forest 
    int num_trees{5};
    std::cout<<"\n\nRandom Forest with "<<num_trees<<" trees:"<<std::endl;
    Random_Forest rf1(data_loader, gini_splitter, num_trees, max_tree_depth, min_split_num);
    rf1.fit();
    rf1.evaluate_test_data();
    return 0; 
}
