#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int D = 256;
const int MOD = 1000000007;

string str, pat;
int n, m;
ll patHash;

bool check(int ind){
	if(ind+m > n)
		return 0;
	for(int i = ind; i < ind+m; i++){
		if(str[i] != pat[i-ind])
			return 0;
	}
	return 1;
}

ll calcHash(string s){
	ll power = 1;
	ll _hash = 0;
	for(int i = m-1; i >= 0; i--){
		_hash = (_hash + (s[i]*power) % MOD) % MOD;
		power = (power*D) % MOD;
	}
	return _hash;
}

int calcMaxPow(){
	ll temp = 1;
	for(int i = 0; i < m-1; i++)
		temp = (temp*D) % MOD;
	return temp;
}

int main(){
	
	cin >> str >> pat;
	n = str.length();
	m = pat.length();
	
	if(m > n)
		return 0;
	
	patHash = calcHash(pat); 
	ll curHash = calcHash(str);
	if(curHash == patHash){
		//optional check
		if(check(0))
			cout << "0 ";
	}
	int mxPow = calcMaxPow();
	
	for(int i = m; i < n; i++){
		//remove last
		curHash = (MOD + curHash - (mxPow*str[i-m]) % MOD) % MOD;
		//roll
		curHash = (curHash*D) % MOD;
		//add first 
		curHash = (curHash + str[i]) % MOD;

		if(curHash == patHash){
			//optional check
			if(check(i-m+1))
				cout << i-m+1 << " ";
		}
	} 
}
