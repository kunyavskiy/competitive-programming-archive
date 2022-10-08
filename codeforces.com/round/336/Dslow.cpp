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

const int MOD = 1000000007;

int mult(int a, int b) {
    return (int) ((a * 1LL * b) % MOD);
}


vector<vector<int>> g;
vector<int> v0;


int solve(int v) {
    int ans = v0[v];
    for (int u : g[v]) {
        ans = (ans + solve(u)) % MOD;
    }
    return mult(ans, g[v].size()+1);
}

int main() {
#ifdef LOCAL
    assert(freopen(TASKNAME".in", "r", stdin));
    assert(freopen(TASKNAME".out", "w", stdout));
#endif

    v0.resize(1);
    g.resize(1);
    int q;
    scanf("%d %d",&v0[0], &q);
    for (int i = 0; i < q; i++) {
        int ty;
        scanf("%d",&ty);
        if (ty == 1) {
            int p, v;
            scanf("%d%d",&p, &v);
            --p;
            v0.push_back(v);
            g[p].push_back(g.size());
            g.push_back(vector<int>());
        } else {
            int v;
            scanf("%d",&v);
            --v;
            printf("%d\n", solve(v));
        }
    }
    return 0;
}
