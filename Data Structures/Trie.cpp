#include <bits/stdc++.h>
using namespace std;

struct Node{
	bool isWord;
	unordered_map <int,int> child;
};

Node T[2000000];
int curNode = 1;

void insertTrie(const vector <int>& v){
	int cur = 0;
	for(int x : v){
		int& nxt = T[cur].child[x];
		if(nxt == 0)
			nxt = curNode++;
		cur = nxt;
	}
	T[cur].isWord = 1;
}

bool findTrie(const vector <int>& v){
	int cur = 0;
	for(int x : v){
		cur = T[cur].child[x];
		if(cur == 0)
			return 0;
	}
	return T[cur].isWord;
}

int main(){
	vector <int> a = {1,5,2};
	vector <int> b = {1,5,3};
	vector <int> c = {2,5,0};
	vector <int> d = {2,1,0};
	insertTrie(a);
	insertTrie(b);
	insertTrie(c);
	insertTrie(d);
	vector <int> e = {2,1,0};
	vector <int> f = {2,1};
	vector <int> g = {1,5,1};
	vector <int> h = {1,5,3};
	cout << findTrie(e) << findTrie(f) << findTrie(g) << findTrie(h); 
}
