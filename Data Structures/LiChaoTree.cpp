#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int C = 1000005;
const ll INF = 1LL << 60;
pair <ll, ll> t[4*C];

inline ll eval(pair <ll, ll> f, int x){
    return f.first * (ll)x + f.second;
}

void insert(pair <ll, ll> f, int ind = 1, int l = 0, int r = C){
    int mid = (l+r)/2;
    ll dl = eval(f, l) - eval(t[ind], l);
    ll dm = eval(f, mid) - eval(t[ind], mid);
    if(dm < 0)
        swap(t[ind], f);
    if(r - l == 1)
        return;
    if(dl * dm > 0)
        insert(f, 2*ind+1, mid, r);
    else
        insert(f, 2*ind, l, mid);
}

void erase(pair <ll, ll> f, int ind = 1, int l = 0, int r = C){
    int mid = (l+r)/2;
    ll dl = eval(f, l) - eval(t[ind], l);
    ll dm = eval(f, mid) - eval(t[ind], l);
    if(f == t[ind]){
        t[ind] = {0, INF};
        return;
    }
    if(dl * dm > 0)
        insert(f, 2*ind+1, mid, r);
    else
        insert(f, 2*ind, l, mid);
}   

ll getMin(int x, int ind = 1, int l = 0, int r = C){
    int mid = (l+r)/2;
    if(r - l == 1)
        return eval(t[ind], x);
    if(x < mid)
        return min(eval(t[ind], x), getMin(x, 2*ind, l, mid));
    return min(eval(t[ind], x), getMin(x, 2*ind+1, mid, r));
}

void init(){
    for(int i = 0; i < 4*C; i++)
        t[i] = {0, INF};
}

int main(){
    init();
    insert({-3, 100});
    insert({-2, 70});
    insert({-1, 50});
    cout << getMin(10) << " " << getMin(20) << " " << getMin(22) << " " << getMin(29) << " " << getMin(35) << endl;
    erase({-2, 70});
    cout << getMin(10) << " " << getMin(20) << " " << getMin(22) << " " << getMin(29) << " " << getMin(35) << endl;
}