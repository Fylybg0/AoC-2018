#include <iostream>
#include <fstream>
#include <unordered_set>
#include <chrono>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

vector<string> ids;

bool is_correct(string id1, string id2) {
    int differs = 0;
    for (int i = 0; i < id1.size(); i++) if (id1[i] != id2[i]) differs += 1;
    return differs == 1;
} 

void setup() {
    ifstream file("input.txt");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        ids.push_back(line);
    }
}

void solve() {
    for (int i = 0; i < ids.size(); i++) {
        for (int j = 0; j < ids.size(); j++) {
            if (i != j && is_correct(ids[i], ids[j])) {
                for (int x = 0; x < ids[i].size(); x++) if (ids[i][x] == ids[j][x]) cout << ids[i][x];
                cout << endl;
                return;
            }
        }
    }
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