#include <bits/stdc++.h>
using namespace std;
#define int long long

int log_a_to_base_b(int a, int b)
{
    return log2(a) / log2(b);
}

void solve(){
    int l,r;cin>>l>>r;
    int ans=0;
    ans=log_a_to_base_b(l,3)+1;
    ans+=ans;
    for(int i=l+1;i<=r;i++){
        ans+=(log_a_to_base_b(i,3)+1);
    }
    cout<<ans<<endl;

}


int32_t main(){
int t;
cin>>t;
while(t--){
solve();
}


}