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

#define TASKNAME "HELPLIRA"

#ifdef LOCAL
static struct __timestamper {
	~__timestamper(){
		TIMESTAMP(end);
	}
} __TIMESTAMPER;
#endif

typedef long long ll;
typedef long double ld;


int read(){
	int x1,y1,x2,y2,x3,y3;
	scanf("%d %d %d %d %d %d",&x1,&y1,&x2,&y2,&x3,&y3);
	x2 -= x1, y2 -= y1;
	x3 -= x1, y3 -= y1;
	return abs(x2 * y3 - y2 * x3);
}

int v[110000];

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

    int n;
    scanf("%d",&n);
    int minv, maxv;
    minv = maxv = 0;
    for (int i = 0; i < n; i++){
    	v[i] = read();
    	if (v[i] <= v[minv]) minv = i;
    	if (v[i] >= v[maxv]) maxv = i;
    }

    printf("%d %d\n", minv+1, maxv+1);
    return 0;
}