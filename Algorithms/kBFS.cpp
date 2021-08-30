#include <bits/stdc++.h>
using namespace std;

const int MAXW = 2;
const int N = 1000005;

vector < pair<int,int> > adj[N];
queue <int> nxt[MAXW+1];

bool v[N];
int d[N];

void kBFS(int src){
    int processing = 1, curDist = 0;
    nxt[0].push(src);

    while(processing > 0){
        int modDist = curDist % (MAXW + 1);
        while(!nxt[modDist].empty()){
            for(pair<int,int> edge : adj[nxt[modDist].front()]){
                if(!v[edge.first]){
                    v[edge.first] = 1;
                    nxt[(curDist + edge.second) % (MAXW + 1)].push(edge.first);
                    processing++;
                }
            }
            d[nxt[modDist].front()] = curDist;
            nxt[modDist].pop();
            processing--;
        }
        curDist++;
    }
}

char grid[505][505];
int n;
int src, dest;

bool isValid(int row, int col){
    if(row < 0 || row >= n || col < 0 || col >= n)
        return 0;
    return grid[row][col] != 'X';
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> grid[i][j];
            if(grid[i][j] == 'T')
                src = i*n+j+1;
            else if(grid[i][j] == 'G')
                dest = i*n+j+1;
        }
    }

    for(int row = 0; row < n; row++){
        for(int col = 0; col < n; col++){
            if(grid[row][col] != 'X'){
                int node = row*n + col + 1;
                if(isValid(row+1,col))
                    adj[node].push_back({node+n,0});
                if(isValid(row-1,col))
                    adj[node].push_back({node-n,2});
                if(isValid(row,col+1))
                    adj[node].push_back({node+1,1});
                if(isValid(row,col-1))
                    adj[node].push_back({node-1,1});
            }
        }
    }

    kBFS(src);
    if(v[dest]) cout << d[dest];
    else cout << "IMPOSSIBLE";
    cout << "\n";
}
/*
10
XXXXXXXXXX
X________X
X_T______X
XXXXXXXX_X
X______X_X
X__X_____X  
X__XXXXXXX
X__X____GX
X________X
XXXXXXXXXX
*/