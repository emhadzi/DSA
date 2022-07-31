#include <bits/stdc++.h>
using namespace std;

stack <pair <int, int> > s1, s2;

void add(int x, stack <pair <int, int> >& s = s1){
	int mn = s.empty() ? x : min(x, s.top().second);
	s.push({x, mn});
}

void rem(){
	if(s2.empty()){
		while(!s1.empty()){
			add(s1.top().first, s2);
			s1.pop();
		}
	}
	s2.pop();
}

int getMin(){
	if(s1.empty())
		return s2.top().second;
	if(s2.empty())
		return s1.top().second;
	return min(s1.top().second, s2.top().second);
}

int main(){
	add(5); add(2); add(2); add(6);
	rem();
	cout << getMin() << " ";
	add(3);
	cout << getMin() << " ";
	rem(); rem();
	cout << getMin() << " ";
}
