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

#define TASKNAME "CAOS3"

#ifdef LOCAL
static struct __timestamper {
	~__timestamper(){
        TIMESTAMP(end);
	}
} __TIMESTAMPER;
#endif

typedef long long ll;
typedef long double ld;

int dp[25][25][25][25];
int n,m;
char s[25][25];
int have[25][25];

int calc(int xl, int yl, int xr, int yr){
//	eprintf("%d %d %d %d\n", xl, yl, xr, yr);
	if (dp[xl][yl][xr][yr] != -1)
		return dp[xl][yl][xr][yr];

	vector<int> g;
	for (int i = xl; i < xr; i++)
		for (int j = yl; j < yr; j++)
			if (have[i][j])
				g.pb(
				       calc(xl , yl , i , j ) ^
				       calc(xl , j+1, i , yr) ^
				       calc(i+1, yl , xr, j ) ^
				       calc(i+1, j+1, xr, yr)
				    );
			

	sort(g.begin(),g.end());
	g.erase(unique(g.begin(), g.end()), g.end());
	g.pb(g.size()+1);
	int& res = dp[xl][yl][xr][yr];
	res = 0;
	while (g[res] == res) res++;
	return res;
}

void solve(){
	scanf("%d %d",&n,&m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf(" %c",&s[i][j]);

	memset(have, 0, sizeof(have));

	for (int i = 2; i < n-2; i++)
		for (int j = 2; j < m-2; j++){
			bool fail = false;
			for (int k = -2; k <= 2; k++)
				if (s[i+k][j] == '#' || s[i][j+k] == '#')
					fail = true;
			have[i][j] = !fail;
//			if (have[i][j])
//				eprintf("%d %d\n", i, j);
		}

	memset(dp, -1, sizeof(dp));

	int gr = calc(0, 0, n, m);
	if (gr)
		printf("Asuna\n");
	else
		printf("Kirito\n");
}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	int t;
  	scanf("%d",&t);

  	while (t-->0)
  		solve();

      
  return 0;
}