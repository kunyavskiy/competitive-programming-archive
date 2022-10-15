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

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


vector<int> g[110];
char c[110];

void dfs(int v,int col){
	if (c[v] == 0)
		c[v] = col+'0';
	else {
		if (c[v] -'0' != col){
			printf("-1\n");
			exit(0);
		}
		return;	
	}
	for (int i = 0; i < g[v].size(); i++)
		dfs(g[v][i],1-col);

}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int n;
  	scanf("%d",&n);
  	for (int i = 0; i < n; i++){
  		int a;
  		for (;;){
  			scanf("%d",&a);
  			if (a == 0)
  				break;
  			g[i].pb(a-1);
  			g[a-1].pb(i);
  		}
  	}
  	dfs(0,0);
  	puts(c);
  return 0;
}