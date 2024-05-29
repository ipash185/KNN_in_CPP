#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include "DataVector.h"
#include "VectorDataset.h"

//append in file
#include <fstream>

using namespace std;
using namespace chrono;

int main() {

    string filename = "";
    cout<<"Enter only the test filename (location) in a line:\n";
    getline(cin, filename);
    string trainfilename = "";
    cout<<"Enter only the train filename (location) in a line:\n";
    getline(cin, trainfilename);
    int k = 5;
    // cout<<"Enter the value of k:\n";
    // cin>>k;
    VectorDataset dataset;
    dataset.readCSV(filename);
    VectorDataset train;
    train.readCSV(trainfilename);

    auto start = high_resolution_clock::now();
    string outfile;
    cout<<"Enter only the output filename (location) in a line:\n";
    getline(cin, outfile);
    ofstream file(outfile, ios::app);
    if (file.is_open()) {
    } else {
        cout << "Unable to open file" << endl;
    }

    for (int i = 0; i < 100; i++) {
        file<<"index of vector: "<<i<<endl;
        auto start2 = high_resolution_clock::now();
        VectorDataset d = dataset.knearestneighbor(i, k, train);
        auto stop2 = high_resolution_clock::now();
        auto duration2 = duration_cast<milliseconds>(stop2 - start2);
        cout << "Neighbour of vector: " << i << endl;
        d.printDataset();
        file << "Time taken to calculate nearest neighbors: " << duration2.count() << " milliseconds\n\n";
    }
    file.close();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    
    cout << "\nTotal time taken to calculate nearest neighbors: " << duration.count() << " milliseconds\n\n";


    return 0;
}