#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

struct state
{
    vector<vector<int>> puzzle;
    int cost, level , h;
};

vector<vector<int>> puzzle = {
    {2, 8, 3},
    {1, 6, 4},
    {7, 0, 5}};

vector<vector<int>> finalState = {
    {1, 2, 3},
    {8, 0, 4},
    {7, 6, 5} // consider 0 as empty tile
};

int fscore(const vector<vector<int>> &currState)
{
    int h = 0;
    for (int i = 0; i < currState.size(); i++)
    {
        for (int j = 0; j < currState[0].size(); j++)
        {
            if (currState[i][j] != finalState[i][j])
            {
                h++;
            }
        }
    }
    return h;
}

state CalculatFscore(state temp)
{
    int cost = fscore(temp.puzzle);
    temp.level++;
    temp.h = cost;
    temp.cost = cost==0 ? 0 : cost + temp.level;
    return temp;
}

struct CompareState
{
    bool operator()(const state &s1, const state &s2)
    {
        if (s1.cost == s2.cost)
        {
            return s1.level > s2.level;
        }
        return s1.cost > s2.cost;
    }
};

vector<int> locateZero(state curr)
{
    vector<int> v;
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            // cout << "x: " << x << ", y: " << y << " [x][y]= "<< curr.puzzle[x][y]<< endl;

            if (curr.puzzle[x][y] == 0)
            {
                v.push_back(x);
                v.push_back(y);
                return v;
            }
        }
    }
    return {0, 0};
}

void display(state curr)
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            cout << curr.puzzle[x][y] << " ";
        }
        cout << endl;
    }

    cout << "h : " << curr.h << endl;
    cout << "level : " << curr.level << endl;
    cout << "cost : " << curr.cost << endl;
    cout<< endl;
}

void solve()
{
    state initial;
    set<vector<vector<int>>> st;
    initial.puzzle = puzzle;
    initial.cost = fscore(initial.puzzle);
    initial.h = fscore(initial.puzzle);
    initial.level = 0;

    priority_queue<state, vector<state>, CompareState> pq;
    pq.push(initial);

    while (!pq.empty())
    {
        state curr = pq.top();

        display(curr);
        if (curr.cost == 0)
        {
            cout << "done" << endl;
            return;
            // break;
        }
        pq.pop();

        // find pos of empty space
        vector<int> pos = locateZero(curr);
        int x = pos[0];
        int y = pos[1];

        // move empty space up
        if (x > 0)
        {
            state temp = curr; // temp copy
            int val = temp.puzzle[x - 1][y];
            temp.puzzle[x - 1][y] = 0;
            temp.puzzle[x][y] = val;
            temp = CalculatFscore(temp);
            if (st.find(temp.puzzle) == st.end())
            {
                pq.push(temp);
            }
            // cout << "x: " << x << ", y: " << y << endl;
        }

        if (x < 2)
        {
            state temp = curr;
            int val = temp.puzzle[x + 1][y];
            temp.puzzle[x + 1][y] = 0;
            temp.puzzle[x][y] = val;

            temp = CalculatFscore(temp);
            if (st.find(temp.puzzle) == st.end())
            {
                pq.push(temp);
            }
        }

        if (y > 0)
        {
            state temp = curr;
            int val = temp.puzzle[x][y - 1];
            temp.puzzle[x][y - 1] = 0;
            temp.puzzle[x][y] = val;

            temp = CalculatFscore(temp);
            if (st.find(temp.puzzle) == st.end())
            {
                pq.push(temp);
            }
        }

        if (y < 2)
        {
            state temp = curr;
            int val = temp.puzzle[x][y + 1];
            temp.puzzle[x][y + 1] = 0;
            temp.puzzle[x][y] = val;

            temp = CalculatFscore(temp);
            if (st.find(temp.puzzle) == st.end())
            {
                pq.push(temp);
            }
        }
    }
    cout << "succeeded";
}

int main()
{

    cout<<"give positions for puzzle"<<endl;
    for (int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++){
            cout<< "enter the value : "<<endl;
            cin>> puzzle[i][j];
        }
    }
    
    cout<<"give positions for final State"<<endl;
    for (int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++){
            cout<< "enter the value : "<<endl;
            cin>> finalState[i][j];
        }
    }

    solve();

    //cout << fscore(puzzle);
    return 0;
}


/*

PS E:\code\AI> g++ .\8-puzzle.cpp 
PS E:\code\AI> ./a.exe
give positions for puzzle
enter the value :
2
enter the value :
8
enter the value :
3
enter the value :
1
enter the value :
6
enter the value :
4
enter the value :
7
enter the value :
0
enter the value :
5
give positions for final State
enter the value :
1
enter the value :
2
enter the value :
3
enter the value :
8
enter the value :
0
enter the value :
4
enter the value :
7
enter the value :
6
enter the value :
5
2 8 3
1 6 4
7 0 5
h : 5
level : 0
cost : 5

2 8 3
1 0 4
7 6 5
h : 3
level : 1
cost : 4

2 0 3
1 8 4
7 6 5 
h : 4
level : 2
cost : 6

2 8 3
0 1 4
7 6 5
h : 4
level : 2
cost : 6

2 8 3
1 0 4
7 6 5
h : 3
level : 3
cost : 6

0 2 3 
1 8 4
7 6 5
h : 3
level : 3
cost : 6

2 8 3
1 0 4
7 6 5
h : 3
level : 3
cost : 6

1 2 3
0 8 4
7 6 5
h : 2
level : 4
cost : 6

1 2 3
8 0 4
7 6 5
h : 0
level : 5
cost : 0

done
PS E:\code\AI> 
*/