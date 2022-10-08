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


int main() {
#ifdef LOCAL
    assert(freopen(TASKNAME".in", "r", stdin));
    assert(freopen(TASKNAME".out", "w", stdout));
#endif

    int n, A, cf, cm;
    long long m;
    scanf("%d %d %d %d %lld", &n, &A, &cf, &cm, &m);

    vector<pair<ll, int> > cur(n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &cur[i].first);
        cur[i].second = i;
    }

    sort(cur.begin(), cur.end());

    long long answer = 0;

    int to_max = n - 1;
    long long cost_max = 0;
    while (to_max >= 0 && cost_max + (A - cur[to_max].first) <= m) {
        cost_max += A - cur[to_max].first;
        to_max--;
    }
    to_max++;

    int ans_val = 0;
    answer = max(answer, (n - to_max) * 1LL * cf + cur[0].first * 1LL * cm);

    long long cost_min = 0;

    for (int i = 1; i < n; i++) {
        cost_min += (cur[i].first - cur[i - 1].first) * 1LL * i;
        while (cost_min + cost_max > m && to_max < n) {
            cost_max -= (A - cur[to_max].first);
            to_max++;
        }
        if (cost_min + cost_max <= m) {
            ll nans = (n - to_max) * 1LL * cf + cur[0].first * 1LL * cm;
            if (answer < nans) {
                answer = nans;
                ans_id = i;
            }
        }
    }

    printf("%lld\n", answer);
    for (int i = 0; i < n; i++) {
        ll dlt = max(0LL, ans_val - cur[i].first);
        m -= dlt;
        cur[i].first += dlt;
    }
    for (int i = n - 1; i >= 0; i--) {
        ll dlt = min(m, A - cur[i].first);
        m -= dlt;
        cur[i].first += dlt;
    }
    sort(cur.begin(), cur.end(), [](const pair<int,int>& a, const pair<int, int>& b) { return a.second < b.second;});
    for (int i = 0; i < n; i++)
        printf("%lld%c", cur[i].first, " \n"[i == n-1]);
    return 0;
}