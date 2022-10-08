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
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ((_WIN32 || __WIN32__) && __cplusplus < 201103L)
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "B"

#ifdef LOCAL

static struct __timestamper {
    string what;

    __timestamper(const char *what) : what(what) { };

    __timestamper(const string &what) : what(what) { };

    ~__timestamper() {
        TIMESTAMPf("%s", what.data());
    }
} __TIMESTAMPER("end");

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

ll A;

ll get_minval(vector<pair<ll, ll>>& cur, vector<ll>& psum, ll& r, ll n, ll m) {
    while (r > 0) {
        ll id = r - 1;
        ll mid = cur[id].first;
        if (mid * id - psum[id] <= m)
            break;
        else
            r--;
    }
    ll limit = (r == n) ? A : cur[r].first;
    return (int) (min(limit, (m + psum[r]) / r));
}


int main() {
#ifdef LOCAL
    assert(freopen(TASKNAME".in", "r", stdin));
    assert(freopen(TASKNAME".out", "w", stdout));
#endif

    ll n, cf, cm, m;
    scanf("%lld %lld %lld %lld %lld", &n, &A, &cf, &cm, &m);

    vector<pair<ll, ll> > cur(n);
    for (int i = 0; i < n; i++) {
        int temp;
        scanf("%d", &temp);
        cur[i].first = temp;
        cur[i].second = i;
    }

    sort(cur.begin(), cur.end());


    vector<ll> psum(n+1);
    for (int i = 0; i < n; i++){
        psum[i + 1] = psum[i] + cur[i].first;
    }

    ll r = n;

    ll ans_val = get_minval(cur, psum, r, n, m);
    ll answer = ans_val * cm;


    if (m + psum[n] >= n * A) {
        ans_val = A;
        answer = n * cf + A * cm;
    } else {
        ll mbak = m;
        for (ll i = n - 1; i >= 0; i--) {
            m -= A - cur[i].first;
            if (m < 0) break;
            r = min(r, i);
            ll cur_val = i == 0 ? A : get_minval(cur, psum, r, i, m);
            ll cur_ans = cur_val * cm + (n - i) * cf;
            if (cur_ans > answer) {
                answer = cur_ans;
                ans_val = cur_val;
            }
        }

        m = mbak;
    }

    printf("%lld\n", answer);
    for (ll i = 0; i < n; i++) {
        ll dlt = max(0LL, ans_val - cur[i].first);
        m -= dlt;
        cur[i].first += dlt;
    }
    for (ll i = n - 1; i >= 0; i--) {
        ll dlt = min(m, A - cur[i].first);
        m -= dlt;
        cur[i].first += dlt;
    }
    sort(cur.begin(), cur.end(), [](const pair<ll,ll>& a, const pair<ll, ll>& b) { return a.second < b.second;});
    for (ll i = 0; i < n; i++)
        printf("%d ", (int)cur[i].first);
    return 0;
}
