// #include <iostream>
// #include <algorithm>
// #include <cmath>
// #include <vector>
// #include <fstream>
// #include <sstream>
// #include "Treeindex.h"
// using namespace std;

// const int SZ = 100;
// DataVector::DataVector(int dimension)
// {
//     setDimension(dimension);
// }
// DataVector::DataVector(const std::vector<double>& values) {
//         v = values;
// }
// void DataVector::setDimension(int dimension)
// {
//     v.clear();
//     v.resize(dimension, 0.0);
// }

// DataVector::~DataVector()
// {
// }

// DataVector::DataVector(const DataVector &other)
// {
//     v = other.v;
// }

// DataVector &DataVector::operator=(const DataVector &other)
// {
//     if (this != &other)
//     {
//         v = other.v;
//     }
//     return *this;
// }

// DataVector DataVector::operator+(const DataVector &other)
// {
//     if (v.size() != other.v.size())
//     {
//         std::cerr << "Error: Vector dimensions are not equal for addition.\n";
//         exit(EXIT_FAILURE);
//     }

//     DataVector sum(v.size());
//     for (int i = 0; i < v.size(); i++)
//     {
//         sum.v[i] = v[i] + other.v[i];
//     }
//     return sum;
// }

// DataVector DataVector::operator-(const DataVector &other)
// {
//     if (v.size() != other.v.size())
//     {
//         std::cerr << "Error: Vector dimensions are not equal for subtraction.\n";
//         exit(EXIT_FAILURE);
//     }

//     DataVector diff(v.size());
//     for (int i = 0; i < v.size(); i++)
//     {
//         diff.v[i] = v[i] - other.v[i];
//     }
//     return diff;
// }

// double DataVector::operator*(const DataVector &other) const
// {
//     if (v.size() != other.v.size())
//     {
//         cerr << "Error: Vector dimensions are not equal for dot product.\n";
//         exit(EXIT_FAILURE);
//     }

//     double dotProduct = 0.0;
//     for (int i = 0; i < v.size(); i++)
//     {
//         dotProduct += v[i] * other.v[i];
//     }
//     return dotProduct;
// }

// DataVector &DataVector::operator=(const vector<double> &vec)
// {
//     v = vec;
//     return *this;
// }

// double DataVector::norm()
// {
//     return sqrt((*this) * (*this));
// }

// double DataVector::dist(const DataVector &other)
// {
//     DataVector diff = *this - other;
//     return diff.norm();
// }
// void DataVector::print()
// {
//     for (int i = 0; i < v.size(); i++)
//     {
//         cout << v[i] << " ";
//     }
//     cout << endl;
// }

// vector<DataVector> readData(const string &filepath)
// {
//     vector<DataVector> final; // Create a VectorDataset object to store the final dataset
//     ifstream file(filepath);  // Open the file for reading

//     // Check if the file is successfully opened
//     if (!file.is_open())
//     {
//         cerr << "Error: File not found\n";
//         return final; // Return an empty dataset if the file is not found
//     }

//     string line;
//     getline(file, line); // Read the first line (assuming it contains header information)

//     // Read each line of the file
//     while (getline(file, line))
//     {
//         istringstream iss(line);
//         vector<double> values;
//         double val;
//         char comma;

//         // Parse the line and extract values separated by commas
//         while (iss >> val)
//         {
//             values.push_back(val);
//             // Check for a comma after each value
//             if (iss >> comma && comma != ',')
//             {
//                 cerr << "Error: Unexpected character after value in line: " << line << endl;
//                 return final; // Return an empty dataset in case of unexpected characters
//             }
//         }

//         // Create a DataVector and populate it with the parsed values
//         DataVector temp;
//         temp = values;
//         DataVector dataVector(temp);

//         // Add the DataVector to the final dataset
//         final.push_back(dataVector);
//     }

//     file.close(); // Close the file after reading
//     return final; // Return the final dataset
// }

// // // DataVector class remains the same as before

// // struct Node {
// //     vector<DataVector> v;
// //     Node* left;
// //     Node* right;
// //     vector<double> direction; // New member for RPTree
// //     double threshold;         // New member for RPTree
// // };

// // class RPTreeIndex {
// //     Node* root;

// //     Node* buildTree(vector<DataVector>& points, int depth) {
// //         if (points.empty()) {
// //             return nullptr;
// //         }

// //         int k = points[0].v.size();
// //         int axis = depth % k;

// //         if (points.size() <= SZ) {
// //             Node* newnode = new Node;
// //             newnode->axis = axis;
// //             newnode->left = nullptr;
// //             newnode->right = nullptr;
// //             newnode->direction.resize(k);

// //             // Choose a random unit direction
// //             for (int i = 0; i < k; ++i) {
// //                 newnode->direction[i] = (rand() % 2000 - 1000) / 1000.0; // Random direction
// //             }

// //             newnode->threshold = 0.0; // Threshold initialization
// //             newnode->v = points;
// //             return newnode;
// //         }

// //         // Choose a random unit direction
// //         vector<double> direction(k);
// //         for (int i = 0; i < k; ++i) {
// //             direction[i] = (rand() % 2000 - 1000) / 1000.0; // Random direction
// //         }

// //         // Find the farthest point along the chosen direction
// //         double maxDistance = -1.0;
// //         DataVector farthestPoint;

// //         for (const auto& point : points) {
// //             double distance = point * direction;
// //             if (distance > maxDistance) {
// //                 maxDistance = distance;
// //                 farthestPoint = point;
// //             }
// //         }

// //         // Choose a random threshold value
// //         double delta = ((rand() % 2000) - 1000) / 1000.0;
// //         double threshold = farthestPoint * direction + delta * sqrt(k);

// //         // Partition the data based on the threshold
// //         vector<DataVector> leftPoints, rightPoints;
// //         for (const auto& point : points) {
// //             if (point * direction <= threshold) {
// //                 leftPoints.push_back(point);
// //             } else {
// //                 rightPoints.push_back(point);
// //             }
// //         }

// //         // Create a new node and recursively build left and right subtrees
// //         Node* newnode = new Node;
// //         newnode->axis = axis;
// //         newnode->left = buildTree(leftPoints, depth + 1);
// //         newnode->right = buildTree(rightPoints, depth + 1);
// //         newnode->direction = direction;
// //         newnode->threshold = threshold;

// //         return newnode;
// //     }
// //     vector<DataVector> search(DataVector &point, Node *node)
// //     {
// //         if (node == NULL)
// //         {
// //             return vector<DataVector>();
// //         }
// //         if (node->medianval == -1)
// //         {
// //             return node->v;
// //         }

// //         double compareval = point.v[node->axis];

// //         if (compareval <= node->medianval)
// //         {
// //             return search(point, node->left);
// //         }
// //         else
// //         {
// //             return search(point, node->right);
// //         }
// //     }
// //     RPTreeIndex() : root(nullptr) {}
// //     static RPTreeIndex *instance;
// //     public:
// //         static RPTreeIndex *GetInstance()
// //     {
// //         if (!instance)
// //         {
// //             instance = new RPTreeIndex();
// //         }
// //         return instance;
// //     }

// //     vector<DataVector> searchQuery(DataVector &point)
// //     {
// //          return search(point, root);
// //     }

// //     void makeTree(vector<DataVector>& points) {
// //         root = buildTree(points, 0);
// //     }

// //     // You can add a search method here similar to KDTreeIndex

// //     ~RPTreeIndex() {
// //         // Implement a destructor to delete the tree
// //     }
// // };
// // class DataVector {
// // public:
// //     vector<double> v;

// //     DataVector(int dimension) {
// //         setDimension(dimension);
// //     }

// //     void setDimension(int dimension) {
// //         v.clear();
// //         v.resize(dimension, 0.0);
// //     }

// //     ~DataVector() {}

// //     DataVector(const DataVector& other) {
// //         v = other.v;
// //     }

// //     DataVector& operator=(const DataVector& other) {
// //         if (this != &other) {
// //             v = other.v;
// //         }
// //         return *this;
// //     }

// //     DataVector operator+(const DataVector& other) {
// //         if (v.size() != other.v.size()) {
// //             cerr << "Error: Vector dimensions are not equal for addition.\n";
// //             exit(EXIT_FAILURE);
// //         }

// //         DataVector sum(v.size());
// //         for (int i = 0; i < v.size(); i++) {
// //             sum.v[i] = v[i] + other.v[i];
// //         }
// //         return sum;
// //     }

// //     DataVector operator-(const DataVector& other) {
// //         if (v.size() != other.v.size()) {
// //             cerr << "Error: Vector dimensions are not equal for subtraction.\n";
// //             exit(EXIT_FAILURE);
// //         }

// //         DataVector diff(v.size());
// //         for (int i = 0; i < v.size(); i++) {
// //             diff.v[i] = v[i] - other.v[i];
// //         }
// //         return diff;
// //     }

// //     DataVector& operator=(const vector<double>& vec) {
// //         v = vec;
// //         return *this;
// //     }

// //     double norm() {
// //         return sqrt((*this) * (*this));
// //     }

// //     double dist(const DataVector& other) {
// //         DataVector diff = *this - other;
// //         return diff.norm();
// //     }

// //     void print() {
// //         for (int i = 0; i < v.size(); i++) {
// //             cout << v[i] << " ";
// //         }
// //         cout << endl;
// //     }
// // };

// struct Node
// {
//     vector<DataVector> v;
//     Node *left;
//     Node *right;
//     vector<double> direction;
//     double threshold;
// };

// class RPTreeIndex
// {
//     Node *root;

//     Node *buildTree(vector<DataVector> &points, int depth)
//     {
//         if (points.empty())
//         {
//             return nullptr;
//         }

//         int k = points[0].v.size();
//         // cout<<"k: "<<k<<endl;
//         int axis = depth % k;
//         cout<<axis<<endl;
//         Node *newnode = new Node;
//         newnode->direction.resize(k);
//         for (int i = 0; i < k; i++)
//         {
//             newnode->direction[i] = (rand() % 2000 - 1000) / 1000.0; // Random direction
//         }

//         // Choose a random point from the dataset
//         int idx = rand() % points.size();
//         DataVector randomPoint = points[idx];

//         // Find the farthest point from the randomly chosen point
//         double maxDistance = 0.0;
//         DataVector farthestPoint;
//         for (const auto &point : points)
//         {
//             double distance = randomPoint.dist(point);
//             if (distance > maxDistance)
//             {
//                 maxDistance = distance;
//                 farthestPoint = point;
//             }
//         }

//         // Choose a random threshold value
//         double delta = (rand() % 2000 - 1000) / 1000.0;
//         newnode->threshold = maxDistance / sqrt(k) * delta;

//         // Split the dataset into two subsets
//         vector<DataVector> leftPoints, rightPoints;
//         for (const auto &point : points)
//         {
//             double distance = (point * DataVector(newnode->direction)) - newnode->threshold;
//             if (distance <= 0.0)
//             {
//                 leftPoints.push_back(point);
//             }
//             else
//             {
//                 rightPoints.push_back(point);
//             }
//         }

//         newnode->left = buildTree(leftPoints, depth + 1);
//         newnode->right = buildTree(rightPoints, depth + 1);

//         return newnode;
//     }

//     // Helper function for recursive search
//     void searchHelper(DataVector &point, Node *node, vector<DataVector> &result)
//     {
//         if (node == nullptr)
//         {
//             return;
//         }

//         // Calculate the distance from the point to the splitting hyperplane
//         double distance = (point * DataVector(node->direction)) - node->threshold;

//         if (distance <= 0.0)
//         {
//             // Recursively search the left subtree
//             searchHelper(point, node->left, result);
//         }
//         else
//         {
//             // Recursively search the right subtree
//             searchHelper(point, node->right, result);
//         }

//         // Check if the point is within the hypersphere defined by the splitting hyperplane
//         if (distance * distance <= node->threshold * node->threshold)
//         {
//             result.insert(result.end(), node->v.begin(), node->v.end());
//         }
//     }
//     static RPTreeIndex *instance;

// public:
//     RPTreeIndex() : root(nullptr) {}

//     void makeTree(vector<DataVector> &points)
//     {
        
//         root = buildTree(points, 0);
//         cout<<"jio"<<endl;
//     }

//     vector<DataVector> searchQuery(DataVector &point)
//     {
//         vector<DataVector> result;
//         searchHelper(point, root, result);
//         return result;
//     }
//     static RPTreeIndex *GetInstance()
//     {
//         if (!instance)
//         {
//             instance = new RPTreeIndex();
//         }
//         return instance;
//     }
//     ~RPTreeIndex()
//     {
//         // Implement a destructor to delete the tree
//     }
// };

// RPTreeIndex *RPTreeIndex::instance = nullptr;

// bool cmp(const pair<DataVector, double> &a, const pair<DataVector, double> &b)
// {
//     return a.second < b.second;
// }
// void knearestneighbor(vector<DataVector> &traindata, DataVector &testvector, int k)
// {
//     // Calculate distances between the test vector and all vectors in the training dataset
//     vector<pair<DataVector, double>> distances;
//     int n = traindata.size();
//     for (int i = 0; i < n; i++)
//     {
//         double distance = testvector.dist(traindata[i]);
//         distances.push_back(make_pair(traindata[i], distance));
//     }

//     // Sort the distances in ascending order
//     sort(distances.begin(), distances.end(), cmp);

//     // Create a dataset for the k-nearest neighbors
//     for (int i = 0; i < min(k, n); i++)
//     {
//         cout << "Vector " << i + 1 << ": ";
//         distances[i].first.print();
//     }
// }
// // The rest of your existing code for DataVector and main function remains unchanged

// int main()
// {
//     // Your existing main function code
//     cout << "Reading Data initiated" << endl;
//     vector<DataVector> myData = readData("fmnist-test.csv");
//     cout << "Reading data finished" << endl;
//     myData[0].print();
//     cout << myData.size() << endl;
    
//     RPTreeIndex::GetInstance()->makeTree(myData);

//     cout << "hello" << endl;
//     DataVector testvector;
//     // vector<double> v={0.0,0.0,0.0,2.0,0.0,1.0,1.0,0.0,0.0,0.0,0.0,57.0,67.0,73.0,76.0,76.0,83.0,62.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,1.0,1.0,0.0,0.0,13.0,79.0,128.0,201.0,162.0,161.0,173.0,192.0,172.0,181.0,184.0,108.0,30.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,102.0,139.0,142.0,103.0,115.0,162.0,154.0,165.0,153.0,139.0,129.0,150.0,138.0,171.0,161.0,26.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,106.0,124.0,108.0,103.0,106.0,93.0,100.0,180.0,156.0,147.0,138.0,85.0,157.0,114.0,124.0,154.0,157.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,2.0,0.0,29.0,134.0,101.0,113.0,108.0,97.0,116.0,81.0,146.0,183.0,164.0,111.0,146.0,131.0,122.0,132.0,145.0,169.0,93.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,65.0,131.0,105.0,101.0,108.0,100.0,104.0,97.0,74.0,206.0,174.0,115.0,150.0,108.0,119.0,146.0,152.0,162.0,141.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,108.0,123.0,112.0,106.0,98.0,100.0,101.0,111.0,72.0,136.0,132.0,112.0,115.0,109.0,142.0,150.0,160.0,162.0,195.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,135.0,122.0,119.0,112.0,83.0,93.0,97.0,106.0,115.0,91.0,109.0,83.0,109.0,125.0,165.0,140.0,193.0,160.0,176.0,6.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,23.0,135.0,132.0,149.0,104.0,78.0,96.0,97.0,103.0,108.0,108.0,115.0,84.0,114.0,149.0,158.0,147.0,209.0,160.0,178.0,52.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,57.0,124.0,131.0,160.0,103.0,96.0,101.0,109.0,109.0,111.0,108.0,114.0,106.0,113.0,156.0,163.0,156.0,196.0,167.0,174.0,85.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,86.0,116.0,126.0,160.0,132.0,102.0,96.0,104.0,107.0,98.0,93.0,123.0,116.0,112.0,149.0,160.0,181.0,186.0,162.0,162.0,123.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,112.0,114.0,112.0,167.0,146.0,100.0,100.0,101.0,107.0,96.0,100.0,126.0,103.0,120.0,141.0,158.0,167.0,187.0,147.0,148.0,170.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,124.0,118.0,101.0,197.0,89.0,101.0,100.0,96.0,108.0,103.0,108.0,122.0,107.0,127.0,139.0,150.0,119.0,196.0,145.0,142.0,179.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,131.0,115.0,97.0,198.0,47.0,108.0,96.0,96.0,106.0,119.0,102.0,120.0,103.0,123.0,140.0,150.0,81.0,206.0,146.0,135.0,194.0,0.0,0.0,0.0,0.0,0.0,0.0,4.0,136.0,118.0,98.0,193.0,21.0,109.0,96.0,106.0,102.0,129.0,100.0,119.0,102.0,118.0,141.0,153.0,45.0,216.0,148.0,139.0,205.0,12.0,0.0,0.0,0.0,0.0,0.0,24.0,137.0,117.0,101.0,187.0,25.0,113.0,92.0,112.0,94.0,120.0,105.0,127.0,97.0,115.0,142.0,150.0,19.0,213.0,148.0,131.0,204.0,36.0,0.0,0.0,0.0,0.0,0.0,40.0,141.0,109.0,117.0,158.0,12.0,124.0,90.0,116.0,96.0,117.0,113.0,136.0,94.0,111.0,147.0,163.0,31.0,191.0,146.0,134.0,206.0,58.0,0.0,0.0,0.0,0.0,0.0,39.0,129.0,102.0,147.0,119.0,0.0,120.0,90.0,119.0,101.0,116.0,106.0,127.0,102.0,114.0,146.0,180.0,20.0,146.0,159.0,129.0,204.0,70.0,0.0,0.0,0.0,0.0,0.0,58.0,126.0,111.0,162.0,101.0,21.0,132.0,89.0,123.0,108.0,106.0,102.0,126.0,111.0,116.0,141.0,178.0,50.0,112.0,169.0,138.0,164.0,84.0,0.0,0.0,0.0,0.0,0.0,108.0,134.0,134.0,185.0,84.0,73.0,123.0,87.0,122.0,111.0,102.0,106.0,128.0,114.0,109.0,134.0,174.0,97.0,98.0,160.0,147.0,175.0,135.0,0.0,0.0,0.0,0.0,0.0,97.0,142.0,169.0,198.0,37.0,84.0,107.0,97.0,122.0,112.0,109.0,112.0,126.0,102.0,96.0,131.0,172.0,128.0,51.0,254.0,168.0,164.0,111.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,12.0,46.0,2.0,119.0,102.0,109.0,123.0,96.0,116.0,122.0,132.0,106.0,106.0,129.0,151.0,184.0,26.0,20.0,8.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,13.0,137.0,101.0,114.0,100.0,106.0,134.0,135.0,129.0,104.0,111.0,123.0,151.0,194.0,74.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,3.0,0.0,73.0,132.0,101.0,104.0,102.0,140.0,108.0,108.0,131.0,106.0,119.0,113.0,142.0,167.0,135.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,112.0,118.0,107.0,104.0,139.0,109.0,97.0,123.0,138.0,107.0,127.0,120.0,136.0,161.0,159.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,3.0,0.0,142.0,148.0,112.0,105.0,101.0,83.0,125.0,123.0,143.0,104.0,115.0,100.0,126.0,168.0,178.0,7.0,0.0,2.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,2.0,0.0,9.0,126.0,184.0,200.0,167.0,163.0,171.0,150.0,167.0,156.0,174.0,197.0,182.0,162.0,61.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,30.0,72.0,95.0,109.0,111.0,111.0,106.0,101.0,71.0,12.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
//     testvector = myData[1];
//     vector<DataVector> smallset = RPTreeIndex::GetInstance()->searchQuery(testvector);
//     // cout << "bye" << endl;
//     // smallset[1].print();
//     cout<<"k"<<endl;
//     knearestneighbor(smallset, testvector, 3);
//     cout<<"b"<<endl;
//     return 0;
// }


#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include "Treeindex.h"

using namespace std;