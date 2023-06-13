# Tree-Based-Models-Cpp

This repo implements tree-based classification algorithms using an Object-Oriented Programming
OOP approach in C++. The program loads and processes classification data sets, creates random
training and test data splits, and constructs decision trees using either the Gini or Entropy impurity
measures. Further, it aggregates predictions of multiple decision trees as part of a random forest.
The program evaluates the tree based models using the test data and outputs their accuracy and a
confusion matrix to the user. Abstraction hides the statistical algorithms used to create and predict
with these models, leaving a simple interface for a user to interact with.
