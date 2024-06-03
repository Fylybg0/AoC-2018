#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;

string line;

void setup() {
    ifstream file("input.txt");
    if (!file.is_open()) return;

    getline(file, line);
}

bool is_upper(char ch1, char ch2) {
    return (ch1 == toupper(ch2) && tolower(ch1) == ch2);
}

void solve() {
    int i = 0, j = 1;

    while (j < line.length()) {
        if (is_upper(line[i], line[j]) || is_upper(line[j], line[i])) {
            line.erase(i, j-i+1);
            if (i != 0) {
                j = i;
                i--;
            }
        } else {
            i++, j++;
        }
    }   
    cout << line.length() << endl;
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