#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
using namespace std;

int sum = 0;

void solve () {
    ifstream file("input.txt");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        int num = stoi(line);
        sum += num;
    }

    cout << sum << endl;
}

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();

    solve();

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    cout << "Clock time: " << duration.count() / (double)1000000 << " s" << endl;


    return 0;
}