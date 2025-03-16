//https://zhtluo.com/cp/splay-tree-one-tree-to-rule-them-all.html
#include <bits/stdc++.h>
using namespace std;

struct Node{
	int val, sz;
	Node *par, *c[2];
	
	Node(int val) : sz(1), val(val){
		c[0] = c[1] = par = nullptr;
	}

	void upd(){
		sz = 1;
		for(int i = 0; i < 2; i++)
			if(c[i]) sz += c[i]->sz;
	}
};

Node *root;

//1-indexed pos
Node *find(Node *src, int pos){
	int curPos = 1 + (src->c[0] ? src->c[0]->sz : 0);
	if(pos == curPos)
		return src;
	else if(pos < curPos)
		return find(src->c[0], pos);
	return find(src->c[1], pos - curPos);
}

void insert(Node *src, int pos, Node *newNode){
	int curPos = 1 + (src->c[0] ? src->c[0]->sz : 0);
	if(pos <= curPos){ //go left
		if(src->c[0]) insert(src->c[0], pos, newNode);
		else{ 
			src->c[0] = newNode;
			newNode->par = src;
		}
	}
	else{
		if(src->c[1]) insert(src->c[1], pos - curPos, newNode);
		else{
			src->c[1] = newNode;
			newNode->par = src;
		}
	}
	src->upd();
}

void rotate(Node *src){
	Node *tmp = src->par;	
	if(tmp->par){
		bool side = tmp->par->c[1] == tmp;
		tmp->par->c[side] = src;
	}
	src->par = tmp->par;

	bool side = tmp->c[1] == src;
	tmp->c[side] = src->c[!side];
	if(tmp->c[side])
		tmp->c[side]->par = tmp;

	src->c[!side] = tmp;
	tmp->par = src;
	
	tmp->upd(), src->upd();
}

void splay(Node *src){
	while(src->par){
		if(!src->par->par)
			rotate(src);
		else{
			Node *p1 = src->par, *p2 = p1->par;
			bool side1 = (src == p1->c[1]), side2 = (p1 == p2->c[1]);
			if(side1 ^ side2)
				rotate(src), rotate(src); //zig-zag
			else
				rotate(p1), rotate(src); //zig-zig
		}
	}
	root = src;
}

//solution to https://pdp-archive.github.io/30-PDP/c-rafting-statement

int main(){
	//freopen("rafting.in", "r", stdin);
	//freopen("rafting.out", "w", stdout);
	
	int n, pos;
	cin >> n >> pos;
	root = new Node(1);

	for(int i = 2; i <= n; i++){
		cin >> pos;
		Node *x = new Node(i);
		insert(root, pos, x);
		splay(x);
	}

	for(int i = 1; i <= n; i++)
		cout << find(root, i)->val << " ";
}

