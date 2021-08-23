#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int D = 256;
const int MOD = 1000000007;

int txt_rows, txt_cols, pat_rows, pat_cols;
char txt[1005][1005], pat[1005][1005];
ll horHash[1005][1005], verHash[1005];
ll patHash, curHash;

void read(){
	cin >> txt_rows >> txt_cols;
	for(int i = 0; i < txt_rows; i++){
		for(int j = 0; j < txt_cols; j++)
			cin >> txt[i][j];
	} 
	cin >> pat_rows >> pat_cols;
	for(int i = 0; i < pat_rows; i++){
		for(int j = 0; j < pat_cols; j++)
			cin >> pat[i][j];
	} 
}

bool check(int row, int col){
	if(row+pat_rows > txt_rows || col+pat_cols > txt_cols)
		return 0;
	for(int i = row; i < row+pat_rows; i++){
		for(int j = col; j < col+pat_cols; j++){
			if(pat[i-row][j-col] != txt[i][j])
				return 0;
		}
	}
	return 1;
}

void consider(int row, int col){
	if(patHash == curHash){
		//check is optional
		if(check(row,col))
			cout << "{" << row << "," << col << "} ";
	}
}

ll calcPower(ll base, ll exp){
	ll res = 1;
	for(int i = 0; i < exp; i++)
		res = (res * D) % MOD;
	return res;
}

void calcVerHash(){
	ll step = calcPower(D,pat_cols);
	for(int col = 0; col < txt_cols; col++){
		ll power = 1, _hash = 0;
		for(int row = pat_rows-1; row >= 0; row--){
			_hash = (_hash + power * txt[row][col]) % MOD;
			power = (power * step) % MOD;
		}
		verHash[col] = _hash;
	}
}

void calcHorHash(){
	for(int row = 0; row < txt_rows; row++){
		//calculate initial horizontal hash of this row
		curHash = 0;
		for(int col = 0; col < pat_cols; col++){
			//roll
			curHash = (curHash*D) % MOD;
			//add right element
			curHash = (curHash + txt[row][col]) % MOD;
		}
		horHash[row][0] = curHash;
		
		//calculate max power for deletion
		ll power = calcPower(D,pat_cols-1);
		
		//roll until the end
		for(int col = pat_cols; col <= txt_cols; col++){
			//remove last
			curHash = (MOD + curHash - power*txt[row][col-pat_cols]) % MOD;
			//roll 
			curHash = (curHash*D) % MOD;
			//add right element
			curHash = (curHash + txt[row][col]) % MOD;
			horHash[row][col-pat_cols+1] = curHash;
		}
	}
}

ll bruteHash(char grid[1005][1005]){
	ll _hash = 0, power = 1;
	for(int row = pat_rows-1; row >= 0; row--){
		for(int col = pat_cols-1; col >= 0; col--){
			_hash = (_hash + power * grid[row][col]) % MOD;
			power = (power * D) % MOD;
		}
	}
	return _hash;
}

int main(){
	read();
	if(pat_rows > txt_rows || pat_cols > txt_cols)
		return 0;
	calcHorHash();
	calcVerHash();
	curHash = bruteHash(txt);
	patHash = bruteHash(pat);
	
	ll rowMx = calcPower(D, (pat_rows-1)*pat_cols);
	ll rowMult = calcPower(D, pat_cols);
	ll verMx = calcPower(D, pat_cols-1); 
	
	for(int col = 0; col <= txt_cols - pat_cols; col++){
		consider(0,col);
		ll nxt = curHash;
		for(int row = 1; row <= txt_rows - pat_rows; row++){
			//remove upper row (row-1)
			curHash = (MOD + curHash - (rowMx*horHash[row-1][col]) % MOD) % MOD;
			//roll one row
			curHash = (curHash*rowMult) % MOD;
			//add lower row (row+pat_rows)
			curHash = (curHash + horHash[row+pat_rows-1][col]) % MOD;
			consider(row,col);
		}
		if(col < txt_cols - pat_cols){
			//CHANGE COLUMN
			//remove left column
			nxt = (MOD + nxt - (verMx * verHash[col]) % MOD) % MOD;
			//roll once to the right
			nxt = (nxt * D) % MOD;
			//add right column
			nxt = (nxt + verHash[col+pat_cols]) % MOD;
			
			curHash = nxt;
		}
	}	
}
