//https://zhtluo.com/cp/splay-tree-one-tree-to-rule-them-all.html
#include <bits/stdc++.h>
using namespace std;

struct Node{
	int val, sz;
	Node *par, *c[2];
	
	Node(int val) : sz(1), val(val){}

	void upd(){
		sz = 1;
		for(int i = 0; i < 2; i++)
			if(c[i]) sz += c[i]->sz;
	}
};

Node *root;

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
	if(curPos <= pos){ //go left
		if(src->c[0]) insert(src->c[0], pos, newNode);
		else src->c[0] = newNode;
		newNode->par = src;
	}
	else{
		if(src->c[1]) insert(src->c[1], pos, newNode);
		else src->c[1] = newNode;
		newNode->par = src;
	}
	src->upd();
	cout << src->val << " " << src->sz << endl;
}

int main(){
	root = new Node(5);
	insert(root, 1, new Node(1));
	insert(root, 2, new Node(4));
	cout << "ok" << endl;
	for(int i = 1; i <= 3; i++)
		cout << find(root, i)->val << " ";
}
