#include <iostream>
#include <fstream>
#include <unordered_set>
#include <chrono>
#include <algorithm>
using namespace std;

pair<int, int> counter {0, 0};

void setup() {
    ifstream file("input.txt");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        unordered_set<char> unique(line.begin(), line.end());
        bool two = true, three = true;


        for (char ch : unique) {
            int c = count(line.begin(), line.end(), ch);
            if (c == 2 && two) {
                two = false;
                counter.first += 1;
            } else if (c == 3 && three) {
                three = false;
                counter.second += 1;
            }
        }
    }

    int checksum = counter.first * counter.second;
    cout << checksum << endl;
}


int main() {
    auto start_time = std::chrono::high_resolution_clock::now();

    setup();
    
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    cout << "Clock time: " << duration.count() / (double)1000000 << " s" << endl;

    return 0;
}