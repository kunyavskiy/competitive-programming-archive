//#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "1156"

typedef long long ll;
typedef long double ld;

int n,m;
int color[110];

vector<int> comps[2][110];
vector<int> g[110];
int ccnt;

void dfs(int v,int c){
	if (color[v] == c) return;
	if (color[v] != -1) {
		printf("IMPOSSIBLE\n");
		exit(0);
	}
	color[v] = c;
	comps[c][ccnt].pb(v);
	for (int i = 0; i < (int)g[v].size(); i++)
		dfs(g[v][i], 1 - c);
}

int dp[110][110];

vector<int> res1,res2;

void go(int c,int n){
	assert(c >= 0 && n >= 0 && dp[c][n]);
	if (c == 0) return;
	if ((int)comps[0][c-1].size() <= n && dp[c-1][n - (int)comps[0][c-1].size()]){
		res1.insert(res1.end(), comps[0][c-1].begin(), comps[0][c-1].end());
		res2.insert(res2.end(), comps[1][c-1].begin(), comps[1][c-1].end());
		go(c-1, n - (int)comps[0][c-1].size());
		return;
	}
	res2.insert(res2.end(), comps[0][c-1].begin(), comps[0][c-1].end());
	res1.insert(res1.end(), comps[1][c-1].begin(), comps[1][c-1].end());
	go(c-1, n - (int)comps[1][c-1].size());
}

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
    scanf("%d %d",&n,&m);
    for (int i = 0; i < m; i++){
    	int a,b;
    	scanf("%d %d",&a,&b);
    	--a,--b;
    	g[a].pb(b);
    	g[b].pb(a);
    }

    memset(color,-1,sizeof(color));

    for (int i = 0; i < 2*n; i++)
    	if (color[i] == -1){
    		dfs(i, 0);
    		ccnt++;
    	}
    dp[0][0] = 1;
    for (int i = 0; i < ccnt; i++)
    	for (int j = 0; j <= n; j++)    		
    		if (dp[i][j]) {
    			dp[i+1][j+comps[0][i].size()] = 1;
    			dp[i+1][j+comps[1][i].size()] = 1;
    		}
    if (!dp[ccnt][n]){
    	printf("IMPOSSIBLE\n");
    	return 0;
    }
    go(ccnt,n);  
    assert((int)res1.size() == n);
    assert((int)res2.size() == n);
    for (int i = 0; i < (int)res1.size(); i++)
    	printf("%d%c", res1[i]+1," \n"[i==(int)res1.size()-1]);
    for (int i = 0; i < (int)res2.size(); i++)
    	printf("%d%c", res2[i]+1," \n"[i==(int)res2.size()-1]);
    TIMESTAMP(end);
    return 0;
}