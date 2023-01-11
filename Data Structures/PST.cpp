#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node{
	int val;
	Node *l, *r;
	Node() : val(0), l(nullptr), r(nullptr){}
};

vector <Node*> root;
int n;

ll getSum(Node* cur, int l, int r, int tl = 1, int tr = n){
	if(l == tl && r == tr)
		return cur->val;
	int mid = (tl + tr)/2;
	ll sum = 0;
	if(l <= mid) sum += getSum(cur->l, l, min(mid, r), tl, mid);
	if(r > mid) sum += getSum(cur->r, max(l, mid+1), r, mid+1, tr);
	return sum;
}

void updUtil(int pos, int v, Node* old, Node* cur, int tl = 1, int tr = n){
	*cur = *old; 
	if(tl == tr){
		cur->val = v;
		return;
	} 
	int mid = (tl + tr)/2;
	if(pos <= mid){
		cur->l = new Node();
		updUtil(pos, v, old->l, cur->l, tl, mid);
	}
	else{
		cur->r = new Node();
		updUtil(pos, v, old->r, cur->r, mid+1, tr);
	}
	cur->val = cur->l->val + cur->r->val; 
}

inline void upd(int pos, int v, Node* old){
	root.push_back(new Node());
	updUtil(pos, v, old, root.back());
}

void initUtil(Node* cur, int l, int r){
	if(l == r)
		return;
	cur->l = new Node();
	cur->r = new Node();
	int mid = (l+r)/2;
	initUtil(cur->l, l, mid);
	initUtil(cur->r, mid+1, r);
}

inline void init(){
	root.push_back(new Node());
	initUtil(root[0], 1, n);
}

int main(){
	cin >> n;
	init();
	int type, t, pos, v, l, r;
	while(1){
		cin >> type >> t;
		if(type == 1){
			cin >> pos >> v;
			upd(pos, v, root[t]);
			cout << endl;
		}
		else{
			cin >> l >> r;
			cout << getSum(root[t], l, r) << endl;
		}
	}
}
