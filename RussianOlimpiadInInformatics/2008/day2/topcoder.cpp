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

int round(int64 a,int64 b){
	int res=0;
	for (;a!=b;){
		res++;
		a>>=1;
		b>>=1;
	}
	return res;
}

map<int64,int> minh;
map<int64,vector<int64> > g;
map<int64,vector<int64> > gr;

int cnt(int64 v){
	if (minh.count(v)!=0)
		return minh[v];
	if (g.count(v)==0){
		return minh[v]=1;
	}
	vector<int64>& gv=g[v];
	int sz=gv.size();
	bool ok[64];
	setval(ok,false);
	for (int i=0;i<sz;i++)		
		{
			int64 to=gv[i];
			int64 r=round(v,to);
			int64 toh=cnt(to);
			if (toh>=r)
				ok[r]=true;
		}
	for (int i=1;i<64;i++)
		if (!ok[i])
		{
			minh[v]=i;
			return i;
		}
	return -1;
}

int main()
{
//  freopen("topcoder.in","r",stdin);
//  freopen("topcoder.out","w",stdout);
  int64 k,n,m;
  cin>>k>>n>>m;
  for (int i=0;i<n;i++){
  	int64 a,b;
  	cin>>a>>b;
  	--a,--b;
  	if (g.count(a)==0)
  		g.insert(mp(a,vector<int64>(1,b)));
  	else
  		g[a].pb(b);
  	if (gr.count(b)==0)
  		gr.insert(mp(b,vector<int64>(1,a)));
  	else
  		gr[b].pb(a);
  }
  for (int i=0;i<m;i++){
  	int64 a;
  	cin>>a;
  	--a;
  	int64 ans=k;
  	if (gr.count(a)!=0){
	  	vector<int64>& ga=gr[a];
	  	int sz=ga.size();
	  	for (int i=0;i<sz;i++){
	  			int64 to=ga[i];
	  			int64 r=round(a,to);
	  			int64 toh=cnt(to);
	  		//	cerr<<a<<" "<<to<<" "<<r<<" "<<toh<<endl;
	  			if (toh>=r)
	  				ans=min(ans,r);
	  		}
	  }
	  cout<<ans<<" ";
  }
  cout<<endl;
  return 0;
}