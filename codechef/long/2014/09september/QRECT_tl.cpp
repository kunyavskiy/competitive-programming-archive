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

#define TASKNAME "QRECT"

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
typedef unsigned long long ull;
     
const int MAXN = 110000;

int rx1[MAXN];
int rx2[MAXN];
int ry1[MAXN];
int ry2[MAXN];
bool used[MAXN];

bool inter(int a, int b, int c, int d){
	return max(a, c) <= min(b, d);
}


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif
    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; i++) {
    	char c;
    	int x1, y1, x2, y2;
    	scanf(" %c", &c);
    	if (c == 'Q') {
    		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
    		int ans = 0;
    		for (int j = 0; j < i; j++)
    			if (used[j] && inter(x1, x2, rx1[j], rx2[j]) && inter(y1, y2, ry1[j], ry2[j])) {
    				ans++;
    			}
    		printf("%d\n", ans);
    	} else if (c == 'I') {
    		scanf("%d%d%d%d",&rx1[i],&ry1[i],&rx2[i],&ry2[i]);
    		used[i] = true;
    	} else if (c == 'D') {
    		scanf("%d",&x1);
    		used[x1-1] = false;
    	}
    }
  	
    return 0;
}