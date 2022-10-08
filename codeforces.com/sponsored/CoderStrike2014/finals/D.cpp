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

#define TASKNAME "D"

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


const int MAXN = 1<<20;


int tree[4*MAXN + 10];
int lst;

void addval(int x, int val){
	x += lst;      
	for (; x; x /= 2)
		tree[x] += val;
}

int findkth(int k){
	int v = 1;
	while (v < lst) {
		v = 2*v;
		if (tree[v] <= k)
			k -= tree[v], v++;
	}
	return v - lst;
}

int prev[2*MAXN];
int val[2*MAXN];
bool used[2*MAXN];


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif
  	int n,m;
  	scanf("%d%d",&n,&m);

  	lst = 2;
  	while (lst < n + m) lst *= 2;
  	for (int i = m; i < n + m; i++)
  		addval(i, 1), prev[i] = -1, val[i] = -1;
  	for (int i = 0; i < m; i++)
  	    prev[i] = -1, val[i] = -1;
  	for (int i = 0; i < m; i++){
  		int x, y;
  		scanf("%d %d",&x, &y);
  		int pos = findkth(y - 1);
  		if (val[pos] != -1 && val[pos] != x) {
  			printf("-1\n");
  			return 0;
  		}
  		if (val[pos] == -1 && used[x]) {
  			printf("-1\n");
  			return 0;
  		}
  		used[x] = true;
  		val[pos] = x;
  		int p = m - i - 1;
  		prev[pos] = p;
		addval(pos, -1);
		addval(p, 1);
		val[p] = val[pos];
  	}

  	int ptr = 1;
  	for (int i = 0; i < n + m; i++)
  		if (prev[i] != -1) {
			assert(val[i] == -1 || val[i] == val[prev[i]]);
  			val[i] = val[prev[i]];
  		} else if (val[i] == -1) {
  			while (used[ptr]) ptr++;
  			val[i] = ptr;
  			used[ptr] = true;
  		}
     for (int i = m; i < n + m; i++)
     	printf("%d%c", val[i], " \n"[i==n+m-1]);
    return 0;
}