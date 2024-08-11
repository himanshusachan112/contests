#include <bits/stdc++.h>
using namespace std;
#define int long long


// prefect prefixe
//https://www.codechef.com/problems/PREPER?tab=statement
void perfect_prefixes(int a[], int n){
	    int ans=0;
	    int sum=0;
	    int cursum[]={0,0};
	    int add=0;
	    for(int i=0;i<n;i++){
	        sum+=a[i];
	        if(sum==((i+1)*(i+2))/2)ans++;
	        if(i<n-1){
	            int bef=(sum==((i+1)*(i+2))/2);
	            int aft=((sum-a[i]+a[i+1])==((i+1)*(i+2))/2);
	            cursum[i%2]=max(0ll,cursum[i%2]+aft-bef);
	            add=max(add,cursum[i%2]);
	        }
	    }
	    cout<<ans+add<<endl;
}
//=================================================================================================



// minimum operation to make array equal to target.
//https://leetcode.com/problems/minimum-operations-to-make-array-equal-to-target/description/
long long minimumOperations(vector<int>& nums, vector<int>& target) {
        int n=nums.size();
        long long ans=0;
        for(int i=0;i<n;i++){
            int curr=target[i]-nums[i];
            int prev;
            if(i==0 || (curr>=0 && (target[i-1]-nums[i-1])<=0) || (curr<=0 && (target[i-1]-nums[i-1])>=0) ){
                prev=0; 
            }
            else{
                prev=target[i-1]-nums[i-1];
            }
            // cout<<curr<<" "<<prev<<endl;
            if(abs(curr)>abs(prev)){
                ans+=(abs(curr)-abs(prev));
            }



        }
        return ans;
    }
//===========================================================


// find the minimum area to cover all ones II
// https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-ii/description/
long long minimumArea(vector<vector<int>>& grid, int startj , int starti, int endj, int endi) {
        
        long long left=1e5,right=0,top=1e5,bottom=0;
        bool flag=true;
        for(int i=starti; i<=endi; i++){
            for(int j=startj; j<=endj; j++){
                if(grid[i][j]==1){
                    flag=false;
                    left=min(left,(long long)j);
                    right=max(right,(long long)j);
                    top=min(top,(long long)i);
                    bottom=max(bottom,(long long)i);
                }
            }
        }
        if(flag) return 1;
        cout<<left<<" "<<right<<" "<<top<<" "<<bottom<<endl;
        return (right-left+1)*(bottom-top+1);
    }
    int minimumSum(vector<vector<int>>& grid) {
        int n=grid.size();
        int m=grid[0].size();
        long long ans=1e5;
        for(int i=1 ; i<n-1; i++){
            long long  a=minimumArea(grid,0,0,m-1,i-1);
            for(int j=i; j<n; j++){
                if(i==j) continue;
                
                long long  b=minimumArea(grid,0,i,m-1,j-1);
                long long  c=minimumArea(grid,0,j,m-1,n-1);
                ans=min(ans, a+b+c);

            }
        }

        for(int i=1 ; i<m-1; i++){
            long long a=minimumArea(grid,0,0,i-1,n-1);
            for(int j=i; j<m; j++){
                if(i==j) continue;
                
                long long b=minimumArea(grid,i,0,j-1,n-1);
                long long c=minimumArea(grid,j,0,m-1,n-1);
                ans=min(ans, a+b+c);

            }
        }

        for(int i=1 ; i<n; i++){
            long long p=minimumArea(grid,0,0,m-1,i-1);
            long long q=minimumArea(grid,0,i,m-1,n-1);
            for(int j=1; j<m; j++){
                
                long long a=minimumArea(grid,0,i,j-1,n-1);
                long long b=minimumArea(grid, j,i ,m-1 ,n -1);
                ans=min(ans,a+b+p);

                a=minimumArea(grid,0,0,j-1,i-1);
                b=minimumArea(grid, j,0 ,m-1 ,i -1);
                ans=min(ans,a+b+q);
            }
        }


        for(int i=1 ; i<m; i++){
            long long p=minimumArea(grid,0,0,i-1,n-1);
            long long q=minimumArea(grid,i,0,m-1,n-1);
            for(int j=1; j<n; j++){
                
                long long a=minimumArea(grid,i,0,m-1,j-1);
                long long b=minimumArea(grid, i,j ,m-1 ,n-1);
                ans=min(ans,a+b+p);

                a=minimumArea(grid,0,0,i-1,j-1);
                b=minimumArea(grid, 0,j ,i-1 ,n-1);
                ans=min(ans,a+b+q);
            }
        }
        return ans;

    }
//=============================================================================================



int32_t main(){

    int arr[]={1,2,3,4,5};
	vector<int> a={2,3,4},b={5,3,2};
    vector<vector<int>> vec={{1,0,1},{0 ,1 ,1}};

    // perfect_prefixes(arr,5);
	// cout<<minimumOperations(a,b);
    cout<<minimumSum(vec);

}