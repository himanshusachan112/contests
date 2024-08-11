#include <bits/stdc++.h>
using namespace std;



//********************************************************EXPONENTIAL**************************************************************

// finding exponential. tc{logn}
long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
//===========================================



// Problem: Compute  pow(a,n)%m (exponent modulo) 
// This is a very common operation. For instance it is used in computing the modular multiplicative inverse.
// this is because modulo operation does not interfare in multiplication.
long long binpow_modulo(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
//===================================================



// You are given a sequence of length n and permutation array(n) . Apply arr it a given permutation  k times.
//applying a permutation to arr[] for 2^N times is same as applying the permutation on itself for N times and then applying it on the arr[].
vector<int> applyPermutation(vector<int> sequence, vector<int> permutation) {
    vector<int> newSequence(sequence.size());
    for(int i = 0; i < sequence.size(); i++) {
        newSequence[i] = sequence[permutation[i]];
    }
    return newSequence;
}

vector<int> permute(vector<int> sequence, vector<int> permutation, long long k) {
    while (k > 0) {
        if (k & 1) {
            sequence = applyPermutation(sequence, permutation);
        }
        permutation = applyPermutation(permutation, permutation);
        k >>= 1;
    }
    return sequence;
}
//=======================================================          







int main(){
    vector<vector<int>> vec={};
    vector<vector<int>> tec={};

    // cout<<binpow(3,5);
    // cout<<binpow_modulo(3,5,2);
    // permute(vec,tec,3);


}