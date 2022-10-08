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

const int MOD = 1000000007;

void add(int& a, int b) {
    if ((a += b) >= MOD) a -= MOD;
}

int mult(int a, int b) {
    return (int) ((a * 1LL * b) % MOD);
}

int pow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = mult(res, a);
        a = mult(a, a);
        b >>= 1;
    }
    return res;
}

int inv(int a) {
    return pow(a, MOD - 2);
}

const int MAXN = 30010;

int f[MAXN];
int invf[MAXN];

int cnk(int n, int k) {
    if (n < k) return 0;
    return mult(f[n], mult(invf[k], invf[n-k]));
}

vector<int> dp[MAXN];

void solve(int n, int k) {
    if (dp[n].size()) {
        assert((int)dp[n].size() == k + 1);
        return;
    }
    if (n == 1) {
        dp[n].resize(k+1);
        for (int i = 1; i <= k; i++) {
            dp[n][i] = cnk(k, i);
        }
        return;
    }
    int n1 = n/2;
    int n2 = n - n1;
    solve(n1,k);
    solve(n2,k);
}

int main() {
#ifdef LOCAL
    assert(freopen(TASKNAME".in", "r", stdin));
    assert(freopen(TASKNAME".out", "w", stdout));
#endif

    f[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        f[i] = mult(f[i - 1], i);
    }
    for (int i = 0; i < MAXN; i++) {
        invf[i] = inv(f[i]);
    }

    ll n;
    int k;
    scanf(LLD "%d",&n,&k);
    if (n > k) {
        printf("0\n");
        return 0;
    }

    solve(n, k);

    assert((int)dp[n].size() == k + 1);

    int ans = 0;
    for (int i = 0; i <= k; i++) {
        add(ans, mult(dp[n][i], cnk(k, i)));
    }

    return 0;
}
