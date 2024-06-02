#include <iostream>
#include <string>
#include <fstream>
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
    solve();
    return 0;
}