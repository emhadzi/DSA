#include <iostream>
#include <cstring>
using namespace std;
#define ll long long

//When handling sums, BIT can exceed 4 bytes 
ll* BIT;

//Supports updates for queries
//Update A[i] increasing it by val
//To update to specific value : val = newVal - A[i] 
void updateBIT(int i, int val, int N) {
    i++;
    while (i <= N) {
        BIT[i] += val;
        i += i & (-i);
    }
}

//Returns sum from A[0] to A[i] including A[i]
//To get sum [i,j] : getSum(j) - getSum(i-1)
ll getSum(int i) {
    ll sum = 0;
    i++;
    while (i > 0) {
        sum += BIT[i];
        i -= i & (-i);
    }
    return sum;
}

//Creates Binary index tree using values from an array A of size N
void createBIT(int* A, int N) {
    BIT = new ll[N + 1];
    memset(BIT, 0, 8 * N + 8);

    for (int i = 0; i < N; i++)
        updateBIT(i, A[i], N);
}

int main() {
    int N = 5;
    int A[]{ 3,2,5,1,2 };
    createBIT(A, N);
    cout << getSum(3) - getSum(-1) << "\n";
    int newVal = 7;
    int index = 1;
    updateBIT(index, newVal - A[index], N);
    cout << getSum(2) - getSum(0);
}