#include "Data_Loader.h"
#include "Splitter.h"
#include "Gini_Splitter.h"
#include "Entropy_splitter.h"
#include "Node.h"
#include "Internal_Node.h"
#include "Leaf_Node.h"
#include "Decision_Tree.h"
#include "Random_Forest.h"


// g++ -o project Data_Loader.cpp, Splitter.cpp, Gini_Splitter.cpp, Entropy_Splitter.cpp, Internal_Node.cpp, Leaf_Node.cpp, Decision_Tree.cpp, Random_Forest.cpp, Project_Main.cpp


int main() {

    std::string file_name{"breast_cancer_data_set.csv"};
    float train_fraction{0.9};
    bool exclude_first_row{true};

    int max_tree_depth{1000};
    int min_split_num{2};
    bool train_on_bootsrapped_data{false};

    
    std::shared_ptr<Data_Loader> data_loader = std::make_shared<Data_Loader>(file_name, exclude_first_row, train_fraction);
    std::shared_ptr<Splitter> gini_splitter = std::make_shared<Gini_Splitter>();
    Decision_Tree dt1(data_loader, gini_splitter, train_on_bootsrapped_data, max_tree_depth, min_split_num);
    
    dt1.fit();
    dt1.evaluate_test_data();

    return 0; 
}
