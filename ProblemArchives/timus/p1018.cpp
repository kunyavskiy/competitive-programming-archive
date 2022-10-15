#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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
#define setval(a,v) memset(a,v,sizeof(a))

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif


#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

vector<int> g[110],l[110];

vector<int> dp[110][110];
int n,q;


void dfs(int v,int p){
	for (int i = 0; i < g[v].size(); i++){
		if (g[v][i] == p){
			swap(g[v][i],g[v].back());
			swap(l[v][i],l[v].back());
			g[v].pop_back();
			l[v].pop_back();
			--i;
			continue;
		}
		dfs(g[v][i],v);
	}

	for (int i = 0; i <= q; i++)
		dp[v][i].resize(g[v].size()+1,-1);
}

int calc(int v,int cnt,int son){
	int& ans = dp[v][cnt][son];
	if (ans != -1)
		return ans;
	ans = -(1<<30);

	if (son == 0)
		return ans = 0;
	

	int to = g[v][son-1];
	int len = l[v][son-1];

	ans = calc(v,cnt,son-1);

	for (int i = 0; i < cnt; i++)
		ans = max(ans,calc(to,i,g[to].size()) + len + calc(v,cnt - i - 1,son-1));

    return ans;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  scanf("%d %d",&n,&q);


  for (int i = 0; i < n -1; i++){
  	int a,b,c;
  	scanf("%d %d %d",&a,&b,&c);
  	--a,--b;
  	g[a].pb(b);l[a].pb(c);
  	g[b].pb(a);l[b].pb(c);
  }

  dfs(0,-1);

  cout << calc(0,q,g[0].size()) << endl;
	
  return 0;
}