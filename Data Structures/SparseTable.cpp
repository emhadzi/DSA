#include <bits/stdc++.h>
using namespace std;

const int N = 200005, K = 18;

int n = 5;
int a[]{3,2,10,6,1};
long long st[N][K];
int lg[N];

void init(){
	
	lg[1] = 0;
	for(int i = 2; i <= n; i++)
		lg[i] = lg[i/2] + 1;
	
	for(int i = 0; i < n; i++)
		st[i][0] = a[i];
	for(int z = 1; z < 18; z++){
		for(int i = 0; i + (1 << z) <= n; i++)
			st[i][z] = min(st[i][z-1], st[i + (1 << (z-1))][z-1]);
	}	
}

int getMin(int l, int r){
	int z = lg[r - l + 1];
	return min(st[l][z], st[r - (1 << z) + 1][z]);
}

long long getSum(int l, int r){
	int len = r - l + 1, z = 0;
	long long sum = 0;
	while(len > 0){
		if(len & 1){
			sum += st[l][z];
			l += (1 << z);
		}
		len >>= 1; z++;
	}
	return sum;
}

int main(){
	init();
	for(int i = 0; i < 5; i++){
		for(int j = i; j < 5; j++)
			cout << getMin(i, j) << " ";
	}
}
