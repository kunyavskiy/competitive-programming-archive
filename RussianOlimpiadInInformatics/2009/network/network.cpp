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

const int maxn=100010;
const int maxm=200010;

vector<int> g[maxn];
vector<int> num[maxn];
vector<int> comp[maxm*2];
vector<int> mycomp[maxn];
int cptr;
pair<int,int> reb[maxm];
bool used[maxn];
bool us[maxm];
int tin[maxn];
int fup[maxn];
int tec[maxm];
int tecptr;

void getcomp(int v,int p=-1){
	static int timer=0;
	used[v]=true;
	tin[v]=timer++;
	int sz=g[v].size();
	fup[v]=tin[v];
	for (int i=0;i<sz;i++){
		int to=g[v][i];
		int id=num[v][i];
		if (to==p)
			continue;
		if (!us[id])
		{
			tec[tecptr++]=id;
			us[id]=1;
		}
		if (used[to])
			fup[v]=min(fup[v],tin[to]);
		else
		{
			getcomp(to,v);
			fup[v]=min(fup[v],fup[to]);
			if (fup[to]>=tin[v]){
				comp[cptr].pb(v);
				int pt=0;
				for (;tec[tecptr-1]!=id;tecptr--){
					int idx=tec[tecptr-1];
					comp[cptr].pb(reb[idx].first+reb[idx].second-comp[cptr][pt]);
					pt++;
				}
				int idx=tec[tecptr-1];
				if (pt==0)
					comp[cptr].pb(reb[idx].first+reb[idx].second-comp[cptr][pt]);
				tecptr--;				
				int csz=comp[cptr].size();
				for (int i=0;i<csz;i++)
					mycomp[comp[cptr][i]].pb(cptr);
				cptr++;
			}
		}
	}
}

int tw[1000000];
int x[maxn];
int y[maxn];

void printans(int v,int Y){
//	cerr<<v<<" "<<Y<<endl;
	y[v]=Y;
	x[v]=tw[Y]++;
	int sz=mycomp[v].size();
	for (int i=0;i<sz;i++){
		int c=mycomp[v][i];
		if (us[c])
			continue;
		us[c]=true;
		int csz=comp[c].size();
		for (int j=0;j<csz;j++){
			if (comp[c][j]==v)
				{
					rotate(comp[c].begin(),comp[c].begin()+j,comp[c].end());
					break;
				}
		}		
		for (int j=1;j<csz;j++)
			printans(comp[c][j],Y+1);
	}
}


int main()
{
  freopen("network.in","r",stdin);
  freopen("network.out","w",stdout);
  int n,m;
  scanf("%d %d",&n,&m);
  for (int i=0;i<m;i++)
  	{
  		int a,b;
  		scanf("%d %d",&a,&b);
  		--a;--b;
  		g[a].pb(b);
  		g[b].pb(a);
  		num[a].pb(i);
  		num[b].pb(i);
			reb[i]=mp(a,b);
  	}
	memset(used,false,sizeof(used));
	memset(us,false,sizeof(us));
	getcomp(0);
	memset(us,false,sizeof(us));
	printans(0,0);
	for (int i=0;i<n;i++)
		printf("%d %d\n",x[i],y[i]);
  return 0;
}