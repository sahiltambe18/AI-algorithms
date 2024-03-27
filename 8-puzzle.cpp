#include<iostream>
#include<vector>
#include<set>
#include<unordered_map>
using namespace std;

vector<vector<int>> puzzle = {
    {1,6,8},
    {7,5,2},
    {3,4,0}
};

vector<vector<int>> finalState = {
    {1,2,3},
    {4,5,6},
    {7,8,0} // consider 0 as empty tile
};

set<vector<vector<int>>> st;
unordered_map<int, vector<vector<vector<int>>>> mp;

int fscore(const vector<vector<int>>& currState) {
    int h = 0;
    for(size_t i = 0; i < currState.size(); i++) {
        for(size_t j = 0; j < currState[0].size(); j++) {
            if(currState[i][j] != finalState[i][j]) {
                h++;
            }
        }
    }
    return h;
}

void solve(vector<vector<int>>& currState, int g, int x, int y) {
    if(st.find(currState) != st.end()) {
        return;
    }
    st.insert(currState);
    mp[g].push_back(currState) ;

    int h = fscore(currState);
    if(h == 0) {
        return;
    }

    // Try moving up
    if(x - 1 >= 0) {
        swap(currState[x][y], currState[x - 1][y]);
        solve(currState, g + 1, x - 1, y);
        swap(currState[x][y], currState[x - 1][y]); // Backtrack
    }

    // Try moving down
    if(x + 1 < currState.size()) {
        swap(currState[x][y], currState[x + 1][y]);
        solve(currState, g + 1, x + 1, y);
        swap(currState[x][y], currState[x + 1][y]); // Backtrack
    }

    // Try moving left
    if(y - 1 >= 0) {
        swap(currState[x][y], currState[x][y - 1]);
        solve(currState, g + 1, x, y - 1);
        swap(currState[x][y], currState[x][y - 1]); // Backtrack
    }

    // Try moving right
    if(y + 1 < currState[0].size()) {
        swap(currState[x][y], currState[x][y + 1]);
        solve(currState, g + 1, x, y + 1);
        swap(currState[x][y], currState[x][y + 1]); // Backtrack
    }
}

int main() {
    solve(puzzle, 0, 2, 2);
    for(auto& kv : mp) {
        cout << "Steps: " << kv.first << endl;
        for(auto& v : kv.second) {
            for(auto& val : v) {
                for(auto& vv : val) {
                    cout<<vv<<" ";
                }cout<<endl;
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}