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

#define TASKNAME "F"

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


int solve_max(int n, const vector<int> &c, int k) {
    int odd_cycles = 0;
    for (int x : c) {
        odd_cycles += x % 2;
    }
    int two = (n - odd_cycles) / 2;
    int one = n - 2 * two;

    int ans = 0;
    ans += 2 * min(k, two);
    k -= min(k, two);
    ans += min(k, one);
    return ans;
}

const int MAXN = 1000000;

int dp[MAXN];
int ndp[MAXN];

void add_dp(int v, int cnt, int tot) {
    int d = v * (cnt + 1);
    for (int i = 0; i < v; i++) {
        int val = 0;
        for (int j = i; j <= tot; j += v) {
            val += dp[j];
            if (j >= d) val -= dp[j - d];
            ndp[j] = val > 0;
        }
    }
    for (int i = 0; i <= tot; i++) {
        dp[i] |= ndp[i];
    }
}

int solve_min(vector<int> c, int k) {
    sort(c.begin(), c.end());
    dp[0] = 1;
    int tot = 0;
    for (int i = 0; i < (int)c.size(); ) {
        int j = i;
        while (j < (int)c.size() && c[i] == c[j]) j++;
        add_dp(c[i], j - i, tot += (j - i) * c[i]);
        i = j;
    }
    return dp[k] == 1 ? k : k + 1;
}

int main() {
#ifdef LOCAL
    assert(freopen(TASKNAME".in", "r", stdin));
    assert(freopen(TASKNAME".out", "w", stdout));
#endif

    int n, k;
    scanf("%d %d", &n, &k);
    vector<int> p(n);
    for (int& x : p) {
        scanf("%d", &x);
        --x;
    }

    vector<int> cycles;
    vector<bool> used(n);
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        int c = 0;
        for (int j = i; !used[j]; j = p[j]) {
            c++;
            used[j] = true;
        }
        cycles.push_back(c);
    }

    printf("%d %d\n", solve_min(cycles, k), solve_max(n, cycles, k));


    return 0;
}
