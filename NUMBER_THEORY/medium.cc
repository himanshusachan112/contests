#include <bits/stdc++.h>
using namespace std;

// Number hunt.
//https://www.codechef.com/problems/NUMHUNT?tab=statement
bool isPrime(int number) {
    for(int i = 2; i * i <= number; i++) {
        if(number % i == 0) return false;
    }
    return true;
}
void numberhunt(){
	int x;
	cin>>x;
	if(x==1 || x==2) {
		cout<<6<<endl;
		return ;
	}
	vector<int> vec;
	
	while(vec.size()<2){
		if(isPrime(x)){
			vec.push_back(x);
		}
		x++;
	}
	cout<<vec[0]*vec[1]<<endl;

}
//=============================================================





int main(){
//  cout<<numberhunt(3);

}