#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include <set>
#include <chrono>
using namespace std;

struct Claim {
    int id, x, y, w, h;
};

vector<Claim> claims;


Claim parse_line(string line) {
    Claim cl;
    char ignore;
    
    stringstream ss(line);
    ss >> ignore >> cl.id >> ignore >> cl.x >> ignore >> cl.y >> ignore >> cl.w >> ignore >> cl.h;

    return cl;
}

Claim get_overlap(Claim cl1, Claim cl2) {
    Claim cl;
    cl.id = 0;
    cl.x = max(cl1.x, cl2.x);
    cl.w = min(cl1.x + cl1.w, cl2.x + cl2.w) - cl.x;
    cl.y = max(cl1.y, cl2.y);
    cl.h = min(cl1.y + cl1.h, cl2.y + cl2.h) - cl.y;
    return cl;
}

Claim overlaping_claims(Claim cl1, Claim cl2) {
    Claim ol_claim;
    ol_claim.id = -1;
    if (cl1.x <= cl2.x && cl2.x < cl1.x + cl1.w && cl1.y <= cl2.y && cl2.y < cl1.y + cl1.h) {
        ol_claim = get_overlap(cl1, cl2);
    } else if (cl1.x <= cl2.x && cl2.x < cl1.x + cl1.w && cl2.y <= cl1.y && cl1.y < cl2.y + cl2.h) {
        ol_claim = get_overlap(cl1, cl2);
    } else if (cl2.x <= cl1.x && cl1.x < cl2.x + cl2.w && cl1.y <= cl2.y && cl2.y < cl1.y + cl1.h) {
        ol_claim = get_overlap(cl1, cl2);
    } else if (cl2.x <= cl1.x && cl1.x < cl2.x + cl2.w && cl2.y <= cl1.y && cl1.y < cl2.y + cl2.h) {
        ol_claim = get_overlap(cl1, cl2);
    }
    return ol_claim;
}

void setup() {
    ifstream file("input.txt");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        Claim cl = parse_line(line);
        claims.push_back(cl);
    }
}

void solve() {
    for (Claim cl1 : claims) {
        bool flag = true;
        for (Claim cl2 : claims) {
            if (cl1.id != cl2.id) {
                Claim ol_claim = overlaping_claims(cl1, cl2); 
                if (ol_claim.id != -1) {
                    flag = false;
                    break;
                }
            }
        }
        if (flag) {
            cout << cl1.id << endl;
            return; 
        }
    }
    int result = doubled_claims.size();
    cout << result << endl;
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