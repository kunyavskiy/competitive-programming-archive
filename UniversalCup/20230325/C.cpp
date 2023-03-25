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

char s[1'100'000];
char t[1'100'000];

int main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
#endif

    int tst;
    scanf("%d", &tst);
    while (tst-- > 0) {
        int n;
        scanf("%d", &n);
        scanf("%s", s);
        scanf("%s", t);

        int ops = 0;

        auto get = [&](int id) {
            if (id < 0 || id >= n) return 0;
            return (s[id] != t[id]) ? 1 : 0;
        };

        for (int i = 0; i <= n; i++) {
            if (get(i-1) != get(i)) {
                ops++;
            }
        }

        eprintf("ops = %d\n", ops);

        long long res = 0;
        switch (ops) {
            case 0: res = n * 1LL * (n + 1) / 2; break;
            case 2: res = 2 * (n - 1); break;
            case 4: res = 6; break;
            default: res = 0; break;
        }

        printf("%lld\n", res);
    }

    return 0;
}
