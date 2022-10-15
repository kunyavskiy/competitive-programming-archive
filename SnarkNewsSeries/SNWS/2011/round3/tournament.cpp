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

#define taskname "tournament"

using namespace std;

typedef long long int64;
typedef long double ld;

const int MAXN=110000;

bool my[MAXN];
bool used[MAXN];
vector<int> g[MAXN];

void dfs(int v){
	if (used[v]) return;
	used[v]=true;
	for (int i=0;i<g[v].size();i++)
		dfs(g[v][i]);	
}



int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
	int n,m,k;
	scanf("%d %d %d",&n,&k,&m);
	for (int i=0;i<k;i++){
		int a;
		scanf("%d",&a);
		my[a-1]=true;
	}
	for (int i=0;i<m;i++){
		int a,b;
		scanf("%d %d",&a,&b);
		--a,--b;
		g[a].pb(b);
	}
	for (int i=0;i<n;i++)
		if (my[i])
			dfs(i);
	for (int i=0;i<n;i++)
		if (!used[i]){
			printf("no\n");
			return 0;
		}
	printf("yes\n");
	return 0;
} 