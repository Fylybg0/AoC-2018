#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <chrono>
using namespace std;

int nums_size;
vector<int> nums;
unordered_set<int> freqs = {0};

void setup() {
    ifstream file("input.txt");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        int num = stoi(line);
        nums.push_back(num);
    }
    nums_size = nums.size();
}

void solve() {
    int freq = 0;
    int idx = 0;
    while (freqs.insert(freq += nums[idx]).second) {
        idx = (idx + 1) % nums_size;
    } 

    cout << freq << endl;
}

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();

    setup();
    solve();

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    cout << "Clock time: " << duration.count() / (double)1000000 << " s" << endl;


    return 0;
}