#include <bits/stdc++.h>
using namespace std;




// count the number of substring with dominant ones.
// https://leetcode.com/problems/count-the-number-of-substrings-with-dominant-ones/description/
int numberOfSubstrings(string s) {
    int n=s.size();
    int ans=0;
    vector<int> vec;
    vec.push_back(-1);
    for(int i=0;i<n;++i){
        if(s[i]=='0') vec.push_back(i);
        int m=vec.size();
        int zeros=0;
        int indx=i,previndx=-1;
        for(int j=m-1;j>=0;--j){
            if(zeros*zeros > i+1) break;
            previndx=indx;
            indx=vec[j];
            int ones=i-indx-zeros;
            if(ones>=zeros*zeros){
                ans+=min(ones-(zeros*zeros-1), previndx-indx);
            }
            zeros++;
        }
        
    }
    return ans;

}
//===================================================================================================




int main(){
    
    cout<<numberOfSubstrings("1101");

}