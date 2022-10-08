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


int r, c, k;

struct myList {
    vector<int> next;
    vector<int> prev;
    vector<int> nextk;
    vector<int> pos;

    int result;

    int getval(int i) {
        if (prev[i] != i && next[i] != i) {
            return (pos[i] - pos[prev[i]]) * (c - pos[nextk[i]]);
        }
        return 0;
    }

    myList(vector<int> _pos) : pos(_pos) {
        pos.push_back(c);
        pos.push_back(-1);
        vector<int> order(pos.size());
        for (int i = 0; i < (int)order.size(); i++)
            order[i] = i;
        sort(order.begin(), order.end(), [&](int a, int b) { return pos[a] < pos[b];});
        next.resize(pos.size());
        prev.resize(pos.size());
        nextk.resize(pos.size());

        for (size_t i = 0; i + 1 < pos.size(); i++) {
            next[order[i]] = order[i+1];
            prev[order[i+1]] = order[i];
        }

        prev[order[0]] = order[0];
        next[order.back()] = order.back();

        result = 0;
        for (int i = 0; i < (int)pos.size(); i++) {
            nextk[i] = i;
            for (int j = 1; j < k; j++) {
                nextk[i] = next[nextk[i]];
            }
            result += getval(i);
        }
    }

    void remove(int id) {
        result -= getval(id);
        result -= getval(next[id]);
        int p = id;
        for (int i = 1; i < k; i++) {
            p = prev[p];
            result -= getval(p);
        }
        int from = next[id];
        next[prev[id]] = next[id];
        prev[next[id]] = prev[id];
        result += getval(from);
        p = from;
        for (int i = 1; i < k; i++) {
            p = prev[p];
            nextk[p] = next[nextk[p]];
            result += getval(p);
        }
    }
};


struct cell {
    int x, y, id;
};

int main() {
#ifdef LOCAL
    assert(freopen(TASKNAME".in", "r", stdin));
    assert(freopen(TASKNAME".out", "w", stdout));
#endif

    int n;
    scanf("%d%d%d%d",&r,&c, &n,&k);

    vector<cell> v(n);
    for (auto& c : v) {
        scanf("%d%d", &c.x, &c.y);
        --c.x;
        --c.y;
    }

    sort(v.begin(), v.end(), [](const cell& a, const cell& b) { return a.y < b.y;});

    for (int i = 0; i < n; i++)
        v[i].id = i;

    vector<cell> xv = v;
    sort(xv.begin(), xv.end(), [](const cell& a, const cell& b) { return a.x < b.x;});

    long long ans = 0;

    for (int i = 0; i < r; i++) {
        vector<int> pos;
        for (int j = 0; j < (int)v.size(); j++) {
            if (v[j].x < i) continue;
            v[j].id = (int)pos.size();
            pos.push_back(v[j].y);
        }
        myList list(pos);
        ans += list.result;

        int ptr = (int)xv.size() - 1;
        for (int j = r - 1; j > i; j--) {
            while (ptr >= 0 && xv[ptr].x == j) {
                list.remove(v[xv[ptr].id].id);
                ptr--;
            }
            ans += list.result;
        }
    }

    printf("%lld\n", ans);
    return 0;
}
