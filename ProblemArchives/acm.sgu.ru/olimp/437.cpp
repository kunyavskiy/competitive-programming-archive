#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

bool check(int n,int k,int have){
	if (n<=have+1)
		return true;
	if (k==0)
		return false;
	return check(n-have-2,k-1,have+have+1);	
}

int main()
{                        
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n;
	cin>>n;
	if (n==1){
		cout<<0<<endl;
		return 0;
	}
	int l=0,r=n;
	for (;r-l>1;)
		if (check(n,(l+r)/2,(l+r)/2))
			r=(l+r)/2;
		else 
			l=(l+r)/2;
	cout<<r<<endl;
	return 0;
}