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

#define taskname "trade"

using namespace std;

typedef long long int64;
typedef long double ld;

const int MAXN=110000;

int tin[MAXN];
int tout[MAXN];
int par[MAXN];
vector<int> g[MAXN];
vector<int> l[MAXN];
int n;

void calct(int v,int p){
	static int timer=0;
	par[v]=p;
	tin[v]=timer++;
	for (int i=0;i<g[v].size();i++)
		if (g[v][i]!=p)
			calct(g[v][i],v);
	tout[v]=timer++;	
}

bool ispar(int a,int b){
	return tin[a] <= tin[b] && tout[b] <= tout[a];
}

void getway(int a,int b,vector<int>& v){
	v.clear();
	for (;!ispar(a,b);a=par[a]){
		v.pb(a);
	}
	v.pb(a);
	int tmp=v.size();
	for (;a!=b;b=par[b]){
		v.pb(b);
	}
	reverse(v.begin()+tmp,v.end());
}

void read(){
	scanf("%d",&n);
	for (int i=0;i<n-1;i++){
		int a,b;
		scanf("%d %d",&a,&b);
		--a;--b;
		g[a].pb(b);
		g[b].pb(a);
		int len;
		scanf("%d",&len);
		l[a].pb(len);
		l[b].pb(len);
	}
	calct(0,-1);
}

bool inway[MAXN];
int dest[MAXN];
int d[MAXN];
vector<int> w;
const int inf=(1e+9)+10000;


bool check(int val){
	queue<int> q;
	for (int i=0;i<n;i++){
		inway[i]=false;
		dest[i]=val;
		d[i]=g[i].size();
		if (d[i]==1)
			q.push(i);
	}	
	int last=-1;
	for (;!q.empty();){
		int v=q.front();
		q.pop();
		if (d[v]==0)
			continue;			
		--d[v];		
		int p=-1;
		int len=-1;
		for (int i=0;i<g[v].size();i++)
			if (d[g[v][i]]){
				p=g[v][i];
				len=l[v][i];
				break;
			}		
		--d[p];
		if (d[p]==1)
			q.push(p);				
		if (dest[v] >= len){
			dest[p]=min(dest[p],dest[v]-len);
			continue;
		}
		if (last!=-1){
			getway(last,v,w);
			for (int i=1;i+1<w.size();i++)
				if (inway[w[i]])
					return false;
			for (int i=0;i<w.size();i++){
				inway[w[i]]=true;
				dest[w[i]]=inf;				
			}
			last=v;
		}
		else
			last=v;
	}
	return true;
}

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
	read();
	int l=-1,r=inf-2;
	for (;r-l>1;){
//		cerr<<l<<" "<<r<<endl;
		int mid=(l+r)/2;
		if (check(mid))
			r=mid;
		else
			l=mid;
	}
	cout<<r<<endl;
	return 0;
} 