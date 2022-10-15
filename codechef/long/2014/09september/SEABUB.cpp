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

#define TASKNAME "SEABUB"

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
typedef double ld;


ld res[101][101*101];


void precalc(){
	res[0][0] = 1;
	for (int i = 1; i <= 100; i++) {
		ld cur = 0;
		for (int j = 0; j <= i*(i-1)/2; j++) {
			cur += res[i-1][j];
			if (i <= j) cur -= res[i-1][j-i];
			res[i][j] = cur / i;
		}
	}
}

void solve(){
	int n, k;
	ll _k;
	scanf("%d "LLD,&n,&_k);
	k = min(_k, (ll)1e9);
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		scanf("%d",&a[i]);
	int inv = 0;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (a[j] < a[i])
				inv++;
	if (inv <= k) {
		printf("%.10lf\n", 0.0);
		return;
	}
	if (k == 0) {
		printf("%.10lf\n", (double)inv);
		return;
	}
	vector<ld> prob(res[n], res[n] + n * (n - 1) / 2 + 1);

/*	prob[0] = 1;
	for (int i = 1; i <= n; i++) {
		vector<ld> oprob = prob;
		ld cur = 0;
		for (int j = 0; j < (int)prob.size(); j++) {
			cur += prob[j];
			if (i <= j) cur -= oprob[j-i];
			prob[j] = cur / i;
		}
	}*/

	ld ans = 0;
	for (int i = 0; i < (int)prob.size(); i++)
		ans += i * prob[i];
	ld start = prob[0];
	for (int i = 0; i < k-1; i++) {
		ld nans = 0;
		ld cur = start;
		for (int j = i+1; j < (int)prob.size(); j++)
			if (j - i - 1 < ans)
				nans += (j - i - 1) * prob[j], cur += prob[j];
			else {
				nans += ans * (1 - cur);
				break;
			}
		ans = nans;
		start += prob[i+1];
	}	
	printf("%.10lf\n", min(ans, (double)max(0, inv - k)));
}


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

    precalc();

    int t;
    scanf("%d",&t);
    for (int i = 0; i < t; i++)
    	solve();

    return 0;
}