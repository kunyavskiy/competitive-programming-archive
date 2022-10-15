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

#define TASKNAME "LEBAMBOO"

#ifdef LOCAL
static struct __timestamper {
	~__timestamper(){
        TIMESTAMP(end);
	}
} __TIMESTAMPER;
#endif

typedef long long ll;
typedef long double ld;

int n;
int h[55];
int d[55];

void solve(){
	scanf("%d",&n);
	for (int i = 0; i < n; i++)
		scanf("%d",&h[i]);
	for (int i = 0; i < n; i++)
		scanf("%d",&d[i]);

	if (n == 1){
		if (h[0] > d[0])
			printf("%d\n", h[0] - d[0]);
		else
			printf("-1\n");
		return;
	}

	if (n == 2){
		if (h[0] + h[1] == d[0] + d[1])
			printf("%d\n", abs(h[0] - d[0]));
		else
			printf("-1\n");
		return;
	}

	int total = 0;
	for (int i = 0; i < n; i++)
		total += d[i] - h[i];
//	eprintf("%d\n", total);
	if (total % (n - 2) != 0 || total < 0){
		printf("-1\n");
		return;
	}


	int need = 0;

	for (int i = 0; i < n; i++){
		h[i] += total / (n-2);
		if (h[i] % 2 != d[i] % 2 || h[i] < d[i]){
			printf("-1\n");
			return;
		}
		need += (h[i] - d[i]) / 2;
	}

	if (need != total / (n-2))
		printf("-1\n");
	else
		printf("%d\n", need);
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