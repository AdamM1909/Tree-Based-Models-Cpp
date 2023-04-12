#include <vector>
#include <iostream>

class Node {
public:
    virtual ~Node() {}
    virtual float predict(const std::vector<float>& features) const = 0;
    
    friend std::ostream& operator<<(std::ostream& os, const Node& node) {
        node.print(os);
        return os;
    }

    int get_depth() const {
        return depth_;
    }

    void set_depth(int depth) {
        depth_ = depth;
    }
    
protected:
    virtual void print(std::ostream& os) const = 0;
    int depth_;
};

class InternalNode : public Node {
public:
    InternalNode(float threshold, int feature_index, Node* left_child, Node* right_child)
            : threshold_(threshold), feature_index_(feature_index), left_child_(left_child), right_child_(right_child) {}

    float predict(const std::vector<float>& features) const override {
        if (features[feature_index_] < threshold_) {
            return left_child_->predict(features);
        } else {
            return right_child_->predict(features);
        }
    }
    
protected:
    void print(std::ostream& os) const override {
        os << "Internal node (depth=" << depth_ << "): feature_index=" << feature_index_ << ", threshold=" << threshold_ << "\n";
        os << "    " << *(left_child_) << "\n";
        os << "    " << *(right_child_);
    }

private:
    float threshold_;
    int feature_index_;
    Node* left_child_;
    Node* right_child_;
};

class LeafNode : public Node {
public:
    LeafNode(float value) : value_(value) {}

    float predict(const std::vector<float>& features) const override {
        return value_;
    }
    
protected:
    void print(std::ostream& os) const override {
        os << "Leaf node (depth=" << depth_ << "): value=" << value_;
    }

private:
    float value_;
};

int main() {
    Node* root = new InternalNode(2.5, 0,
    new InternalNode(1.5, 1, new LeafNode(1.0), new LeafNode(2.0)),
    new InternalNode(3.5, 1, new LeafNode(3.0), new LeafNode(4.0)));
root->set_depth(0);
std::cout<<*(root)<<std::endl;
}