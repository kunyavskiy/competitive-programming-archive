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
#include <stdarg.h>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if (_WIN32 || __WIN32__)
    #define LLD "%I64d"
#else
#define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "A"
#define TASKMOD "small"

typedef long long ll;
typedef long double ld;


int _solved, _testNum;

class AbstractSolver {
    char *_ob;
    int _ob_pos;
    const int _buffer_size = 16 * (1 << 20);
public:
    int _testId;

    AbstractSolver(int _testId) : _testId(_testId) {
        _ob = (char *) malloc(_buffer_size + 10);
        _ob_pos = 0;
        printf("Case #%d: ", _testId);
    }

    __attribute__((format(printf, 2, 3)))
    void printf(const char *format, ...) {
        va_list ap;
        va_start (ap, format);
        _ob_pos += vsnprintf(_ob + _ob_pos, _buffer_size - _ob_pos, format, ap);
        va_end (ap);
        assert(_ob_pos < _buffer_size - 10);
    }

    virtual void write() {
        _ob[_ob_pos] = 0;
        ::printf("%s", _ob);
    }

    virtual void solve() = 0;;
    virtual void read() = 0;

    void run() {
        solve();
#pragma omp critical 
        {
            _solved++;
            if ((_solved - 1) * 100 / _testNum != _solved * 100 / _testNum || _solved <= 20 || _testNum - _solved <= 20)
                TIMESTAMPf("%d%% of tests solved (%d/%d, %d more)", _solved * 100 / _testNum, _solved, _testNum,
                           _testNum - _solved);
        }
    }
};


void PreCalc() {
}

class Solver : public AbstractSolver {
public:
    Solver(int _testId) : AbstractSolver(_testId) { }

    vector<vector<int>> g;
    vector<int> sal;
    int n, d;

    void read() {
        scanf("%d%d",&n,&d);
        sal.resize(n);
        g.resize(n);
        scanf("%d",&sal[0]);
        int as, cs, rs;
        scanf("%d%d%d",&as,&cs,&rs);
        for (int i = 1; i < n; i++){
            sal[i] = (int) ((as * 1LL * sal[i-1] + cs) % rs);
        }
        int m0, am, cm, rm;
        scanf("%d%d%d%d",&m0, &am, &cm, &rm);
        for (int i = 1; i < n; i++){
            m0 = (int) ((m0 * 1LL * am + cm) % rm);
            g[m0 % i].push_back(i);
        }
    }

    vector<int> state;
    vector<int> in;

    int ans;
    int cur;

    void dfs_add(int v) {
        assert(state[v] == 1);
        if (in[v]) cur++;
        if (!in[v]) return;
        for (int u : g[v]){
            assert(state[u] != 1);
            if (state[u] == 0){
                state[u] = 1;
                dfs_add(u);
            }
        }
    }

    void dfs_remove(int v){
        if (in[v] && state[v] == 1) cur--;
        if (state[v] == 2) return;
        state[v] = 2;
        for (int u : g[v]){
            dfs_remove(u);
        }
    }

    void add(int v){
        assert(!in[v]);
        in[v] = true;
        if (state[v] == 1) {
            dfs_add(v);
            return;
        }
    }
    void remove(int v){
        assert(in[v]);
        if (state[v] == 1){
            dfs_remove(v);
        }
        in[v] = false;
        state[v] = 2;
    }

    void solve() {
        state.resize(n);
        state[0] = 1;
        in.resize(n);
        cur = 0;
        vector<pair<int, int>> v;
        for (int i = 0; i < n; i++)
            v.push_back(mp(sal[i], i));
        sort(v.begin(), v.end());
        int ptr = 0;
        cur = ans = 0;
        for (int i = 0; i < n; i++) {
            while (ptr < n && v[ptr].first - v[i].first <= d){
                add(v[ptr++].second);
                ans = max(ans, cur);
            }
            remove(v[i].second);
        }
        printf("%d\n", ans);
    }

};

int main() {
    freopen(TASKNAME "-" TASKMOD".in", "r", stdin);
    freopen(TASKNAME "-" TASKMOD".out", "w", stdout);

    PreCalc();
    TIMESTAMP(PreCalc);

    char buf[1000];
    fgets(buf, sizeof buf, stdin);
    sscanf(buf, "%d", &_testNum);

    vector<Solver *> solvers(_testNum);

    for (int i = 0; i < _testNum; i++) {
        solvers[i] = new Solver(i + 1);
        solvers[i]->read();
    }

//#pragma omp parallel for
    for (int i = 0; i < _testNum; i++) {
        solvers[i]->run();
    }

    for (int i = 0; i < _testNum; i++) {
        solvers[i]->write();
    }

    TIMESTAMP(end);
    return 0;
}
