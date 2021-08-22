#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n = 4;
int A[4]{5,3,10,2};
ll Seg[3000000];

void combine(int ind){
	Seg[ind] = Seg[2*ind] + Seg[2*ind+1];
}

void upd(int ind, int l, int r, int tar, int val){
	if(l == r && l == tar){ 
		Seg[ind] = val;
		return;
	}
	if(tar < l || r < tar)
		return;
	int mid = (l+r)/2;
	upd(2*ind, l, mid, tar, val);
	upd(2*ind+1, mid+1, r, tar, val);
	combine(ind);
}

long long getSum(int ind, int l, int r, int tl, int tr){
	if(tl <= l && r <= tr)
		return Seg[ind];
	if(r < tl || tr < l)
		return 0;
	int mid = (l+r)/2;
	return getSum(2*ind, l, mid, tl, tr)
		+ getSum(2*ind+1, mid+1, r, tl, tr);
}

void init(int ind, int l, int r){
	if(l == r){
		Seg[ind] = A[l]; 
		return;
	}
	int mid = (l+r)/2;
	init(2*ind, l, mid);
	init(2*ind+1, mid+1, r);
	combine(ind);
}

int main(){
	init(1,0,3);
	cout << getSum(1,0,3,0,1) << "\n";
	cout << getSum(1,0,3,1,3) << "\n";
	upd(1,0,3,1,2);
	upd(1,0,3,3,0);
	cout << getSum(1,0,3,0,3) << "\n";
	cout << getSum(1,0,3,1,2) << "\n";
}
