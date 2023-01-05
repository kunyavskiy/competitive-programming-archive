#include <iostream>
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
#include <numeric>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


using namespace std;

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

void add(int &a, int b) {
    if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
    if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
    return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

int minv(int x) {
    return mpow(x, MOD - 2);
}

#ifdef LOCAL
const int MAXN = 5'100;
#else
const int MAXN = 5'100'000;
#endif
int invv[MAXN];
int fs[MAXN];
int ifs[MAXN];

int cnk(int n, int k) {
    if (n < 0 || k > n) return 0;
    return mul(fs[n], mul(ifs[n - k], ifs[k]));
}

int ord(int a, int b) {
    return cnk(a + b, b);
}

int solve_inc_right(int n, int pos, int val) {

}
int solve_inc_left(int, int, int) {
    return 0;
}
int solve_inc(int n, int pos, int val) {
    int ans = 0;
    if (pos != n - 1) add(ans, solve_inc_right(n, pos, val));
    if (pos != 0) add(ans, solve_inc_left(n, pos, val));
    return ans;
}

int solve_both(int n, int pos, int val) {
    int ans = 0;
    int small = val;
    int large = n - val - 1;
    for (int small_inc = 0; small_inc <= val; small_inc++) {
        int large_dec = pos - small_inc;
        int cur = 1;
        cur = mul(cur, cnk(val, small_inc));
        cur = mul(cur, cnk(large, large_dec));
        cur = mul(cur, ord(small_inc, large_dec));
        cur = mul(cur, ord(small - small_inc, large - large_dec));
        add(ans, cur);
    }
    eprintf("both(%d, %d, %d) = %d\n", n, pos, val, ans);
    return ans;
}

vector<int> find_all_inc(vector<int> v, bool dec) {
    vector<int> res;
    int n = v.size();
    for (int i = 0; i < (1 << n); i++) {
        int l = dec ? n : -1;
        bool is_inc = true;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                if ((v[j] > l) ^ dec) {
                    l = v[j];
                } else {
                    is_inc = false;
                }
            }
        }
        if (is_inc) {
            if (res.empty() || __builtin_popcount(i) > __builtin_popcount(res.back())) {
                res.clear();
            }
            if (res.empty() || __builtin_popcount(i) >= __builtin_popcount(res.back())) {
                res.push_back(i);
            }
        }
    }
    return res;
}

void check(int n) {
    vector<int> v(n);
    std::iota(v.begin(), v.end(), 0);
    do {
        vector<int> inc = find_all_inc(v, false);
        vector<int> dec = find_all_inc(v, true);
        if (__builtin_popcount(inc.back()) + __builtin_popcount(dec.back()) != n + 1) continue;
        assert(inc.size() == 1 || dec.size() == 1);
        int count = 0;
        for (int x : v) printf("%d ", x);
        printf(":");
        for (int i : inc) printf("%d ", i);
        printf("|");
        for (int i : dec) printf("%d ", i);
        printf("\n");
        fflush(stdout);
        for (int a : inc) {
            for (int b : dec) {
                assert(__builtin_popcount(a & b) == 1);
                int pos = __builtin_ctz(a & b);
                if (pos != n - 1 && v[pos + 1] == v[pos] + 1) continue;
                if (pos != n - 1 && v[pos + 1] == v[pos] - 1) continue;
                count++;
            }
        }
        assert(count == 1);
    } while(next_permutation(v.begin(), v.end()));
}

int main() {
#ifdef LOCAL
    freopen("f.in", "r", stdin);
    freopen("f.out", "w", stdout);
#endif

    //check(6);
    //return 0;


    invv[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        invv[i] = mul(MOD - invv[MOD % i], MOD / i);
        assert(mul(i, invv[i]) == 1);
    }
    fs[0] = 1;
    ifs[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fs[i] = mul(fs[i - 1], i);
        ifs[i] = mul(ifs[i - 1], invv[i]);
    }

    int n, pos, val;
    while (scanf("%d%d%d", &n, &pos, &val) == 3) {
        int ans = 0;
        add(ans, solve_inc(n, pos - 1, val - 1));
        add(ans, solve_inc(n, pos - 1, n - val));
        int both = 0;
        add(both, solve_both(n, pos - 1, val - 1));
        if (val != n) {
            sub(both, solve_both(n - 1, pos - 1, val - 1));
        }
        if (val != 1) {
            sub(both, solve_both(n - 1, pos - 1, val - 2));
        }
        eprintf("both_fixed(%d, %d, %d) = %d\n", n, pos, val, both);
        add(ans, both);
        printf("%d\n", ans);
    }

    return 0;
}
