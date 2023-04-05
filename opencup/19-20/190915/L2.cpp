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

map<vector<int>, int> g;

int calc(vector<int> a);

void bt2(vector<int> a, vector<int> b, vector<int> &gg) {
  if (a.size() == b.size()) {
    int n = a.size();
    int r = 0;
    for (int x = 1; x < (1 << n); x++) {
      vector<int> c(n);
      bool ok = true;
      for (int i = 0; i < n; i++) {
        if (x & (1 << i)) c[i] = b[i]; else c[i] = a[i];
        if (c[i] == 0) ok = false;
      }
      if (ok)
      r ^= calc(c);
    }
    gg[r] = true;
    return;
  }
  for (int x = 0; x < a[b.size()]; x++) {
    b.push_back(x);
    bt2(a, b, gg);
    b.pop_back();
  }
}

int calc(vector<int> a) {
  sort(a.begin(), a.end());
  if (g.count(a)) {
    return g[a];
  }
  vector<int> gg(257);
  vector<int> b;
  bt2(a, b, gg);
  int i = 0;
  while (gg[i]) i++;
  g[a] = i;

  if (a.size() > 2) {
    int c = a[0];
    for (int j = 1; j < (int)a.size(); j++) {
      c = calc({c, a[j]});
    }
    assert(i == c);
  }

  return i;
}

void bt(vector<int> a, int n) {
  if (n == 0) {
    for (int x : a) {
      cout << x;
    }
    cout << ": " << calc(a) << "\n";
    return;
  }
  for (int x = 1; x <= 31; x++) {
    if (a.size() > 0 && x < a.back()) continue;
    a.push_back(x);
    bt(a, n - 1);
    a.pop_back();
  }
}

int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l2.out", "w", stdout);
#endif

//  for (int n = 2; n <= 2; n++) {
//    vector<int> a;
//    bt(a, n);
//  }

  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 32; j++) {
      cout << calc({i, j}) << " ";
    }
    cout << "\n";
  }

  return 0;
}
