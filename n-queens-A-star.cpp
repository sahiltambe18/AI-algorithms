#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

struct State {
    vector<int> queens; 
    int cost =0;           
};

struct CompareState {
    bool operator()(const State& s1, const State& s2) {
        return s1.cost > s2.cost; 
    }
};


int heuristic(const vector<int>& queens) {
    int conflicts = 0;
    int n = queens.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
    
            if (queens[i] == queens[j] || abs(queens[i] - queens[j]) == j - i)
                conflicts++;
        }
    }
    return conflicts;
}

// Print the board
void printBoard(const vector<int>& queens) {
    int n = queens.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (queens[j] == i)
                cout << "* ";
            else
                cout << "_ ";
        }
        cout << endl;
    }
    cout << endl;
}

// A* iteratively 
bool solve(int N) {
    //const int N = 4; 
    State initialState;
    //initialState.cost = 0;
    priority_queue<State, vector<State>, CompareState> pq;
    pq.push(initialState);
    
    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();
        if (curr.queens.size() == N) {
            cout << "Solution:" << endl;
            printBoard(curr.queens);
            return true;
        }
        
        int nextColumn = curr.queens.size();
        for (int row = 0; row < N; ++row) {
            bool valid = true;
            // Check 
            
            
                State child = curr;
                child.queens.push_back(row); 
                // child.cost = curr.cost + 1;
                child.cost = heuristic(child.queens); 
                cout<<child.cost<<endl;
                pq.push(child);
            
        }
        //printBoard(curr.queens);
    }
    
    // error
    cout << "error hai bhaii" << endl;
    return false;
}

int main() {
    cout<<"enter the board size"<<endl;
    int N ;
    cin>>N;
    solve(N);
    return 0;
}
