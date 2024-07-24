#include <bits/stdc++.h>
using namespace std;

// maximum distance premutation.
// https://www.codechef.com/problems/MAXDISTPERM
void max_dis_permutation(int n){
    vector<int> arr(n+1);
    int midindx;
    if(n%2==0){
        midindx=n/2;
    }
    else midindx=n/2 + 1;
    arr[midindx]=n;
    int left=1, right=n-1;
    for(int i=midindx+1;i<=n;i++){
        arr[i]=left;
        left++;
    }
    for(int i=midindx-1;i>=0;i--){
        arr[i]=right;
        right--;
    }
    for(int i=1;i<=n;i++){
        cout<<i<<" ";
    }
    cout<<endl;
    for(int i=1;i<=n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}
//=================================================================================================



// Redundant array.
//https://www.codechef.com/problems/REDUARRAY?tab=statement
int mincost_redundantarray( int arr[], int n){
        map<int, int> mp;   
	    for(int i = 0;i<n;i++){
	        mp[arr[i]]++;
	    }
	    long long int minval = INT_MAX;
	    for(auto it : mp){
	        minval = min(minval, (long long int)(n-it.second)*it.first);
	    }
	    return min(minval, (long long int)n) ;
}
//===================================================================================================


int main(){

    vector<int> arr={};
    int arrr[]={2 ,4,2,5};


    // max_dis_permutation(4);
    cout<<mincost_redundantarray(arrr,4);



}