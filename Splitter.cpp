/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-08 14:45:09
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-11 15:39:34
 * @ Description: Implementation of the Splitter base class.
 */
#include "Splitter.h"
#include <iostream>

Splitter::~Splitter() {};
std::vector<size_t> Splitter::sort_by_feature(const std::vector<std::pair<std::vector<float>, float>>& data, int feature_idx)
{
    // Sort on feature without deep copying the data.
    std::vector<size_t> sorted_indices(data.size());
    std::iota(sorted_indices.begin(), sorted_indices.end(), 0); 
    std::sort(sorted_indices.begin(), sorted_indices.end(), [&data, feature_idx](size_t a, size_t b) 
        {return data[a].first[feature_idx] < data[b].first[feature_idx];});
    return sorted_indices;
}
double Splitter::calculate_split_score(const std::vector<std::pair<std::vector<float>, float>>& data, int feature_idx, std::vector<size_t> left_indexes, std::vector<size_t> right_indexes)
    {
        double left_score = calculate_node_score(data, left_indexes);
        double right_score = calculate_node_score(data, right_indexes);
        double split_score = (left_score * left_indexes.size() + right_score * right_indexes.size()) / data.size();
        return split_score;
    }
std::vector<std::pair<double, double>> Splitter::calculate_split_scores(const std::vector<std::pair<std::vector<float>, float>>& data, 
    int feature_idx, std::vector<size_t> sorted_indexes)
    {
        // Find the best split for this feature based on the criterion. 
        std::vector<std::pair<double, double>> split_scores;
        split_scores.reserve(data.size());
        std::vector<size_t> left_indexes = sorted_indexes;
        std::vector<size_t> right_indexes = {};
        // Set up first split.
        right_indexes.push_back(left_indexes.back());
        left_indexes.pop_back();
        // Iterate through all splits.
        for (size_t i{}; i < sorted_indexes.size() - 1; i++) 
            {   
                double split_score = calculate_split_score(data, feature_idx, left_indexes, right_indexes);
                // Dont need my indexes again so can modify in palce. "left_indexes" is a shallow copy of sorted_indexes.
                double threshold = (data[left_indexes.back()].first[feature_idx] + data[right_indexes.back()].first[feature_idx]) / 2;
                split_scores.push_back(std::make_pair(threshold, split_score));
                right_indexes.push_back(left_indexes.back());
                left_indexes.pop_back();
            }
        return split_scores;
    };
std::pair<size_t, float> Splitter::find_best_split(const std::vector<std::pair<std::vector<float>, float>>& data)
{
    std::vector<size_t> sorted_indexes(data.size());
    std::vector<std::pair<double, double>> splits_scores(data.size() - 1);
    size_t best_split_index;
    std::pair<double, double> best_split;
    std::vector<std::pair<double, double>> best_splits;
    best_splits.reserve(data[0].first.size());
    best_splits.clear();

    // Loop over all features in the data and find the best spilt for that feature.
    for (size_t feature{0}; feature < data[0].first.size(); feature++)
    {
        sorted_indexes = sort_by_feature(data, feature);
        splits_scores = calculate_split_scores(data, feature, sorted_indexes);
        best_split_index = index_of_min_second_element(splits_scores);
        best_split = splits_scores[best_split_index];
        best_splits.push_back(best_split);
    }
    size_t best_feature = index_of_min_second_element(best_splits);
    std::pair<size_t, double> best_feature_threshold = std::make_pair(best_feature, best_splits[best_feature].first);
    return best_feature_threshold;
}
size_t Splitter::index_of_min_second_element(const std::vector<std::pair<double, double>>& vec)
{
    double max_second = vec[0].second;
    size_t max_index = 0;

    for (size_t i = 1; i < vec.size(); i++)
    {
        if (vec[i].second < max_second)
        {
            max_second = vec[i].second;
            max_index = i;
        }
    }

    return max_index;
}
int Splitter::calc_n_labels(const std::vector<std::pair<std::vector<float>, float>>& data)
    {
        std::set<float> unique_labels;
        for (auto& pair : data) {unique_labels.insert(pair.second);}
        return unique_labels.size();
    }
std::unordered_map<int, std::size_t> Splitter::label_counts(const std::vector<std::pair<std::vector<float>, float>>& data, const std::vector<size_t> indexes) const
    {
        std::unordered_map<int, std::size_t> label_count_map;
        std::for_each(indexes.begin(), indexes.end(), [&data, &label_count_map](const int& idx) {
            label_count_map[data[idx].second]++;});
        return label_count_map;
    };