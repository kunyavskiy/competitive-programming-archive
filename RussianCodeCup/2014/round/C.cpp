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

#define TASKNAME "C"

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


const int MAXN = 100010;
const int MAGIC = 500;
//vector<int> divs[MAXN];
//bool have[MAXN];


bitset<100010> bs[2][MAGIC];

bool have[2][MAXN];

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
    eprintf("%d\n", sizeof(bs) / 1024 / 1024);
  #endif

/*  	for (int i = 1; i < MAXN; i++)
  		for (int j = i; j < MAXN; j += i)
  			divs[j].pb(i);*/

  	int n[2], H, C, k;
  	scanf("%d %d %d %d %d",&n[0],&n[1],&C,&H,&k);
  	for (int it = 0; it < 2; it++){
  		for (int i = 0; i < n[it]; i++){
  			int a;
  			scanf("%d",&a);
  			have[it][a] = 1;
  		}  			
  	}

  	for (int i = 1; i < MAGIC; i++)
  		for (int k = 1; k * i < MAXN; k++) {
  			if (have[0][i*k]) bs[0][i][k] = 1;
  			if (have[1][i*k]) bs[1][i][k] = 1;
  		}

  	for (int i = 0; i < k; i++){
  		int u, v;
  		scanf("%d %d",&v,&u);
  		ll C1 = C * 1LL* u - v;
  		ll C2 = H * 1LL* u - v;
  		if (C1 >= 0 || C2 <= 0) {
  			printf("NO\n");
  			continue;
  		}
  		C1 = -C1;
  		ll g = __gcd(C1, C2);
  		C1 /= g;
  		C2 /= g;
//  		eprintf("%I64d %I64d\n", C1, C2);
  		if (C1 > MAXN || C2 > MAXN) {
  			printf("NO\n");
  			continue;
  		}
  		int maxc = max(C1, C2);
  		bool found = false;
  		if (maxc < MAGIC) {
  			found = (bs[1][C1] & bs[0][C2]).any();
  		} else {
  			found = false;
  			for (int k = 1; k * maxc < MAXN; k++)
  				if (have[1][k * C1] && have[0][k * C2]) {
  					found = true;
  					break;
  				}
  		}
  		if (found)
			printf("YES\n");
		else
			printf("NO\n");
  	}

      
    return 0;
}