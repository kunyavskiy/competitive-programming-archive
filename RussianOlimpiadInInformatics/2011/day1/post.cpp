#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <stack>
#include <deque>
#include <queue>
#include <string>
#include <algorithm>
#include <cassert>
#include <ctime>

#define mp make_pair
#define pb push_back

using namespace std;

typedef long long int64;
typedef double ld;

const string TASKNAME = "post";
const string INFILE = TASKNAME+".in";
const string OUTFILE = TASKNAME + ".out";

const int MAXN=110000;

vector<pair<int64,int> > g[MAXN];
int d[MAXN];
int n;
ld bestval;

ld gettime(int v,ld st){
	ld d=::d[v];
	int tmp=lower_bound(g[v].begin(),g[v].end(),mp(int64(st)-1,-(1<<30)))-g[v].begin();
	for (int i=tmp;;i++){
		if (st < g[v][i].first){
			if (d<=(g[v][i].first-st)*g[v][i].second)
				return st + d/(g[v][i].second);
			d-=(g[v][i].first-st)*g[v][i].second;
			st=g[v][i].first;						
		}					
	}		
}

ld solve(int start){
	ld time = 0;
	for (int i=start;i!=start+n && bestval > time;i++)
		time=gettime(i%n,time);
	return time;
}


int main(){
	//freopen(INFILE.data(),"r",stdin);
//	freopen(OUTFILE.data(),"w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		int e;
		scanf("%d %d",&d[i],&e);
		g[i].resize(e);
		for (int j=0;j<e-1;j++){
			int tmp;
			scanf("%d",&tmp);
			g[i][j].first=tmp;
		}
		g[i].back().first = 1LL<<62LL;
		for (int j=0;j<e;j++)
			scanf("%d",&g[i][j].second);
//		dst[i].resize(i);
//		for (int j=0;j<e;j++)
//			if (j==0)
				
	}
	int best = 0;
	bestval=1e15;
	bestval = solve(0);
	for (int i=0;i<n;i++){
		ld tmp = solve(i);
		if (bestval > tmp){
			bestval = tmp;
			best = i;
		}
	}
	cout.precision(15);
	cout << fixed << best+1<<" "<<bestval<<endl;
	return 0;
}
