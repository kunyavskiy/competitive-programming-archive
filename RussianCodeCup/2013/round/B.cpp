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

#define TASKNAME "B"

typedef long long ll;
typedef long double ld;

const int MAXN = 11000;

double value[MAXN];

int a[MAXN];
int n,m,k;
int p[25][MAXN];

void solve(){
	scanf("%d %d %d",&n,&m,&k);
	for (int i = 0; i < n; i++)
		value[i] = k;
	for (int i = 0; i < n; i++)
		scanf("%d",&a[i]);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d",&p[j][i]);

	for (int i = 0; i < m; i++){
		double best = 0;
		for (int j = 0; j < n; j++){
			value[j] = value[j] * (p[i][j]+100)/100.0;
			best = max(best, value[j] - a[j]);
		}
		if (i == m-1){
			printf("%.10lf\n",*max_element(value,value+n));
			return;
		}
		for (int j = 0; j < n; j++)
			value[j] = max(best - a[j], value[j]);
	}
	assert(false);
}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  	int tst;
  	scanf("%d",&tst);

  	for (int i = 0; i < tst; i++)
  		solve();
      
  TIMESTAMP(end);
  return 0;
}