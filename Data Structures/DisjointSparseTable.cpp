#include <bits/stdc++.h>
using namespace std;

int n = 5, _n, z;
int a[8]{2,5,10,6,1,0,0,0};
int dst[200005][20];

unsigned int roundToP2(unsigned int i){
	if(__builtin_popcount(i) == 1)
		return i;
	i |= i >> 1;
	i |= i >> 2;
	i |= i >> 4;
	i |= i >> 8;
	i |= i >> 16;
	return i + 1;
}

void init(){
	_n = roundToP2(n);
	for(int i = n; i < _n; i++)
		a[i] = 0; //identity
	
	for(int z = 0; (1 << z) < _n; z++){
		int sz = 1 << z;
		for(int mid = sz; mid < _n; mid += 2*sz){
			int sum = 0; //identity
			for(int i = mid-1; i >= mid-sz; i--){
				sum += a[i];
				dst[i][z] = sum;
			}
			sum = 0;
			for(int i = mid; i < mid+sz; i++){
				sum += a[i];
				dst[i][z] = sum;
			}
		}
	} 
}

int getSum(int l, int r){
	if(l == r)
		return a[l];
	int z = 31 - __builtin_clz(l ^ r);
	return dst[l][z] + dst[r][z];
}

int main(){
	init();
	for(int i = 0; i < n; i++){
		for(int j = i; j < n; j++)
			cout << getSum(i, j) << " ";
	}
}
