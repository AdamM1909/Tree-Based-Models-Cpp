/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-07 16:28:47
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-11 14:59:52
 * @ Description: Header file for the Data_Loader class. 
 * 
 * Data is expected to have numerical features [x_n, ..., x_n] and have a numerical categorical label y.
 * This includes one-hot encoded categorical features. 
 * 
 * The data file provide is expected to be a comma seperated file with each row of the form: 
 * x_1,...,x_n , y
 * 
 * The user can specify if the file has a header row and what proportion of the data should be used
 * as a training data. The remaining data will be assigned to a test set. This fucntion also provides
 * fucntionality to create a random boostrapped training set of the same size as the train set. This
 * boostrapped training set includes repeat data points.
 */

#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <set>

class Data_Loader 
{
public:
    Data_Loader(const std::string& filename, bool first_row_as_labels, float train_ratio);
    void print_data_point(int index) const;
    const std::vector<std::pair<std::vector<float>, float>>& train_data() const;
    const std::vector<std::pair<std::vector<float>, float>>& bootstrapped_train_data();
    const std::vector<std::pair<std::vector<float>, float>>& test_data() const;
    const std::vector<std::pair<std::vector<float>, float>>& data() const;
    int n_labels;
    int n_features;
private:
    std::vector<std::pair<std::vector<float>, float>> data_; 
    std::vector<std::pair<std::vector<float>, float>> train_data_;
    std::vector<std::pair<std::vector<float>, float>> bootstrapped_train_data_;
    std::vector<std::pair<std::vector<float>, float>> test_data_;
    int calc_n_labels();
    int calc_n_features();
    void load_data(const std::string& filename, bool first_row_as_labels);
    void random_train_split(float train_ratio);
    void create_bootstrapped_train_data();
};
#endif