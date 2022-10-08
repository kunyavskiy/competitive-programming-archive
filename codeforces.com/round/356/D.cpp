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

const int MAXN = 410;

int g0[MAXN][MAXN];
int g[MAXN][MAXN];
int cnt[MAXN][MAXN][3];
int cntd[MAXN][MAXN];
int deg[MAXN];
int n;

int probd[MAXN][MAXN];

double solve(vector<int> vs) {
    int total = 0;
    for (int v : vs) {
        total += deg[v];
    }
    for (int v : vs) {
        for (int i = 0; i < n; i++) {
            int dist = g[v][i];
            for (int j = 0; j <= 2; j++) {
                int ndist = dist + j - 1;
                if (ndist >= 0) {
                    probd[i][ndist] += cnt[v][i][j];
                } else {
                    assert(cnt[v][i][j] == 0);
                }
            }
        }
    }
    double ans = 0;
    for (int i = 0; i < n; i++) {
        double cur = 0;
        for (int v : vs) {
            int dist = g[v][i];
            for (int j = 0; j <= 2; j++) {
                int ndist = dist + j - 1;
                if (ndist < 0) continue;
                if (cntd[i][ndist]) {
                    cur += probd[i][ndist] * 1.0 / cntd[i][ndist] / total;
                } else {
                    assert(probd[i][ndist] == 0);
                }
                probd[i][ndist] = 0;
            }
        }
        ans = max(ans, cur);
    }
    assert(ans < 1.0);
    return ans;
}

int main() {
#ifdef LOCAL
    assert(freopen(TASKNAME".in", "r", stdin));
    assert(freopen(TASKNAME".out", "w", stdout));
#endif

    int m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g[i][j] = n * (i != j);
        }
    }
    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a][b] = g[b][a] = 1;
        g0[a][b] = g[b][a] = 1;
        deg[a]++;
        deg[b]++;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!g0[i][j]) continue;
            for (int k = 0; k < n; k++) {
                assert(abs(g[i][k] - g[j][k]) <= 1);
                cnt[i][k][g[j][k] - g[i][k] + 1]++;
            }
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cntd[i][g[i][j]]++;
        }

    double ans = 0;

    for (int i = 0; i < n; i++) {
        double cur = 0;
        for (int d = 0; d < n; d++) {
            vector<int> v;
            for (int j = 0; j < n; j++)
                if (g[i][j] == d) {
                    v.push_back(d);
                }
            if (v.empty()) continue;
            cur += max(1.0 / v.size(), solve(v)) * (v.size() * 1.0 / n);
        }
        ans = max(ans, cur);
    }

    printf("%.10f\n", ans);
    return 0;
}
