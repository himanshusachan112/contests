#include <bits/stdc++.h>
using namespace std;


// shortest distance after road additon queries
//https://leetcode.com/problems/shortest-distance-after-road-addition-queries-ii/description/
vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        int dis=n-1;
        vector<int> next;
        for(int i=0;i<n-1;i++){
            next.push_back(i+1);
        }
        vector<int>ans;
        vector<int> vst(n,false);

        for(auto it:queries){
            int start=it[0];
            int end=it[1];
            if(vst[start] || end<=next[start] || start==end){
                ans.push_back(dis);
                continue;
            }

            int steps=0;
            int node=start;
            while(node!=end){
                node=next[node];
                if(node!=end) vst[node]=true;
                steps++;
            }
            dis-=(steps-1);
            next[start]=end;
            ans.push_back(dis);
        }
        return  ans;

    }
//================================================================================================


int main(){
    vector<vector<int>> que={{3,4},{5,6}}

    shortestDistanceAfterQueries(8,que);

}