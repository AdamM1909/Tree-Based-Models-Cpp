/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 09:25:05
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-11 14:48:46
 * @ Description: Header file for the Splitter base class. 
 * 
 * Splitter objects derived from this base class find the optimal feature and feature threshold
 * to apply a binary split to a numerical dataset. For each feature of the data set, this class
 * sorts the data on this feature and calculates a splitting score for all possible bianry thresholds.
 * It finds the best split threshold for each feature and returns the best feature to split on.
 */


#ifndef SPLITTER_H
#define SPLITTER_H

#include <algorithm>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <numeric>
#include <set>

class Splitter
{
    public:
        virtual ~Splitter();
        virtual double calculate_node_score(const std::vector<std::pair<std::vector<float>, float>>& data, const std::vector<size_t> indexes) const=0;
        std::vector<size_t> sort_by_feature(const std::vector<std::pair<std::vector<float>, float>>& data, int feature_idx);
        double calculate_split_score(const std::vector<std::pair<std::vector<float>, float>>& data, int feature_idx, std::vector<size_t> left_indexes, std::vector<size_t> right_indexes);
        std::vector<std::pair<double, double>> calculate_split_scores(const std::vector<std::pair<std::vector<float>, float>>& data, 
                int feature_idx, std::vector<size_t> sorted_indexes);
        std::pair<size_t, float> find_best_split(const std::vector<std::pair<std::vector<float>, float>>& data);
        size_t index_of_min_second_element(const std::vector<std::pair<double, double>>& vec);
        int calc_n_labels(const std::vector<std::pair<std::vector<float>, float>>& data);
        std::unordered_map<int, std::size_t> label_counts(const std::vector<std::pair<std::vector<float>, float>>& data, const std::vector<size_t> indexes) const;
};
#endif

