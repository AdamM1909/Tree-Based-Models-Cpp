/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-11 09:25:05
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-14 10:36:52
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
        virtual double calculate_node_score_from_label_counts(const std::unordered_map<int, size_t>& label_counts_map, const size_t n_data_points) const=0;
        std::vector<size_t> sort_by_feature(const std::vector<std::pair<std::vector<float>, int>>& data, const size_t feature_idx);
        std::vector<std::pair<double, double>> calculate_split_scores(const std::vector<std::pair<std::vector<float>, int>>& data, 
                const size_t feature_idx, std::vector<size_t> sorted_indexes);
        std::pair<size_t, float> find_best_split(const std::vector<std::pair<std::vector<float>, int>>& data);
        size_t minimum_score(const std::vector<std::pair<double, double>>& vec);
        std::unordered_map<int, size_t> label_counts(const std::vector<std::pair<std::vector<float>, int>>& data, const std::vector<size_t> indexes) const;
};
#endif

