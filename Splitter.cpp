/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-08 14:45:09
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-05-01 11:59:46
 * @ Description: Implementation of the Splitter base class.
 */
#include "Splitter.h"
#include <iostream>
#include <limits>

Splitter::~Splitter() {};
std::vector<size_t> Splitter::sort_by_feature(const std::vector<std::pair<std::vector<float>, int>>& data,const size_t feature_idx)
{
    // Sort on feature without deep copying the data.
    std::vector<size_t> sorted_indices(data.size());
    std::iota(sorted_indices.begin(), sorted_indices.end(), 0); 
    std::sort(sorted_indices.begin(), sorted_indices.end(), [&data, feature_idx](size_t a, size_t b) 
        {return data[a].first[feature_idx] < data[b].first[feature_idx];});
    return sorted_indices;
}
std::vector<std::pair<double, double>> Splitter::calculate_split_scores(const std::vector<std::pair<std::vector<float>, int>>& data, const size_t feature_idx, 
                                                                        const bool verbose)
{
    std::vector<size_t> sorted_indexes = sort_by_feature(data, feature_idx);
    if (verbose){std::cout<<"Feature : "<<feature_idx<<std::endl;}
    
    std::vector<std::pair<double, double>> split_scores;
    split_scores.reserve(data.size());

    std::unordered_map<int, size_t> left_label_counts;
    std::unordered_map<int, size_t> right_label_counts = count_labels(data, sorted_indexes);

    // Start the loop from [T_1|...T_n]
    float last_seen_feature = data[sorted_indexes[0]].first[feature_idx];
    left_label_counts[data[sorted_indexes[0]].second]++;
    right_label_counts[data[sorted_indexes[0]].second]--;

    // These indexes ensure that there is atleast 2 samples
    for (size_t i{1}; i < sorted_indexes.size(); i++) 
    {
        size_t current_idx = sorted_indexes[i];
        int current_label = data[current_idx].second;
        float current_feature = data[current_idx].first[feature_idx];

        // Check repeated threshold.
        if (current_feature != last_seen_feature) 
        {
            double threshold = (current_feature + last_seen_feature) / 2;

            // Calculate the impurity scores based on the updated label counts
            double left_score = calculate_node_score_from_label_counts(left_label_counts, i);
            double right_score = calculate_node_score_from_label_counts(right_label_counts, sorted_indexes.size() - i);
            double split_score = (left_score * (i) + right_score * (sorted_indexes.size() - i)) / data.size();
            
            // Call the constructor in place in the split_scores vector with emplace_back.
            split_scores.emplace_back(threshold, split_score);
            last_seen_feature = current_feature;

            // Print out if required.
            if (verbose){std::cout<<"Threshold: "<<threshold<<", Score: "<<split_score<<std::endl;}
        }
        // Update the label counts on both sides of the split
        left_label_counts[current_label]++;
        right_label_counts[current_label]--;
    }

    return split_scores;
}
std::pair<size_t, float> Splitter::find_best_split(const std::vector<std::pair<std::vector<float>, int>>& data, const bool verbose)
{
    std::vector<size_t> sorted_indexes(data.size());
    std::vector<std::pair<double, double>> splits_scores(data.size() - 1);
    size_t best_split_index;
    std::pair<double, double> best_split;
    std::vector<std::pair<double, double>> best_splits;
    best_splits.reserve(data[0].first.size());
    best_splits.clear();

    // Loop over all features in the data and find the best spilt for that feature.
    for (size_t feature_idx{0}; feature_idx < data[0].first.size(); feature_idx++)
    {
        splits_scores = calculate_split_scores(data, feature_idx);
        best_split_index = find_min_score_index(splits_scores);
        best_split = splits_scores[best_split_index];
        best_splits.push_back(best_split);
    }
    size_t best_feature = find_min_score_index(best_splits);
    std::pair<size_t, double> best_feature_threshold = std::make_pair(best_feature, best_splits[best_feature].first);
    if (verbose){std::cout<<"---------------\n"<<"Best Feature: "<<best_feature_threshold.first<<", Best Threshold: "
                    <<best_feature_threshold.second<<"\n---------------"<<std::endl;}
    return best_feature_threshold;
}
size_t Splitter::find_min_score_index(const std::vector<std::pair<double, double>>& vec)
{
    // A simple O(n) search for the index with the minimum score. 
    double min_val = vec[0].second;
    size_t min_index = 0;

    for (size_t i = 1; i < vec.size(); i++)
    {
        if (vec[i].second < min_val)
        {
            min_val = vec[i].second;
            min_index = i;
        }
    }
    return min_index;
}

std::unordered_map<int, std::size_t> Splitter::count_labels(const std::vector<std::pair<std::vector<float>, int>>& data, const std::vector<size_t> indexes) const
{
    // Counts the total number of labels an indexed part of the data set. 
    std::unordered_map<int, std::size_t> label_count_map;
    for (const auto& idx : indexes) {label_count_map[data[idx].second]++;}
    return label_count_map;
};