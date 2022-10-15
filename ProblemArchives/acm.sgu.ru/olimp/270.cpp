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

int best;
vector<int64> ans;
vector<int64> cur;

int cnt(int64 a){
	a=abs(a);
	int c=0;
	for (;a;a/=10)
		c++;
	return c;
}


void solve(int64 n,int64 a,int coef){	
	if (n==0){
		int val=0;
		for (int i=0;i<cur.size();i++)
			val+=cnt(cur[i]);
		if (val < best){
			best=val;
			ans=cur;
		}
		return;
	}
	int k=n/a;
	int sz=cur.size();
	for (int i=0;i<k;i++){
		n-=a;
		cur.pb(a*coef);
	}
	solve(n,a/10,coef);
	if (n){
		cur.pb(a*coef);
		solve(a-n,a/10,-coef);
	}
	for (;cur.size()>sz;cur.pop_back());		
}

int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	best=1<<30;
	int64 n;
	cin>>n;		
	int64 a=1;
	for (;a<=n;a=10*a+1);
	solve(n,a/10,1);
	cur.pb(a);
	solve(a-n,a/10,-1);
	cout<<best<<" "<<ans.size()<<endl;
	for (int i=0;i<ans.size();i++)
		cout<<ans[i]<<endl;
    return 0;
}