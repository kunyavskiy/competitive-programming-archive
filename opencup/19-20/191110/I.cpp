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

void solve() {
  int n;
  scanf("%d", &n);
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  vector<string> v;
  for (int msk = 0; msk < 4; msk++) {
    string s;
    s.reserve(n);
    s += char('0' + (msk / 2));
    s += char('0' + (msk % 2));
    for (int i = 2; i < n; i++) {
      if (a[i - 1]) {
        s += s[i - 2];
      } else {
        s += char(s[i - 2] ^ 1);
      }
    }

    int l, r;
    l = r = -1;
    bool fail = false;
    for (int i = 0; i < n; i++) {
      int sz = 0;
      if (i <= r) {
        int sym = r + l - i;
        sz = min(a[sym], sym - l);
      }
      while (i - sz > 0 && i + sz < n - 1 && s[i - sz - 1] == s[i + sz + 1]) sz++;
      if (a[i] != sz) {
        fail = true;
        break;
      }
      if (i + sz >= r) {
        l = i - sz;
        r = i + sz;
      }
    }
    if (!fail) {
      v.emplace_back(std::move(s));
    }
  }
  printf("%d\n", (int)v.size());
  for (const string& s: v) {
    printf("%s\n", s.c_str());
  }
}

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0)
    solve();


  return 0;
}
