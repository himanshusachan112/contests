#include <bits/stdc++.h>
using namespace std;
#define int long long


// prefect prefixe
//https://www.codechef.com/problems/PREPER?tab=statement
void perfect_prefixes(int a[], int n){
	    int ans=0;
	    int sum=0;
	    int cursum[]={0,0};
	    int add=0;
	    for(int i=0;i<n;i++){
	        sum+=a[i];
	        if(sum==((i+1)*(i+2))/2)ans++;
	        if(i<n-1){
	            int bef=(sum==((i+1)*(i+2))/2);
	            int aft=((sum-a[i]+a[i+1])==((i+1)*(i+2))/2);
	            cursum[i%2]=max(0ll,cursum[i%2]+aft-bef);
	            add=max(add,cursum[i%2]);
	        }
	    }
	    cout<<ans+add<<endl;
}
//=================================================================================================




int32_t main(){

    int arr[]={1,2,3,4,5};


    // perfect_prefixes(arr,5);

}