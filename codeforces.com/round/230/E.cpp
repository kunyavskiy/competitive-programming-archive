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

#define TASKNAME "E"

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

ll dp1[410][410];
ll dp2[410][410];
ll dp3[410][410];


int v[410];
int w[410];
int n;

ll calc1(int l, int r);


ll calc2(int l, int r){
	ll& res = dp2[l][r];
	if (res != -1) return res;
	if (l == r) return res = 0;
	res = -1e9;
	if (w[l] == w[r]) return res;
	int dx = (w[l] > w[r]) ? -1 : 1;

	for (int j = l + 1; j <= r; j++)
		if (w[j] == w[l] + dx)
			res = max(res, calc1(l + 1, j - 1) + calc2(j, r));
	return res;
}



ll calc1(int l, int r){
	if (l > r) return 0;
	ll& res = dp1[l][r];
	if (res != -1) return res;
	if (l == r) return res = v[1];

	res = -1e9;

	for (int i = l; i < r; i++)
		res = max(res, calc1(l, i) + calc1(i+1, r));

	for (int i = l; i <= r; i++)
		if (w[i] >= w[l] && w[i] >= w[r] && (2*w[i] - w[l] - w[r] + 1 <= n)) {
			res = max(res, calc2(l, i) + calc2(i, r) + v[2 * w[i] - w[l] - w[r] + 1]);
		}
	return res;
}

ll calc3(int l, int r){
	if (l > r) return 0;
	ll& res = dp3[l][r];
	if (res != -1) return res;
	if (l == r) return res = max(0,v[1]);

	res = calc3(l+1, r);

	for (int i = l; i <= r; i++)
		res = max(res, calc1(l, i) + calc3(i+1, r));
	return res;
}




int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  	memset(dp1, -1, sizeof(dp1));
  	memset(dp2, -1, sizeof(dp2));
  	memset(dp3, -1, sizeof(dp3));


  	scanf("%d", &n);
  	for (int i = 0; i < n; i++)
  		scanf("%d", &v[i+1]);
  	for (int i = 0; i < n; i++)
  		scanf("%d", &w[i]);


  	printf(LLD"\n", calc3(0, n - 1));
    return 0;
}