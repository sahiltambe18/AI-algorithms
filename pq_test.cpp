#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct custom
{
    bool operator()(const pair<int, int> &a, const pair<int, int> &b)
    {
        // Compare based on the first element of the pair
        return a.first > b.first;
    }
};

int main() {

    priority_queue<pair<int,int>,vector<pair<int,int>> , custom> pq;
    vector<bool> visited(8,false);
    pq.push({5,6});
    pq.push({10,8});
    pq.push({1,7});
    pq.push({3,6});

    while (pq.empty()!=1)
    {
        cout<<pq.top().first<<" "<<pq.top().second<<endl;
        pq.pop();
    }
    vector<vector<int>> g(5,vector<int>( 5 , 999));
    for(auto i : g){
        for(auto j : i){
            cout<<j<<" ";
        }cout<<endl;
    }
    

    return 0;
}