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

#define TASKNAME "UASEQ"

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


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  	int n, k;
  	scanf("%d%d",&n,&k);
  	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		scanf("%d",&a[i]);
	}

	pair<ll, ll> res = mp(1e18+1, 1e18+1);

	for (int i = 0; i < k + 2 && i < n; i++)
		for (int j = i+1; j < k+2 && j < n; j++) {
			if ((a[j] - a[i]) % (j - i) != 0) continue;
			ll d = (a[j] - a[i]) / (j - i);
			ll b = a[i] - d * i;
			int err = 0;
			for (int q = 0; q < n && err <= k; q++)
				if (a[q] != b + d * q)
					err++;
			if (err > k) continue;
			res = min(res, mp(b, d));
		}
	for (int i = 0; i < n; i++)
		printf(LLD" ", res.first + res.second * i);
	printf("\n");
      
    return 0;
}