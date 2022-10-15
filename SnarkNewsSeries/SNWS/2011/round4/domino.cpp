#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "domino"
#define close botva2156

using namespace std;

typedef long long int64;
typedef long double ld;

const int MAXN=150000;

vector<int> g[MAXN];
bool ugol[MAXN];
int n;

void iterate(int start){
	int n0=n;
	for (int i=start;i<n0;i++){
		if (g[i].size()==3) continue;
		n++;
		g[i].pb(n);
		g[n].pb(i);
		n++;
		if (ugol[i]){
			ugol[n]=true;
			++n;
		}
	}
	for (int i=n0;i<n-1;i++){
		g[i].pb(i+1);
		g[i+1].pb(i);
	}
	g[n-1].pb(n0);
	g[n0].pb(n-1);	
}

int color[MAXN];
int c1[10],c2[10];
int N;
int ans;
bool used[MAXN];

bool canset(int v,int val){
	if (color[v]!=-1)
		return false;
	for (int i=0;i<g[v].size();i++)
		if (color[g[v][i]]!=-1 && color[g[v][i]]!=val)
			return false;
	return true;
}

bool canset(int v1,int v2,int num){
	if (!canset(v1,c1[num]) || !canset(v2,c2[num]))
		return false;
	return true;	
}

bool close(int v){
	for (int i=0;i<g[v].size();i++)
		if (color[g[v][i]]!=-1)
			return true;
	return false;
}

void perebor(int val,bool first){
	ans=max(ans,val);
	for (int pos=0;pos<N;pos++){
		if (used[pos]) continue;
		for (int i=0;i<n;i++)
			for (int j=0;j<g[i].size();j++)
				if (canset(i,g[i][j],pos)){				
					int v=g[i][j];
					if (!close(i) && !close(v)){
						if (!(first && i==0 && j==0))
						 continue;
					}
					int add=0;
					for (int it=0;it<g[i].size();it++)
						if (color[g[i][it]]!=-1)
							add++;
					for (int it=0;it<g[v].size();it++)
						if (color[g[v][it]]!=-1)	
							add++;
					used[pos]=true;
					color[i]=c1[pos];
					color[v]=c2[pos];
					perebor(val+add,false);
					color[i]=-1;
					color[v]=-1;
					used[pos]=false;				
				}
	}

}




int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
	for (int i=0;i<6;i++){
		g[i].pb((i+1)%6);
		g[i].pb((i+5)%6);
		ugol[i]=true;
	}
	n=6;
	int st=0;
	for (int i=1;i<7;i++){
		int nst=n;
		iterate(st);
		st=nst;
	}
	memset(color,-1,sizeof(color));
	cin>>N;
	for (int i=0;i<N;i++)
		cin>>c1[i]>>c2[i];
	perebor(0,true);
	cout<<ans<<endl;
	return 0;
} 