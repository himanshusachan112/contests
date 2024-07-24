#include <bits/stdc++.h>
using namespace std;


void solve(){
	int n; cin>>n;
	map<int,int> mp;
	int arr[n]; for(auto &x:arr){
		cin>>x;
		mp[x]++;
	}
	
	
	for(auto it:mp){
		if(it.second%2){
			cout<<"YES"<<endl;
			return;
		}
	}
	cout<<"NO"<<endl;

}


int main(){
int t;
cin>>t;
while(t--){
solve();
}


}