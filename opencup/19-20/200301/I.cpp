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

const int MOD = 998244353;

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

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  string s;
  int d;
  while (cin >> s >> d) {
    map<vector<int>, int> dp;
    {
      vector<int> init;
      for (int i = 0; i <= (int)s.size(); i++) {
        init.push_back(i);
      }
      dp[init] = 1;
    }

    int ans = 0;
    while (!dp.empty()) {
      map<vector<int>, int> ndp;
      for (const auto& [st, cnt] : dp) {
        if (st.back() == d) {
          add(ans, cnt);
        }
        for (char c = 'A'; c <= 'Z'; c++) {
          vector<int> nst = st;
          for (int i = 0; i <= (int) s.size(); i++) {
            nst[i] = st[i] + 1;
            if (i) {
              nst[i] = min(nst[i], nst[i - 1] + 1);
            }
            if (i) {
              nst[i] = min(nst[i], st[i - 1] + 1);
            }
            if (i && s[i - 1] == c) {
              nst[i] = min(nst[i], st[i - 1]);
            }
          }
          if (*min_element(nst.begin(), nst.end()) <= d) {
            add(ndp[nst], cnt);
          }
        }
      }
      dp = std::move(ndp);
    }
    printf("%d\n", ans);

  }

  return 0;
}
