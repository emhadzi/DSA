#include <bits/stdc++.h>
using namespace std;

int T[1000005], d[1000005], sz[1000005];

int n, m, q;

void init(){
	for(int i = 0; i <= n; i++){
		T[i] = i;
		sz[i] = 1;
	}
}

int root(int x){
	if(T[x] != x)
		return root(T[x]);
	return x;
}

void join(int a, int b){
	a = root(a);
	b = root(b);
	if(a == b)
		return;
	if(d[a] > d[b]){
		T[b] = a;
		sz[a] += sz[b];
	}
	else if(d[a] < d[b]){
		T[a] = b;
		sz[b] += sz[a];
	}
	else{
		T[b] = a;
		sz[a] += sz[b];
		d[a]++;
	}
}

int main(){
	n = 10;
	init();
	join(1,2); join(1,5); join(3,4);
	cout << root(4) << ":" << sz[root(4)] << " ";
	join(6,7); join(4,6);
	cout << root(7) << ":" << sz[root(7)] << " " << root(2) << ":" << sz[root(2)]; 
}
