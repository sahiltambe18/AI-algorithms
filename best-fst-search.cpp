#include <iostream>
#include <queue>
#include <utility>
#include <vector>
// #define infi 999
using namespace std;

int infi = 999;

// int g[8][8] = {
//     {0, 11, 14, 7, infi, infi, infi, infi},
//     {11, 0, infi, infi, 15, infi, infi, infi},
//     {14, infi, 0, infi, 8, 10, infi, infi},
//     {7, infi, infi, 0, infi, 25, infi, infi},
//     {infi, 15, 8, infi, 0, infi, infi, 9},
//     {infi, infi, infi, 25, infi, 0, 20, infi},
//     {infi, infi, infi, infi, infi, 20, 0, 10},
//     {infi, infi, infi, infi, 9, infi, 10, 0}};

//int h[] = {40, 32, 25, 35, 19, 17, 0, 10};

struct custom
{
    bool operator()(const pair<int, int> &a, const pair<int, int> &b)
    {
        // Compare based on the first element of the pair
        return a.first > b.first;
    }
};

int main()
{

    // undirected graph 0th node as starting vertex

    int v;
    cout<<"enter no of vertices : "<<endl;
    cin>>v;

    vector<vector<int>> g(v,vector<int>( v , infi));
    vector<int> h(v,0);
    while (true)
    {
        int s , d , c;
        cout<<"enter -1 -1 to stop adding edges\n";
        cout<<"enter src and dest : \n";
        cin>>s>>d;
        if(s==-1 && d==-1)  break;
        cout<<"enter cost from "<<s<<"->"<<d<<endl;
        cin>>c;
        g[s][d] = c;
        g[d][s] = c;
    }

    for (int i = 0; i < v; i++)
    {
        g[i][i] = 0;
        int hu ;
        cout<<"enter heuristic value of vertex "<<i<<endl;
        cin>>hu;
        h[i] = hu;
    }
    
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, custom> pq;

    vector<bool> visited(v, false);

    int cost = 0, target ;
    cout<<"enter target vertex : \n";
    cin>>target;

    vector<int> path;

    // starting node
    pq.push({h[0], 0});
    // pq.push({40,0});

    int ele = pq.top().second;

    while (!pq.empty())
    {

        int prev = ele;

        ele = pq.top().second;
        pq.pop();

        if (!visited[ele])
        {
            visited[ele] = true;
            for (int i = 0; i < 8; i++)
            {
                if (g[ele][i] != infi)
                {
                    pq.push({h[i], i});
                }
            }

            cost += g[prev][ele];

            path.push_back(ele);
        }

        if (ele == target)
        {
            break;
        }
    }

    cout << "cost is : " << cost << endl;
    for (auto i : path)
    {
        cout << i << " ";
    }

    return 0;
}