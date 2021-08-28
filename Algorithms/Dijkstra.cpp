#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
const int INF = 1 << 30;
int n;

vector <pair <int,int> > adj[MAXN];
int d[MAXN], v[MAXN];
priority_queue <pair<int,int>, vector <pair<int,int> >
    , greater<pair<int,int> > > q;

void dijkstra(int* d, int src){
    for(int i = 1; i <= n; i++)
        v[i] = 0;
    q = priority_queue <pair<int,int>, vector <pair<int,int> >
    , greater<pair<int,int> > >();
    q.push({0,src});
    while(!q.empty()){
        int node = q.top().second;
        int dist = q.top().first;
        q.pop();
        if(!v[node]){
            d[node] = dist;
            v[node] = 1;
            for(pair <int,int> x : adj[node])
                q.push({d[node] + x.second, x.first});
        }
    }
}

int main(){
    
    n = 5;
    adj[1].emplace_back(2,5);
    adj[1].emplace_back(5,2);
    adj[2].emplace_back(1,1);
    adj[2].emplace_back(3,2);
    adj[3].emplace_back(4,5);
    adj[3].emplace_back(1,6);
    adj[4].emplace_back(1,3);
    adj[4].emplace_back(3,2);
    adj[5].emplace_back(2,5);
    adj[5].emplace_back(3,2);

    dijkstra(d,1);
    for(int i = 1; i <= n; i++)
        cout << d[i] << " ";
}