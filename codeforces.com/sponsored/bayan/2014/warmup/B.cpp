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

#define TASKNAME "B"

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


int g[410][410];
char h[25], v[25];
int n, m;

void adde(int i, int j, int i1, int j1) {
	if (i1 < 0 || i1 >= n) return;
	if (j1 < 0 || j1 >= m) return;
	eprintf("%d %d\n", i, j);
	assert(i * m + j <= 400);
	assert(i1 * m + j1 <= 400);
	g[i * m + j][i1 * m + j1] = 1;
}

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif
            
    scanf("%d%d",&n,&m);
    scanf("%s%s", h, v);

    for (int i = 0; i < n; i++)
    	for (int j = 0; j < m; j++) {
    		adde(i, j, i, j);
    		if (h[i] == '<') adde(i, j, i, j-1);
    		if (h[i] == '>') adde(i, j, i, j+1);
    		if (v[j] == '^') adde(i, j, i-1, j);
    		if (v[j] == 'v') adde(i, j, i+1, j);
    	}

    for (int k = 0; k < n * m; k++)
    	for (int i = 0; i < n * m; i++)
	    	for (int j = 0; j < n * m; j++)	
	    		g[i][j] |= g[i][k] && g[k][j];

	for (int i = 0; i < n * m; i++)
		for (int j = 0; j < n * m; j++)
			if (!g[i][j]) {
				eprintf("%d %d\n", i, j);
				printf("NO\n");
				return 0;
			}
	printf("YES\n");      
    return 0;
}