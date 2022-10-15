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

char g[110][110];
int n,d,a;
ll ans;
bool used[110];

void dfs(int v,int p = -1){
	used[v] = true;
	for (int i = 0; i < n; i++)
		if (i != p && g[v][i] == '1'){
			if (used[i])
				g[v][i] = g[i][v] = 'd',ans+=d;
			else
				g[v][i] = g[i][v] = '0',dfs(i,v);
		}
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    cin >> n >> d >> a;
    for (int i = 0; i < n; i++)
    	for (int j = 0; j < n; j++)
	    	cin >> g[i][j];
	ans = -a;
	for (int i = 0; i < n; i++)
		if (!used[i]){
			ans+=a;
			dfs(i);
			g[0][i] = g[i][0] = 'a';
		}
	g[0][0] = '0';
	cout << ans << endl;
	for (int i = 0; i < n; i++,cout<<endl)
		for (int j = 0; j < n; j++)
			cout << g[i][j];

  return 0;
}