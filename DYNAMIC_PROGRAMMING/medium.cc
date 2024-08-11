#include <bits/stdc++.h>
using namespace std;


// maximum total cost of alternating subarrays.
//https://leetcode.com/problems/maximize-total-cost-of-alternating-subarrays/
long long maximumTotalCost(vector<int>& nums) {
        int n=nums.size();
        vector<long long> dp(n);
        dp[0]=nums[0];
        for(int i=1;i<n;i++){
            if(nums[i]>=0){
                dp[i]=dp[i-1]+ nums[i];
            }
            else{
                long long a=0;
                (i-2) >= 0 ? a=dp[i-2] : NULL;
                dp[i]=max(dp[i-1] + nums[i], a+ nums[i-1] + abs(nums[i]));
            }
        }
        return dp[n-1];
}
//======================================================================================================



// maximum total damage with spell count.
//https://leetcode.com/problems/maximum-total-damage-with-spell-casting/description/
long long maximumTotalDamage(vector<int>& power) {
        map<long long,long long> mp;
        for(auto it:power){
            mp[it]++;
        }
        long long n=mp.size();
        vector<long long> dp(n);
        dp[0]=mp.begin()->first * mp.begin()->second;
        auto it=mp.begin();
        it++;
        int i=1;
        for(;it!=mp.end();it++,i++){
            long long op1,op2=0;
            op1=dp[i-1];
            auto temp=it;
            temp--;
            long long t=i-1;
            long long check=it->first ;
            op2=it->first * it->second;
            while(t>=0){ 
                if((check - (temp->first) ) >= 3){
                    op2=dp[t]+(it->first * it->second);
                    break;
                }
                temp--;
                t--;
            }
            
            dp[i]=max(op1,op2);
        }
        return dp[n-1];
    }
//==============================================================================================



int main(){

    vector<int> vec={2,3,5,5};

    // cout<<maximumTotalCost(vec);
    cout<<maximumTotalDamage(vec);
}