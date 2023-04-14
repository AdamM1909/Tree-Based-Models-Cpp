/**
 * @ Author: Adam Myers
 * @ Create Time: 2023-04-07 16:31:58
 * @ Modified by: Adam Myers
 * @ Modified time: 2023-04-13 19:32:58
 * @ Description: Implements fucntionality of the "Data_Loader" class.
 */

#include "Data_Loader.h"
#include "unordered_map"

Data_Loader::Data_Loader(const std::string& filename, const bool first_row_as_labels, const float train_ratio)
{
    load_data(filename, first_row_as_labels);
    random_train_split(train_ratio);
}
void Data_Loader::print_data_point(const int index) const
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
    std::unordered_map<std::string, float> string_label_to_int_map;
    int next_int_label = 0; 
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
        // Try push all features and targets (fields) into "row" as floats.
        while (std::getline(line_stream, field, ',')) 
        {
            try {
                float float_field = std::stof(field);
                row.push_back(float_field);
            } catch (const std::invalid_argument& error) {
                // If the last field is a string, convert it to an integer label else its a string feature so output an error.
                if (!line_stream.good()) 
                {
                    if (string_label_to_int_map.count(field)) {{};} 
                    else {
                        string_label_to_int_map[field] = next_int_label;
                        std::cout << "String label "<<field<<" corresponds to numerical label: "<<next_int_label<<std::endl;
                        next_int_label++;
                    }
                    // Now this can be pushed into the row vector. 
                    row.push_back(string_label_to_int_map[field]);
                } else { 
                    std::cerr<<"Cannot load data. Check all features are numerical. Error: "<<field<<" cannot be converted to a float."<<std::endl;
                    return;
                }
            }
         
        }
        // Store in a STL pair template data structure.
        int label = static_cast<int>(row.back());
        row.pop_back();// Remove target from row
        data_.push_back(std::make_pair(row, label)); 
    }

    std::cout<<"---------------"<<std::endl;
    std::cout<<"Number of entries loaded: "<<data_.size()<<std::endl;

    std::set<float> unique_labels;
    for (auto& pair : data_) {unique_labels.insert(pair.second);}
    
    n_labels_ = unique_labels.size();
    n_features_ = data_[0].first.size();
    std::cout<<"Number of labels: "<<n_labels_<<std::endl;
    std::cout<<"Number of features: "<<n_features_<<std::endl;
    std::cout<<"---------------"<<std::endl;
}
void Data_Loader::random_train_split(const float train_ratio) 
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
        std::cout<<"The train data set has "<<train_data_.size()<<" entries."<<"\n";
        std::cout<<"The test data set has "<<test_data_.size()<<" entries."<<std::endl;
    }
int Data_Loader::n_labels(){return n_labels_;}
int Data_Loader::n_features(){return  n_features_;}
const std::vector<std::pair<std::vector<float>, int>>& Data_Loader::train_data() const {return train_data_;}
const std::vector<std::pair<std::vector<float>, int>>& Data_Loader::bootstrapped_train_data() 
{
    create_bootstrapped_train_data();
    return bootstrapped_train_data_;
}
const std::vector<std::pair<std::vector<float>, int>>& Data_Loader::test_data() const {return test_data_;}
const std::vector<std::pair<std::vector<float>, int>>& Data_Loader::data() const {return data_;}
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
