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

vector<int> g[1100];

int ans[1100];
int to[1100];


int dfs(int v,int p){
	ans[v] = 0;

	for (int i = 0; i < g[v].size(); i++)
		if (g[v][i] != p){
			if (dfs(g[v][i],v) == 0){
				ans[v] = 1;
				to[v] = g[v][i];
				return 1;
			}
		}
	return 0;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int n,s;
  scanf("%d %d",&n,&s);
  --s;
  for (int i = 0; i < n; i++){
  	int a,b;
  	scanf("%d %d",&a,&b);
  	--a,--b;
  	g[a].pb(b);
  	g[b].pb(a);
  }

  for (int i = 0; i < n; i++)
  	sort(g[i].begin(),g[i].end());

  dfs(s,-1);

  if (ans[s] == 0)
  	printf("First player loses\n");
  else
  	printf("First player wins flying to airport %d\n",to[s]+1);
  

  return 0;
}