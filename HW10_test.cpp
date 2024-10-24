#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

unordered_map<char, char> umap = {{'R', '/'},
                                  {'F', '\\'},
                                  {'C', '_'}};

int main() {
    int n; string s;
    while(cin >> n and n > 0) {
        for(int k=1; k<=n; k++) {
            int cnt = 0;
            vector<pair<int, char>> v;
            
            cin >> s;
            for(const auto& x: s) {
                if(x == 'F') cnt--;
                v.emplace_back(cnt, umap[x]);
                if(x == 'R') cnt++;
            }
            
            int maxY = max_element(v.begin(), v.end())->first;
            int minY = min_element(v.begin(), v.end())->first;
            
            cout << "Case #" << k << ":" << endl;
            for(int i=maxY; i>=minY; i--) {
                cout << "| ";
                for(auto [y, c]: v) {
                    cout << ((i == y)? c: ' ');
                }
                cout << endl;
            }
            cout << '+' << string(v.size() + 2, '-') << '\n' << endl;
        }
    }

    return 0;
} 