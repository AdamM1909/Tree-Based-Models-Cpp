/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 12:37:37
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-05-01 12:05:16
 * @ Description: Header file for the Decision_Tree class.
 * 
 * This class has access via a shared pointer to a Data_Loader and Splitter object
 * and builds a decision tree model to fit either the train data set or a boostrapped 
 * train data set. The "recursively_build_tree" fucntion creates the decsion tree model
 * returning the root to the tree. 
 */

#ifndef DECISION_TREE_H
#define DECISION_TREE_H

#include <cstddef>
#include <memory>
#include "Data_Loader.h"
#include "Splitter.h"
#include "Node.h"
#include "Tree_Model.h"
#include <memory>


class Decision_Tree : public Tree_Model
{
public:
    Decision_Tree(std::shared_ptr<Data_Loader> data_loader, std::shared_ptr<Splitter> splitter, bool boostrapped_data,
                 int max_tree_depth = 10, int min_samples_split = 2);
    virtual ~Decision_Tree();
    virtual void fit();
    friend std::ostream& operator<<(std::ostream& os, const Decision_Tree& Decision_Tree);
    virtual float predict(const std::vector<float>& features) const;
private:
    // Node* root_;
    std::unique_ptr<Node> root_;
    bool boostrapped_data_;
    bool is_pure_node(const std::vector<std::pair<std::vector<float>, int>>& data);
    bool is_valid_leaf(const std::vector<std::pair<std::vector<float>, int>>& data, const int depth);
    std::unordered_map<int, std::size_t> label_counts(const std::vector<std::pair<std::vector<float>, int>>& data) const;
    float majority_vote_classify(const std::vector<std::pair<std::vector<float>, int>>& data);
    std::unique_ptr<Node> recursive_build_tree(const std::vector<std::pair<std::vector<float>, int>>& data, int depth);
};
#endif