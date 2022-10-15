#ifndef LOCAL
    #pragma comment(linker, "/STACK:64000000")
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

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef double ld;

ld dp[1100][1100];

vector<int> g[1100];

vector<int> under[1100];

int x[1100];
int y[1100];

inline ld dist(int a,int b){
	return sqrt((x[a]-x[b])*(x[a]-x[b]) + (y[a]-y[b])*(y[a]-y[b]) +0.0);
}


void solve(int v,int p){

	for (int i = 0; i < (int)g[v].size(); i++)
		if (g[v][i] == p){
			swap(g[v][i],g[v][g[v].size()-1]);
			g[v].pop_back();
			break;
		}

	if (g[v].size() == 0){
		under[v].pb(v);
		dp[v][v] = 0;
		return;
	}

	for (int i = 0; i < (int)g[v].size(); i++)
		solve(g[v][i],v);

	sort(g[v].begin(),g[v].end());	

	ld* dp1 = new ld[g[v].size()+10];

	do {
		dp1[0] = dist(v,g[v][0]);


		for (int i = 0; i+1 < (int)g[v].size(); i++){
			dp1[i+1] = 1e20;
			vector<int>& u = under[g[v][i]];
			for (int j = 0; j < (int)u.size(); j++)
				dp1[i+1] = min(dp1[i+1],dp1[i] + dp[g[v][i]][u[j]] + dist(u[j],g[v][i+1]));
		}

		vector<int>& u = under[g[v].back()];
		ld tmp = dp1[g[v].size()-1];
		for (int i = 0; i < (int)u.size(); i++)
			dp[v][u[i]] = min(dp[v][u[i]],tmp + dp[g[v].back()][u[i]]);

	} while (next_permutation(g[v].begin(),g[v].end()));

	delete[] dp1;

	for (int i = 0; i < (int)g[v].size(); i++)
		for (int j = 0; j < (int)under[g[v][i]].size(); j++)
			under[v].pb(under[g[v][i]][j]);
	under[v].pb(v);
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n;
  scanf("%d",&n);
  for (int i = 0; i < n; i++)
  	scanf("%d %d",&x[i],&y[i]);

  for (int i = 0; i < n-1; i++){
  	int a,b;
  	scanf("%d %d",&a,&b);
  	g[a-1].pb(b-1);
  	g[b-1].pb(a-1);
  }

  for (int i = 0; i < n; i++)
  	for (int j = 0; j < n; j++)
  		dp[i][j] = 1e20;

  solve(0,-1);

  ld ans = 1e20;

  for (int i = 0; i < n; i++)
  	ans = min(ans,dp[0][i] + dist(0,i));

  cout.precision(15);
  cout << fixed << ans << endl;   
  return 0;
}