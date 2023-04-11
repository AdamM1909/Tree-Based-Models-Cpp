/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-07 16:31:58
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-11 15:11:25
 * @ Description: Implements fucntionality of the "Data_Loader" class.
 */

#include "Data_Loader.h"

Data_Loader::Data_Loader(const std::string& filename, bool first_row_as_labels, float train_ratio)
{
    load_data(filename, first_row_as_labels);
    n_labels = calc_n_labels();
    n_features = calc_n_features();
    random_train_split(train_ratio);
}
void Data_Loader::print_data_point(int index) const
{
    if (index < 0 || index >= data_.size()) {
        std::cout<<"Index out of bounds."<<std::endl;
    }
    else {
        std::cout<<"Features: [";
        for (const auto& feature : data_[index].first) {std::cout<<feature<<", ";}
        std::cout<<"] Label: "<<data_[index].second<<std::endl;
    }
}
void Data_Loader::load_data(const std::string& filename, bool first_row_as_labels) 
    {
        // Load file into an input stream.
        std::ifstream file_stream(filename);
        if (!file_stream) 
        {
            std::cerr<<"Error: could not open file: "<<filename<<std::endl;
            return;
        }
        // Clear memory to be safe.
        data_.clear();
        // Read in.
        std::string line;
        while (std::getline(file_stream, line)) 
        {
            // Skip first row if necessary. 
            if (first_row_as_labels) 
            {
                first_row_as_labels = false;
                continue;
            }
            std::vector<float> row;
            std::stringstream line_stream(line);
            std::string field;
            // Push all features and targets (fields) into "row" as floats.
            while (std::getline(line_stream, field, ',')) 
            {
                try {
                float float_field = std::stof(field);
                row.push_back(float_field);
                } catch (const std::exception& error) {
                std::cerr<<"Error: could not convert entry"<<field<<" to float. "
                    <<"Ensure all features and targets are numerical. Full error message: "
                    <<error.what()<<std::endl;
                return;
                }  
            }
            // Store in a STL pair template data structure.
            float label = row.back();
            row.pop_back();// Remove target from row
            data_.push_back(std::make_pair(row, label));
        }
    }
void Data_Loader::random_train_split(float train_ratio) 
    {
        // Get a psudorandom shuffle with a time based seed. 
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(data_.begin(), data_.end(), std::default_random_engine(seed));
        int num_train = static_cast<int>(data_.size() * train_ratio);
        // Clear to be safe.
        train_data_.clear();
        test_data_.clear();
        // Reserve for faster allocation.
        train_data_.reserve(num_train);
        test_data_.reserve(data_.size()-num_train);
        // User vector class fucntion "instert" to allocate
        train_data_.insert(train_data_.begin(), data_.begin(), data_.begin() + num_train);
        test_data_.insert(test_data_.begin(), data_.begin() + num_train, data_.end());
    }
int Data_Loader::calc_n_labels()
    {
        // Set to count disticnt items.
        std::set<float> unique_labels;
        for (auto& pair : data_) {unique_labels.insert(pair.second);}
        return unique_labels.size();
    }
int Data_Loader::calc_n_features(){return data_[0].first.size();}
const std::vector<std::pair<std::vector<float>, float>>& Data_Loader::train_data() const {return train_data_;}
const std::vector<std::pair<std::vector<float>, float>>& Data_Loader::bootstrapped_train_data() 
{
    create_bootstrapped_train_data();
    return bootstrapped_train_data_;
}
const std::vector<std::pair<std::vector<float>, float>>& Data_Loader::test_data() const {return test_data_;}
const std::vector<std::pair<std::vector<float>, float>>& Data_Loader::data() const {return data_;}
void Data_Loader::create_bootstrapped_train_data() 
{
    // Get a psudorandom shuffle with a time based seed. 
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    int num = train_data_.size();
    std::default_random_engine gen(seed);
    std::uniform_int_distribution<> uniform_idx(0, num - 1);
    // Create the boostrap dataset and assign.
    bootstrapped_train_data_.clear();
    bootstrapped_train_data_.reserve(num);
    for (size_t i{0}; i < num; ++i) 
    {
        size_t idx = uniform_idx(gen);
        bootstrapped_train_data_.push_back(train_data_[idx]);
    }
}
