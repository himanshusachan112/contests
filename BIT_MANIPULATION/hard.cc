#include <bits/stdc++.h>
using namespace std;


// maximum total reward using operation I
//https://leetcode.com/problems/maximum-total-reward-using-operations-i/description/
int maxTotalReward(vector<int>& arr) {
        const int mxprofit=100000;
        bitset<mxprofit+1> currentprofit;
        currentprofit[0]=1;
        sort(arr.begin(), arr.end());

        for(int i=0; i<arr.size(); i++){
            int x=(mxprofit-(arr[i]-1));
            currentprofit |= (currentprofit << x >> x << arr[i]);
        }

        for(int profit=mxprofit; profit>=0; profit--){
            if(currentprofit[profit]) return profit;
        }
        return -1;
}
//=======================================================================================================================



int main(){
    vector<int> vec={1,1,3,3}; 

    cout<<maxTotalReward(vec);

}