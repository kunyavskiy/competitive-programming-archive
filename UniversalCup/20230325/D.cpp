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

char s[2'100'000];
int c[2'100'000];
int a[2'100'000];
int b[2'100'000];

void solve() {
    int n, m;
    scanf("%d%d%s", &n, &m, s);
    int l = strlen(s);
    for (int i = 0; i < l; i++) {
        c[i] = s[i] - '0';
    }
    c[l] = -1;

    for (int start = 1; start < 10; start++) {
        int ptr = 0;
        auto feed = [&](int v) {
            eprintf("feed(%d)\n", v);
            if (c[ptr] == -1) return false;
            if (v < 10) {
                if (c[ptr] == v) {
                    ptr++;
                    return true;
                }
            } else {
                if (c[ptr] == v / 10 && c[ptr + 1] == v % 10) {
                    ptr += 2;
                    return true;
                }
            }
            return false;
        };
        auto next = [&](int v) {
            if (c[ptr] != 0 && c[ptr] < v) {
                return (c[ptr] * 10 + c[ptr + 1]) / v;
            } else {
                return c[ptr] / v;
            }
        };
        auto tryIt = [&] {
            a[0] = start;
            for (int i = 0; i < m; i++) {
                b[i] = next(a[0]);
                if (!feed(a[0] * b[i])) return false;
            }
            if (b[0] == 0) return false;
            for (int i = 1; i < n; i++) {
                a[i] = next(b[0]);
                for (int j = 0; j < m; j++) {
                    if (!feed(a[i] * b[j])) return false;
                }
            }
            return ptr == l;
        };
        if (tryIt()) {
            for (int i = 0; i < n; i++) printf("%d", a[i]);
            printf(" ");
            for (int i = 0; i < m; i++) printf("%d", b[i]);
            printf("\n");
            return;
        }
    }

    printf("Impossible\n");
}

int main() {
#ifdef LOCAL
    freopen("d.in", "r", stdin);
    freopen("d.out", "w", stdout);
#endif

    int t;
    scanf("%d", &t);
    while (t-- > 0) {
        solve();
    }

    return 0;
}
