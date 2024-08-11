#include <bits/stdc++.h>
using namespace std;


// find minimum diameter after merging two trees.
//https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/
    int helpdia(int root, vector<int> adj[], int &dia, vector<int> &vst){
        int max1=1,max2=1;
        vst[root]=1;
        bool val=true;
        for(auto it:adj[root]){
            if(!vst[it]){
                val=false;
                int temp=helpdia(it,adj,dia,vst)+1;
                if(temp>max2){
                    max1=max2;
                    max2=temp;
                }
                else if(temp<=max2 && temp>=max1){
                    max1=temp;
                }
                // cout<<"node=>"<<root<<" "<<"max1=>"<<max1<<" "<<"max2=>"<<max2<<endl;
            
                
            }
        }
        // cout<<root<<"=>"<<max2<<endl;
        dia=max(dia,max1+max2-1);
        if(val){
            return 1;
        }
        return max2;

        
    }
    int finddia(vector<vector<int>> &edges){
        int nodes=edges.size();
        int dia=1;
        vector<int> vst(nodes+1,0);
        vector<int> adj[nodes+1];
        for(auto it:edges){
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }
        helpdia(0,adj,dia,vst);
        return dia;
    }
    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int a=finddia(edges1);
        // cout<<"dia2=>"<<a<<endl;
        int b=finddia(edges2);
        // cout<<"dia2=>"<<b<<endl;
        return max(a/2 + b/2 + 1, max(a-1,b-1));
    }
//====================================================================================================



// alternating groups III
//https://leetcode.com/problems/alternating-groups-iii/description/
class SegTree_3245 {
public:
    SegTree_3245 (int _n) : n (_n) {
        tree_val.resize(4*n, 0);
        tree_cnt.resize(4*n, 0);
    }
    
    int query_sum (int x) {
        return query_sum (x, n-1, 0, n-1, 0);
    }
    
    int query_cnt (int x) {
        return query_cnt (x, n-1, 0, n-1, 0);
    }
    
    void update (int ind, int val) {
        update (ind, val, 0, n-1, 0);
    }
 
private:
    
    vector<int> tree_val;
    vector<int> tree_cnt;
    int n;
    
    int query_sum (int x, int y, int l, int r, int i) {
        if (r < x || l > y) return 0;
        if (l >= x && r <= y) return tree_val[i];
        
        int m = (l+r) >> 1;
        return (
            query_sum (x, y, l, m, i*2+1) +
            query_sum (x, y, m+1, r, i*2+2)
        );
    }
    
    int query_cnt (int x, int y, int l, int r, int i) {
        if (r < x || l > y) return 0;
        if (l >= x && r <= y) return tree_cnt[i];
        
        int m = (l+r) >> 1;
        return (
            query_cnt (x, y, l, m, i*2+1) +
            query_cnt (x, y, m+1, r, i*2+2)
        );
    }
    
    void update (int ind, int val, int l, int r, int i) {
        if (l == r) {
            tree_cnt[i] += val;
            tree_val[i] = tree_cnt[i]*l;
            return;
        }
        
        int m = (l+r) >> 1;
        if (m >= ind) update (ind, val, l, m, i*2+1);
        else update (ind, val, m+1, r, i*2+2);
        
        tree_val[i] = tree_val[i*2+1] + tree_val[i*2+2];
        tree_cnt[i] = tree_cnt[i*2+1] + tree_cnt[i*2+2];
    }
}; 
int n; 
int Count (int q, pair<int,int> last, SegTree_3245& tree) {
        int sum = tree.query_sum(q);
        int cnt = tree.query_cnt(q);
        int ans = sum - (q-1)*cnt;
                
        int l = last.first, r = last.second;
        if (l >= n || (r-l+1) < q) return ans;
        
        if (r >= n) {
            int can = n-l;
            int has = (r-l+1) - (q-1);
            if (can < has) ans -= (has - can);
        }
        return ans;
    }
    
void Remove (pair<int,int> val, set<pair<int,int>>& all, SegTree_3245& tree) {
        all.erase (val);
        if (val.first >= n) return;
        
        tree.update (val.second-val.first+1, -1);
    }
    
void Insert (pair<int,int> val, set<pair<int,int>>& all, SegTree_3245& tree) {
        all.insert (val);
        if (val.first >= n) return;
        
        tree.update (val.second-val.first+1, 1);
    }
    
pair<int,int> GroupContainingX (int ind, set<pair<int,int>>& all) {
        auto it = all.upper_bound({ind, -1});
        if (it != all.begin()) {
            auto prv = it;
            prv --;
            if (prv->second >= ind) it = prv;
        }
        return *it;
    }
    
void update (int ind, int val, set<pair<int,int>>& all, vector<int>& arr, SegTree_3245& tree) {
        if (ind == 2*n-1 || arr[ind] == val) return;
        arr[ind] = val;

        pair<int,int> with_ind = GroupContainingX (ind, all);
        Remove (with_ind, all, tree);
        int l = with_ind.first, r = with_ind.second;
        
        if (l < ind && r > ind) {
            Insert ({l, ind-1}, all, tree);
             Insert ({ind, ind}, all, tree);
            Insert ({ind+1, r}, all, tree);
            return;
        }
        
        // r == ind || l == ind
        if (l == ind && r != ind) Insert ({l+1, r}, all, tree);
        if (r == ind && l != ind) Insert ({l, r-1}, all, tree);
        
        l = r = ind;
        auto it = all.upper_bound({ind, -1});
        
        vector<pair<int,int>> to_remove;
        
        auto lft = it, rgt = it;


        while (lft != all.begin()) {
            lft --;
            if (arr[lft->second] == arr[l]) break;
            
            to_remove.push_back(*lft);
            l = lft->first;
        }
        while (rgt != all.end()) {
            if (arr[rgt->first] == arr[r]) break;
            
            to_remove.push_back(*rgt);
            r = rgt->second;
            rgt ++;
        }
        
        for (auto i : to_remove) Remove (i, all, tree);
        Insert ({l, r}, all, tree);
    }
    
vector<int> numberOfAlternatingGroups(vector<int>& colors, vector<vector<int>>& queries) {
        n = colors.size();
        
        vector<int> arr(2*n);
        for (int j = 0; j < n; j ++) arr[j] = colors[j];
        for (int j = n; j < 2*n; j ++) arr[j] = colors[j-n];
        
        SegTree_3245 tree(2*n);
        
        set<pair<int,int>> all;
        for (int j = 0; j < 2*n-1; j ++) {
            int l = j, r = j+1;
            while (r < 2*n-1 && arr[r] != arr[r-1]) r ++;
            
            Insert ({l, r-1}, all, tree);
            j = r-1;
        }
        for(auto it:all) cout<<it.first<<" "<<it.second<<endl;
        
        vector<int> result;
        for (auto q: queries) {   
            if (q[0] == 1) {
                result.push_back(Count(q[1], GroupContainingX (n, all), tree));
                continue;
            } 
            
            int ind = q[1], val = q[2];
            update (ind, val, all, arr, tree);
            update (n+ind, val, all, arr, tree);
        }
        for(auto it:result) cout<<it<<" ";
        return result;
    }
//=================================================================================================================



// fenwick tree, it is used when there is upgradation->opera->upgrada->opera... ie query and update
// fenwick tree used to do query operation in logn and update in logn.
//https://leetcode.com/problems/peaks-in-array/description/
class fenwicktree{
    public:
    int N;
    vector<long long> fen;
    fenwicktree(int n){
        N=n+1;
        fen.resize(N,0);
    }

    void update(int i, int add){
        while(i<N){
            fen[i]+=add;
            i+=(i&(-i));
        }
    }

    int sum(int i){
        int s=0;
        while(i>0){
            s+=fen[i];
            i=i-(i&(-i));
        }
        return s;
    }

    int rangequery(int l, int r){
        return sum(r) - sum(l);
    }
};
int findupdate(int i, vector<int> &peak, vector<int> &nums, int n){
     
    if(i<=0 || i>=n-1) return 0;
    if(peak[i]){
        if(nums[i]>nums[i-1] && nums[i]>nums[i+1]){
            return 0;
        }
        else{
            peak[i]=0;
            return -1;
        }
    }
    else{
        if(nums[i]>nums[i-1] && nums[i]>nums[i+1]){
            peak[i]=1;
            return 1;
        }
        else{
            return 0;
        }
    }
    return 0;
}
vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {
    int n=nums.size();
    vector<int> peak(n,0);
    fenwicktree tree(n);
    for(int i=1;i<n-1;i++){
        if(nums[i]>nums[i-1] && nums[i]>nums[i+1]){
            peak[i]=1;
            tree.update(i+1,1);
        }
    }
    vector<int> ans;

    for(auto query:queries){
        int type=query[0];

        if(type==1){
            int l=query[1];
            int r=query[2];
            if(r-l <= 1) {
                ans.push_back(0);
                continue;
            }

            int peaks=tree.rangequery(l+1,r-1+1);
            ans.push_back(peaks);

        }
        else if(type==2){
            int indx=query[1];
            int val=query[2];
            if(nums[indx]==val) continue;
            nums[indx]=val;

            int update=findupdate(indx,peak,nums,n);
            if(update) tree.update(indx+1,update);

            update=findupdate(indx+1,peak,nums,n);
            if(update) tree.update(indx+2,update);

            update=findupdate(indx-1,peak,nums,n);
            if(update) tree.update(indx,update);

        }
    }

    for(auto it:ans) cout<<it<<" ";
    return ans;

}
//============================================================================================================



// Xenia and Bit Operations
//https://codeforces.com/problemset/problem/339/D
class segtree_339D{
    public:
    vector<int> segarr;
    segtree_339D(int n){
        segarr.resize(4*n,0);
    }

    void build(int start, int end, int indx, int arr[], int orr){
        if(start==end){
            segarr[indx]=arr[start];
            return ;
        }
        int mid=(start+end)/2;
        build(start,mid,2*indx,arr,!orr);
        build(mid+1,end,2*indx+1,arr,!orr);
        if(orr)   segarr[indx]=segarr[2*indx] | segarr[2*indx+1];
        else   segarr[indx]=segarr[2*indx] ^ segarr[2*indx+1];
    }

    void update(int start, int end, int indx, int orr, int i, int val){
        if(start==end){
            segarr[indx]=val;
            return;
        }
        int mid=(start+end)/2;
        if(i<=mid){
            update(start,mid,2*indx,!orr,i,val);
        }
        else update(mid+1,end,2*indx+1,!orr, i,val);

        if(orr)   segarr[indx]=segarr[2*indx] | segarr[2*indx+1];
        else   segarr[indx]=segarr[2*indx] ^ segarr[2*indx+1];
    }

    int ans(){
        // for(auto it:segarr) cout<<it<<" ";
        // cout<<endl;
        return segarr[1];
    }
};
void xor_and_or_operation(){
    int n,q;
    cin>>n>>q;

    int el=pow(2,n);
    segtree_339D tree(el);
    int arr[el];
    for(int i=0;i<el;i++){
        cin>>arr[i];
    }
    if(n%2==0){
        tree.build(0,el-1,1,arr,0);
    }
    else tree.build(0,el-1,1,arr,1);
    tree.ans();
    while(q--){
        int i,val;
        cin>>i>>val;
        i--;
        // cout<<"comming"<<endl;
        if(n%2==0){
            tree.update(0,el-1,1,0,i,val);
        }
        else tree.update(0,el-1,1,1,i,val);
        // cout<<"not ocmming";
        cout<<tree.ans()<<endl;
    }

}
//====================================================================================================



// . Sereja and Brackets
//https://codeforces.com/problemset/problem/380/C
class info{
    public:
    int open,close,full;
    info(int _open=0, int _close=0, int _full=0){
        open=_open; close=_close; full=_full;
    }
};

class segtree_380C{
    public:
    vector<info> segarr;
    segtree_380C(int n){
        info a(0,0,0);
        segarr.resize(4*n,a);
    }
    info merge(info left, info right){  
        info ans(0,0,0);
        ans.full=left.full + right.full + min(left.open, right.close);
        ans.open=left.open + right.open - min(left.open, right.close);
        ans.close=left.close + right.close - min(left.open,right.close);
        return ans;
    }
    void build(int start, int end, int indx, info arr[]){
        if(start==end){
            segarr[indx]=arr[start];
            return ;
        }
        int mid=(start+end)>>1;
        build(start,mid,2*indx,arr);
        build(mid+1,end,2*indx+1,arr);
        segarr[indx]=merge(segarr[2*indx], segarr[2*indx+1]);
    }
    info query(int start, int end, int indx, int l, int r){
        if(start>=l && end<=r){//complete overlap
            return segarr[indx];
        }
        if(l>end || r<start){// no overlap
            info a;
            return a;
        }
        int mid=(start+end)>>1;
        info left=query(start,mid,2*indx,l,r);
        info right=query(mid+1,end,2*indx+1,l,r);
        return merge(left,right);
    }
};
void serajaandbackets_380C(){
    string s;
    cin>>s;
    int n=s.size();
    segtree_380C tree(n);
    info arr[n];
    for(int i=0;i<n;i++){
        info temp(s[i]=='(', s[i]==')', 0);
        arr[i]=temp;
    }
    tree.build(0,n-1,1,arr);
    int q;
    cin>>q;
    while(q--){
        int l,r;
        cin>>l>>r;
        l--;r--;
        info ans=tree.query(0,n-1,1,l,r);
        cout<<(ans.full*2)<<endl;
    }
}

//=================================================================================================



// time taken to mark all nodes.
// https://leetcode.com/problems/time-taken-to-mark-all-nodes/description/
void findlrmax(int node,int prev,vector<vector<int>> &dp,vector<int> adj[]){

        for(auto it:adj[node]){
            if(it!=prev){
                findlrmax(it,node,dp,adj);
                int curr=dp[0][it] + (it%2 ? 1 : 2);
                if(curr>dp[0][node]){
                    dp[1][node]=dp[0][node]; dp[0][node]=curr;
                }
                else if(curr>dp[1][node]){
                    dp[1][node]=curr;
                }
            }
        }
    }

    void findmax(int node, int prev, vector<vector<int>> &dp, vector<int> adj[], vector<int> &maxiarr){
        for(auto it:adj[node]){
            if(it!=prev){
                int left=dp[0][node], right=dp[1][node],top=maxiarr[node];
                int toremove=max(dp[0][it], dp[1][it]) + (it%2 ? 1: 2);
                int newval;
                if(toremove==left) newval=max(right,top);
                else if(toremove==right) newval=max(left,top);
                else if(toremove==top) newval=max(left,right);
                else newval=max(left,max(right,top));
                maxiarr[it]=newval+(node%2 ? 1:2);
                findmax(it,node,dp,adj,maxiarr);
            }
        }
    }

    vector<int> timeTaken(vector<vector<int>>& edges) {
        int n=edges.size()+1;
        vector<int> ans(n);
        vector<vector<int>> dp(2,vector<int> (n,0));
        vector<int> adj[n];
        for(auto it:edges){
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }
        findlrmax(0,-1,dp,adj);
        // for(auto it:dp){
        //     for(auto x:it) cout<<x<<" ";
        //     cout<<endl;
        // }
        vector<int> maxiarr(n,0);
        maxiarr[0]=0;
        findmax(0,-1,dp,adj,maxiarr);
        // for(auto it:maxiarr) cout<<it<<" ";
        // cout<<endl;
        for(int i=0;i<n;i++){
            ans[i]=max(maxiarr[i],max(dp[0][i], dp[1][i]));
        }
        return ans;
    }
//======================================================================================



// minimum array changes to make diff equeal.
//https://leetcode.com/problems/minimum-array-changes-to-make-differences-equal/description/
int minChanges(vector<int>& nums, int k) {
        int n=nums.size();
        vector<int> maxdiff;
        map<int,int> mp;
        for(int i=0;i<n/2;i++){
            mp[abs(nums[i]-nums[n-1-i])]++;
            int mxdiff=max(abs(k-nums[i]),max(abs(k-nums[n-1-i]),max(nums[i],nums[n-1-i])));
            maxdiff.push_back(mxdiff);
        }
        sort(maxdiff.begin(),maxdiff.end());
        // for(auto it:maxdiff) cout<<it<<" ";
        // cout<<endl;
        int ans=INT_MAX;
        for(auto it:mp){
            int opr1=maxdiff.end()-lower_bound(maxdiff.begin(),maxdiff.end(),it.first);
            opr1-=it.second;
            int opr2=n/2-(opr1+it.second);
            // cout<<opr2<<endl;
            ans=min(ans,opr1 + 2*opr2);
        }
        return ans;
    }
//===================================================================================








int main(){

    vector<vector<int>> edges1={{0,1},{0,2},{0,3}};
    vector<vector<int>> edges2={{0,1}};

    vector<int> nums={0,1,1,1,0,1};
    vector<vector<int>> queries={{2,1,0},{1,4}};
    

    // cout<<minimumDiameterAfterMerge(edges1,edges2);
    // numberOfAlternatingGroups(nums,queries);
    // countOfPeaks(nums,queries);
    // xor_and_or_operation();
    // serajaandbackets_380C();
    // timeTaken(edges2);
    // cout<<minChanges(nums,4);
    

}