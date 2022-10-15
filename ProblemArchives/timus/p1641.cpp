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

#define TASKNAME "1641"

typedef long long ll;
typedef long double ld;

int color[110];
bool used[110];
bool g[110][110];


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	int n,m,k;
  	scanf("%d %d %d",&n,&k,&m);

  	for (int i = 0; i < n; i++)
  		color[i] = i % k + 1;

  	for (int i = 0; i < n; i++)
  		printf("%d\n", color[i]);

  	for (int i = 0; i < n; i++)
  		for (int j = i+1; j < n && m; j++)
  			if (color[i] != color[j] && !used[i] && !used[j]) {
  				printf("%d %d\n", i+1, j+1);
  				used[i] = used[j] = g[i][j] = 1;
  				m--;
  			}

  	for (int i = 0; i < n; i++)
  		for (int j = i+1; j < n && m; j++)
  			if (color[i] != color[j] && (!used[i] || !used[j]) && !g[i][j]) {
  				printf("%d %d\n", i+1, j+1);
  				used[i] = used[j] = g[i][j] = 1;
  				m--;
  			}

  	for (int i = 0; i < n; i++)
  		for (int j = i+1; j < n && m; j++)
  			if (color[i] != color[j] && !g[i][j]) {
  				printf("%d %d\n", i+1, j+1);
  				used[i] = used[j] = g[i][j] = 1;
  				m--;
  			}


    TIMESTAMP(end);
    return 0;
}