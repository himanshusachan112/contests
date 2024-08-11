#include <bits/stdc++.h>
using namespace std;


// lexicographically smallest string after removing stars.
//https://leetcode.com/problems/lexicographically-minimum-string-after-removing-stars/
string clearStars(string s) {
        vector<int> vec[26];
        int n=s.size();
        vector<bool> present(n,true);
        for(int i=0; i<n; i++){
            if(s[i]=='*'){
                for(int j=0;j<26;j++){
                    if(vec[j].size() > 0){
                        present[vec[j].back()]=false;
                        vec[j].pop_back();
                        break;
                    }
                }
            }
            else{
                vec[s[i] - 'a'].push_back(i);
            }
        } 
        string res;
        for(int i=0;i<n;i++){
            if(s[i]!='*' && present[i]){
                res.push_back(s[i]);
            }
        }
        return res;

    }
//==============================================================================================



int main(){

    // cout<<clearStars("dge*d*");

}