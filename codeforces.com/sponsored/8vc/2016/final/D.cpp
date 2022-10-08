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

#define TASKNAME "D"

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

const int MAXN = 210000;

vector<int> g[MAXN];
int n, k;

int cnt[MAXN];
int max_path[MAXN];
bool will_lose[MAXN];

bool ok = false;
int cost[MAXN];

void update_smax(int temp, int vtemp, int& maxv, int& vmaxv, int& smaxv) {
    if (temp > maxv) {
        swap(temp, maxv);
        swap(vtemp, vmaxv);
    }
    if (temp > smaxv) {
        swap(smaxv, temp);
    }
}

void dfs(int v, int lim, int p) {
    for (int u : g[v])
        if (u != p)
            dfs(u, lim, v);

    if (cost[v] < lim) {
        will_lose[v] = 1;
        max_path[v] = 0;
        cnt[v] = 0;
        return;
    }

    will_lose[v] = 0;
    cnt[v] = 1;
    max_path[v] = 0;
    int max_cnt, vmax_cnt, smax_cnt;
    max_cnt = smax_cnt = 0;
    vmax_cnt = -1;
    int lmax_path, vmax_path, smax_path;
    lmax_path = smax_path = 0;
    vmax_path = -1;



    for (int u : g[v])
        if (u != p) {
            if (!will_lose[u]) {
                cnt[v] += cnt[u];
            } else {
                will_lose[v] = 1;

                update_smax(cnt[u], u, max_cnt, vmax_cnt, smax_cnt);
                update_smax(max_path[u], u, lmax_path, vmax_path, smax_path);
            }
        }

    max_path[v] = lmax_path + cnt[v];

    if (vmax_cnt != vmax_path) {
      if (cnt[v] + lmax_path + max_cnt >= k) ok = true;
    }
    if (cnt[v] + lmax_path + smax_cnt >= k) ok = true;
    if (cnt[v] + smax_path + max_cnt >= k) ok = true;

    cnt[v] += max_cnt;
}

int main() {
#ifdef LOCAL
    assert(freopen(TASKNAME".in", "r", stdin));
    assert(freopen(TASKNAME".out", "w", stdout));
#endif

    scanf("%d%d",&n, &k);

    for (int i = 0; i < n; i++)
        scanf("%d", &cost[i]);

    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d%d",&a, &b);
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int l = 0;
    int r = 1111111;

    while (r - l > 1) {
        int m = (l + r) / 2;
        ok = false;
        dfs(0, m, -1);
        if (ok)
            l = m;
        else
            r = m;
    }

    printf("%d\n", l);


    return 0;
}
