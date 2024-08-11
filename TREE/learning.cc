#include <bits/stdc++.h>
using namespace std;


// segment trees and updates on points.
// you will get initial array and update query and range query.
// [1,3,2]  1->update query, here you have to update index three to the value of 2.      tc{logn}
// [2,4,6]  2-> range query, here you have to give range of sum from index 4 to index 6.    tc{logn}
class sum_segtree{
    public:
    vector<int> segtree;
    sum_segtree(int n){
        //size will be 4n because (n+n/2+n/4...1)=2n and suppose n is 5 then total nodes will be next 2 to the power n. 
        // so total lenght for segtree is 4n
        segtree.resize(4*n,0); // this is 1 based indexing. 
    }

    void build(vector<int> &arr, int start, int end, int indx){
        if(start==end){
            segtree[indx]=arr[start];
            return ;
        }
        int mid=(start + end)/2;
        build(arr, start, mid, 2*indx);
        build(arr, mid+1, end, 2*indx +1);
        segtree[indx]=segtree[2*indx] + segtree[2*indx+1];
    }

    void update(vector<int> arr, int start, int end, int indx, int pos){
        if(start==end){
            segtree[indx]=arr[pos];
            return;
        }
        int mid=(start+end)/2;

        if(mid>=pos){
            update(arr,start,mid,2*indx,pos);
        }
        else{
            update(arr,mid+1,end,2*indx+1,pos);
        }
        segtree[indx]=segtree[2*indx] + segtree[2*indx + 1]; 
    }
     
    int query(int start, int end, int indx, int l, int r){
        if(start>=l && end<=r){
            return segtree[indx];
        }
        if(l>end || r<start){
            return 0;
        }
        int mid=(start + end)/2;
        int leftanswer=query(start, mid, 2*indx, l,r);
        int rightanswer=query(mid+1,end,2*indx+1,l,r);
        return leftanswer + rightanswer;
    }
};
vector<int> range_sum_array_segtree(vector<int> arr, vector<vector<int>> queries){  // update and query is done on the 0 based indexing.
    int n=arr.size();
    sum_segtree tree(n);
  
    tree.build(arr,0,n-1,1);
    
    vector<int> ans;
    for(auto query:queries){
        int type=query[0];
        if(type==1){    //update
            int pos=query[1];
            int val=query[2];
            arr[pos]=val;
            tree.update(arr,0,n-1,1,pos);
        }
        else{   //range sum

            ans.push_back(tree.query(0,n-1,1,query[1], query[2]));
        }
    }
    for(auto it:ans) cout<<it<<" ";
    return ans;
}
//=========================================================================================



// segment trees and updates on points.
// you will get initial array and update query and range query.
// [1,3,2]  1->update query, here you have to update index three to the value of 2.      tc{logn}
// [2,4,6]  2-> range query, here you have to give min in range from index 4 to index 6.    tc{logn}
class min_segtree{
    public:
    vector<int> segtree;
    min_segtree(int n){
        segtree.resize(4*n,0);
    }

    void build(vector<int> &arr, int start, int end, int indx){
        if(start==end){
            segtree[indx]=arr[start];
            return ;
        }
        int mid=(start + end)/2;
        build(arr, start, mid, 2*indx);
        build(arr, mid+1, end, 2*indx +1);
        min(segtree[indx]=segtree[2*indx], segtree[2*indx+1]);
    }

    void update(vector<int> arr, int start, int end, int indx, int pos){
        if(start==end){
            segtree[indx]=arr[pos];
            return;
        }
        int mid=(start+end)/2;

        if(mid>=pos){
            update(arr,start,mid,2*indx,pos);
        }
        else{
            update(arr,mid+1,end,2*indx+1,pos);
        }
        segtree[indx]=min(segtree[2*indx], segtree[2*indx + 1]); 
    }
     
    int query(int start, int end, int indx, int l, int r){
        if(start>=l && end<=r){//complete overlap
            return segtree[indx];
        }
        if(l>end || r<start){// no overlap
            return INT_MAX;
        }
        int mid=(start + end)/2;
        int leftanswer=query(start, mid, 2*indx, l,r);
        int rightanswer=query(mid+1,end,2*indx+1,l,r);
        return min(leftanswer ,rightanswer);
    }
};
vector<int> range_min_arrays_segtree(vector<int> arr, vector<vector<int>> queries){
    int n=arr.size();
    min_segtree tree(n);
  
    tree.build(arr,0,n-1,1);
    
    vector<int> ans;
    for(auto query:queries){
        int type=query[0];
        if(type==1){    //update
            int pos=query[1];
            int val=query[2];
            arr[pos]=val;
            tree.update(arr,0,n-1,1,pos);
        }
        else{   //range min

            ans.push_back(tree.query(0,n-1,1,query[1], query[2]));
        }
    }
    for(auto it:ans) cout<<it<<" ";
    return ans;
}
//=========================================================================================



// segment trees and updates on range.
// you will get initial array and update query and range query.
// 1->update query, here you have to increment index from 2 to 4 to the value of 5.    tc{logn}
// 2-> range query, here you have to give range of sum from index 4 to index 6.    tc{logn}
class lazy_sum_segtree{
    public:
    vector<int> segarr,lazy;
    lazy_sum_segtree(int n){
        segarr.resize(4*n,0);
        lazy.resize(4*n,0);
    }

    void build(int start, int end, int indx, int arr[]){
        if(start==end){
            segarr[indx]=arr[start];
            return ;
        }
        int mid=(start+end)>>1;
        build(start,mid,2*indx,arr);
        build(mid+1,end,2*indx+1,arr);
        segarr[indx]=segarr[2*indx] + segarr[2*indx+1];
    }

    void update(int start, int end, int indx, int l, int r, int val){
        //update the previous remaining updates and propagete downward.
        cout<<"start"<<endl;
        if(lazy[indx]!=0){
            segarr[indx]+=((end-start+1)*lazy[indx]);
            //propagate the lazy updates downward 
            //for the remaining updates to get updated.
            if(start!=end){
                lazy[indx*2]+=lazy[indx];
                lazy[2*indx+1]+=lazy[indx];
            }
            lazy[indx]=0;
        }
        cout<<"no overlap "<<endl;

        //no overlap
        if(start >r || end <l){
            return ;
        }
        cout<<"complete overlap "<<endl;
        //complete overlap
        if(start>=l && end<=r){
            segarr[indx]+=(end-start+1)*val;
            if(start!=end){
                lazy[indx*2]+=val;
                lazy[2*indx+1]+=val;
            }
            return ;
        }
        cout<<" partial overlap"<<endl;

        //partial overlap
        int mid=(start+end)/2;
        update(start,mid,2*indx,l,r,val);
        update(mid+1,end,2*indx+1,l,r,val);
        segarr[indx]=segarr[2*indx] + segarr[2*indx+1];
    }


    int query(int start, int end, int indx, int l, int r){
        // update if any updates are remaining so that nodes remain fresh.
        if(lazy[indx]!=0){
            segarr[indx]+=((end-start+1)*lazy[indx]);
            //propagate the lazy updates downward 
            //for the remaining updates to get updated.
            if(start!=end){
                lazy[indx*2]+=lazy[indx];
                lazy[2*indx+1]+=lazy[indx];
            }
            lazy[indx]=0;
        }

        //no overlap
        if(start >r || end <l){
            return 0;
        }
        //complete overlap
        if(start>=l && end<=r){
            return segarr[indx];
        }


        //partial overlap
        int mid=(start+end)/2;
        int left=query(start,mid,2*indx,l,r);
        int right=query(mid+1,end,2*indx+1,l,r);
        return left+right;

    }
        
};
void range_sum_array_segtree_lazy(){
    int n;
    cin>>n;
    int arr[n];
    for(auto &it:arr)  cin>>it;

    lazy_sum_segtree tree(n);
    tree.build(0,n-1,1,arr);
    int q;
    cin>>q;
    while(q--){
        int type; cin>>type;
        if(type==1){
            cout<<"lr"<<endl;
            int l,r; cin>>l>>r;
            // asking for sum between indx l and r inclusive.

            cout<<tree.query(0,n-1,1,l,r)<<endl;
        }
        else{
            int l,r,val; cin>>l>>r>>val;
            //update all values from indx l to r are incremented by val. 
            tree.update(0,n-1,1,l,r,val);
            cout<<"cosfm"<<endl;
        }
    }
}
//==============================================================================================



// segment trees and updates on range.
// you will get initial array and update query and range query.
// 1->update query, here you have to increment index from 2 to 4 to the value of 5.    tc{logn}
// 2-> range query, here you have to give max in index 4 to index 6.    tc{logn}
class lazy_min_segtree{
    public:
    vector<int> segarr,lazy;
    lazy_min_segtree(int n){
        segarr.resize(4*n,0);
        lazy.resize(4*n,0);
    }

    void build(int start, int end, int indx, int arr[]){
        if(start==end){
            segarr[indx]=arr[start];
            return ;
        }
        int mid=(start+end)>>1;
        build(start,mid,2*indx,arr);
        build(mid+1,end,2*indx+1,arr);
        segarr[indx]=min(segarr[2*indx] ,segarr[2*indx+1]);
    }

    void update(int start, int end, int indx, int l, int r, int val){
        //update the previous remaining updates and propagete downward.
        cout<<"start"<<endl;
        if(lazy[indx]!=0){
            segarr[indx]+=lazy[indx];
            //propagate the lazy updates downward 
            //for the remaining updates to get updated.
            if(start!=end){
                lazy[indx*2]+=lazy[indx];
                lazy[2*indx+1]+=lazy[indx];
            }
            lazy[indx]=0;
        }
        cout<<"no overlap "<<endl;

        //no overlap
        if(start >r || end <l){
            return ;
        }
        cout<<"complete overlap "<<endl;
        //complete overlap
        if(start>=l && end<=r){
            segarr[indx]+=(end-start+1)*val;
            if(start!=end){
                lazy[indx*2]+=val;
                lazy[2*indx+1]+=val;
            }
            return ;
        }
        cout<<" partial overlap"<<endl;

        //partial overlap
        int mid=(start+end)/2;
        update(start,mid,2*indx,l,r,val);
        update(mid+1,end,2*indx+1,l,r,val);
        segarr[indx]=min(segarr[2*indx]  ,segarr[2*indx+1]);
    }


    int query(int start, int end, int indx, int l, int r){
        // update if any updates are remaining so that nodes remain fresh.
        if(lazy[indx]!=0){
            segarr[indx]+=lazy[indx];
            //propagate the lazy updates downward 
            //for the remaining updates to get updated.
            if(start!=end){
                lazy[indx*2]+=lazy[indx];
                lazy[2*indx+1]+=lazy[indx];
            }
            lazy[indx]=0;
        }

        //no overlap
        if(start >r || end <l){
            return INT_MAX;
        }
        //complete overlap
        if(start>=l && end<=r){
            return segarr[indx];
        }


        //partial overlap
        int mid=(start+end)/2;
        int left=query(start,mid,2*indx,l,r);
        int right=query(mid+1,end,2*indx+1,l,r);
        return min(left,right);

    }
        
};
void range_min_array_segtree_lazy(){
    int n;
    cin>>n;
    int arr[n];
    for(auto &it:arr)  cin>>it;

    lazy_min_segtree tree(n);
    tree.build(0,n-1,1,arr);
    int q;
    cin>>q;
    while(q--){
        int type; cin>>type;
        if(type==1){
            cout<<"lr"<<endl;
            int l,r; cin>>l>>r;
            // asking for sum between indx l and r inclusive.

            cout<<tree.query(0,n-1,1,l,r)<<endl;
        }
        else{
            int l,r,val; cin>>l>>r>>val;
            //update all values from indx l to r are incremented by val. 
            tree.update(0,n-1,1,l,r,val);
            cout<<"cosfm"<<endl;
        }
    }
}
//==============================================================================================



// segment trees and updates on range.
// you will get initial array of coins head(1) and tail(0)  and update query and range query.
// 1->update query, here you have to flip indx from 2 to 4.    tc{logn}
// 2-> range query, here you have to give total heads from index 4 to index 6.    tc{logn}
class lazy_flip_segtree{
    public:
    vector<int> segarr,lazy;
    lazy_flip_segtree(int n){
        segarr.resize(4*n,0);
        lazy.resize(4*n,0);
    }

    void build(int start, int end, int indx, int arr[]){
        if(start==end){
            segarr[indx]=arr[start];
            return ;
        }
        int mid=(start+end)>>1;
        build(start,mid,2*indx,arr);
        build(mid+1,end,2*indx+1,arr);
        segarr[indx]=segarr[2*indx] + segarr[2*indx+1];
    }

    void update(int start, int end, int indx, int l, int r){
        //update the previous remaining updates and propagete downward.
        cout<<"start"<<endl;
        if(lazy[indx]!=0){
            segarr[indx]=((end-start+1)-segarr[indx]);
            //propagate the lazy updates downward 
            //for the remaining updates to get updated.
            if(start!=end){
                lazy[indx*2]=!lazy[2*indx];
                lazy[2*indx+1]=!lazy[2*indx+1];
            }
            lazy[indx]=0;
        }
        cout<<"no overlap "<<endl;

        //no overlap
        if(start >r || end <l){
            return ;
        }
        cout<<"complete overlap "<<endl;
        //complete overlap
        if(start>=l && end<=r){
            segarr[indx]=((end-start+1)-segarr[indx]);
            if(start!=end){
                lazy[indx*2]=!lazy[2*indx];
                lazy[2*indx+1]=!lazy[2*indx+1];
            }
            return ;
        }
        cout<<" partial overlap"<<endl;

        //partial overlap
        int mid=(start+end)/2;
        update(start,mid,2*indx,l,r);
        update(mid+1,end,2*indx+1,l,r);
        segarr[indx]=segarr[2*indx] + segarr[2*indx+1];
    }


    int query(int start, int end, int indx, int l, int r){
        // update if any updates are remaining so that nodes remain fresh.
        if(lazy[indx]!=0){
            segarr[indx]+=((end-start+1)-segarr[indx]);
            //propagate the lazy updates downward 
            //for the remaining updates to get updated.
            if(start!=end){
                lazy[indx*2]=!lazy[2*indx];
                lazy[2*indx+1]=!lazy[2*indx+1];
            }
            lazy[indx]=0;
        }

        //no overlap
        if(start >r || end <l){
            return 0;
        }
        //complete overlap
        if(start>=l && end<=r){
            return segarr[indx];
        }


        //partial overlap
        int mid=(start+end)/2;
        int left=query(start,mid,2*indx,l,r);
        int right=query(mid+1,end,2*indx+1,l,r);
        return left+right;

    }
        
};
void range_flip_array_segtree_lazy(){
    int n;
    cin>>n;
    int arr[n];
    for(auto &it:arr)  cin>>it;

    lazy_flip_segtree tree(n);
    tree.build(0,n-1,1,arr);
    int q;
    cin>>q;
    while(q--){
        int type; cin>>type;
        if(type==1){
            cout<<"lr"<<endl;
            int l,r; cin>>l>>r;
            // asking for sum between indx l and r inclusive.

            cout<<tree.query(0,n-1,1,l,r)<<endl;
        }
        else{
            int l,r,val; cin>>l>>r;
            //update all values from indx l to r are incremented by val. 
            tree.update(0,n-1,1,l,r);
            cout<<"cosfm"<<endl;
        }
    }
}
//==============================================================================================



int main(){

    vector<int> vec={1,2,3,4,5};
    vector<vector<int>> qu={{1,2,1},{2,2,4}};



    // range_sum_array_segtree(vec,qu);
    // range_min_arrays_segtree(vec,qu);
    // range_sum_array_segtree_lazy();
    // range_min_array_segtree_lazy();
    // range_flip_array_segtree_lazy();


  


}