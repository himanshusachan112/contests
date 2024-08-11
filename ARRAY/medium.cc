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



// Largest k.
// https://www.codechef.com/problems/LARGESTK
static bool largestkcomp(int a, int b){
	return a>b;
}
void largestk(){
	int n;cin>>n;
	map<int,int> mp;
	for(int i=0;i<n;i++){
		int a;
		cin>>a;
		mp[a]++;
	}
	int ans=0;
	int dis=0, track=0;
	vector<int> vec;
	for(auto it:mp){
		vec.push_back(it.second);
	}
	sort(vec.begin(),vec.end(),largestkcomp);
	for(auto it:vec){
		dis++;
		track+=it;
		int k=dis;
		while(k<=track){
			ans=max(ans,k);
			k+=dis;
		}
	}
	cout<<ans<<endl;


}
//====================================================================



// minimize inversion
//https://www.codechef.com/problems/MINIMISEINV?tab=statement
int findinversion(string s){
	int cnt1=0;
	int ans=0;
	for(auto it:s){
		if(it=='1'){
			cnt1++;
		}
		else{
			ans+=cnt1;
		}
	}
	return ans;
}
string changes(string s, int zeros, int ones){
	int n=s.size();
	for(int i=n-1;i>=0 && ones>0;i--){
		if(s[i]=='0'){
			 s[i]='1';
			 ones--;
		}
	}
	for(int i=0;i<n && zeros>0;i++){
		if(s[i]=='1'){
			s[i]='0';
			zeros--;
		}
	}
	return s;
}
void minimize_inverison(){
	int n,k; cin>>n>>k;
	string s;
	cin>>s;
	int ans=findinversion(s);
	for(int i=1;i<=k;i++){
		int a=i;
		int b=k-i;
		string newone=changes(s,a,b);
		string newtwo=changes(s,b,a);
		ans=min(ans,min(findinversion(newone), findinversion(newtwo)));
	}
	cout<<ans<<endl;


}
//=============================================================================



// max min and length
//https://www.codechef.com/problems/MAXMINLEN
void max_min_length(){
	int n;
	cin>>n;
	int arr[n]; 
	for(auto &it:arr) cin>>it;

	sort(arr,arr+n);
	map<int,int> pre,suf;
	//pre
	int cnt=1;
	for(int i=0;i<n;i++){
		if(i==0){
			pre[arr[0]]=1;
			continue;
		}
		if(arr[i]-arr[i-1]==1){
			cnt++;
			pre[arr[i]]=cnt;
		}
		else{
			cnt=1;
			pre[arr[i]]=cnt;
		}
	}
	cnt=1;
	for(int i=n-1;i>=0;i--){
		if(i==n-1){
			suf[arr[n-1]]=1;
			continue;
		}
		if(arr[i+1]-arr[i]==1){
			cnt++;
			suf[arr[i]]=cnt;
		}
		else{
			cnt=1;
			suf[arr[i]]=cnt;
		}
	}
	// for(auto it:pre) cout<<it.second<<" ";
	// cout<<endl;
	// for(auto it:suf) cout<<it.second<<" ";
	// cout<<endl;
	int ans=0;
	for(int i=1;i<n;i++){
		if(pre.find(arr[i]-2)!=pre.end()){
			ans+=(pre[arr[i]-2]*suf[arr[i]]);
			// cout<<"aaya"<<ans<<endl;
		}
	}
	cout<<ans<<endl;


}
//=============================



// find the max len valid subsequence II
//https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-ii/
int maximumLength(vector<int>& nums, int k) {
        int n=nums.size();
        for(auto &it:nums){
            it=it%k;
        }
        int ans=1;

		// starign the wa to find the longest alternative subsequence.
        vector<vector<int>> dp(n,vector<int>(k,0));
        vector<int> last(k,-1);

        for(int i=0;i<n;i++){
            int num=nums[i];
            for(int val=0;val<k;val++){
                int indx=last[val];
                if(indx==-1){
                    dp[i][val]=1;
                }
                else{
                    dp[i][val]=dp[indx][nums[i]]+1;
                    ans=max(ans,dp[i][val]);
                }
            }
            last[nums[i]]=i; 
        }
        return ans;


    }
//========================================================================================================



// minimum number of grid to make binary grid palindromic II
//https://leetcode.com/problems/minimum-number-of-flips-to-make-binary-grid-palindromic-ii/
int minFlips(vector<vector<int>>& grid) {
    
}
//==========================================================================================
int main(){

    vector<int> arr={};
    int arrr[]={2 ,4,2,5};
	vector<vector<int>> vec={};
	
    // max_dis_permutation(4);
    // cout<<mincost_redundantarray(arrr,4);
	// cout<<maximumLength(arr,4);
	cout<<minFlips(vec);
    


}