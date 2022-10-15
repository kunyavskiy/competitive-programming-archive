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

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "1266"

#ifdef LOCAL
static struct __timestamper {
    string what;
    __timestamper(const char* what) : what(what){};
    __timestamper(const string& what) : what(what){};
	~__timestamper(){
        TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

const int MAXN = 20;

ld g[MAXN][MAXN];


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  	int n,m;
  	scanf("%d%d",&n,&m);
  	    
  	for (int i = 0; i < m; i++){
  		int a, b, r;
  		scanf("%d%d%d",&a,&b,&r);
  		--a,--b;
  		g[a][a] -= 1.0/r;
  		g[a][b] += 1.0/r;
  		g[b][a] += 1.0/r;
  		g[b][b] -= 1.0/r;
  	}

  	--n;
  	for (int i = 0; i < n; i++)
	  	g[i][n] = !i;


	for (int i = 0; i < n; i++){

/*		for (int k = 0; k < n; k++)
			for (int j = 0; j <= n; j++)
				eprintf("%.2lf%c", (double)g[k][j], " \n"[j==n]);
		eprintf("\n");*/

		int best = i;
		for (int k = i; k < n; k++)
			if (abs(g[k][i]) > abs(g[best][i]))
				best = k;
	    assert(abs(g[best][i]) >= 1e-9);     
	    for (int j = 0; j <= n; j++)
	    	swap(g[best][j], g[i][j]);
	    for (int j = 0; j < n; j++)
	    	if (i != j) {
	    		ld coef = g[j][i] / g[i][i];
	    		for (int k = 0; k <= n; k++)
	    			g[j][k] -= coef * g[i][k];
	    		assert(fabs(g[j][i]) < 1e-9);
	    	}
	}	

//	for (int i = 0; i < n; i++)
//		eprintf("%.2lf\n", (double)(g[i][n] / g[i][i]));


	printf("%.2lf\n", (double)abs(g[0][n] / g[0][0]));
    return 0;
}