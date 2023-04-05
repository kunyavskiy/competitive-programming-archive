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
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

vector<int> p;
vector<char> b;
vector<char> s;
vector<int> pr;
vector<int> nm;

ll res;

void go(int l, int r, int len) {
  if (r - l < 2)
    return;

//  for (int i = 0; i < len; i++) {
//    cout << b[i];
//  }
//  cout << " " << (r - l) << "\n";
//  for (int i = l; i < r; i++) {
//    cout << p[i] << " ";
//  }
//  cout << "\n";

  nm.push_back(r - l);

  if (len == 0) {
    pr.push_back(-1);
  } else {
    int k = pr[len - 1];
    while (k >= 0 && b[k] != b[len - 1]) {
      k = pr[k];
    }
    pr.push_back(k + 1);
  }

  if (len > 0) {
    ll nn = nm[len];
    res += nn * (nn - 1) / 2 * (len - pr[len]);
  }

//  cout << "!!! " << len << " " << pr[len] << " " << res << "\n";

  int m = l;
  for (int i = l; i < r; i++) {
    int x = p[i];
    if (x + len == (int) s.size()) {
      swap(p[i], p[r - 1]);
      r--; i--;
    } else {
      if (s[x + len] == 'a') {
        swap(p[i], p[m]);
        m++;
      }
    }
  }

  b.push_back('a');
  go(l, m, len + 1);
  b.pop_back();
  b.push_back('b');
  go(m, r, len + 1);
  b.pop_back();

  nm.pop_back();
  pr.pop_back();
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);

//  vector<bool> z(1000000007);
//  for (int i = 0; i < 1000000007; i++) {
//    if (!z[i]) {
//      int c = 0;
//      int j = i;
//      while (!z[j]) {
//        z[j] = true;
//        c++;
//        j = (int)((j * 13331ll + 23333ll) % 1000000007ll);
//      }
//      cout << c << " " << i << "\n";
//    }
//  }

#endif

  int n, seed;
  scanf("%d%d", &n, &seed);

  if (seed == 791372847) {
    for (ll len = 1; len < n; len++) {
      res += len * (n - len);
    }
    cout << res << "\n";
    return 0;
  }

  s.resize(n);
  for (int i = 0; i < n; i++) {
    seed = (int) ((seed * 13331ll + 23333ll) % 1000000007ll);
    s[i] = 'a' + (seed & 1);
  }

//  for (int i = 0; i < n; i++) {
//    cout << s[i];
//  }
//  cout << "\n";

  p.resize(n);
  for (int i = 0; i < n; i++) {
    p[i] = i;
  }

  go(0, n, 0);
  cout << res << "\n";

  return 0;
}
