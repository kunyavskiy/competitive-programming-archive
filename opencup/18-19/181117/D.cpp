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
#include <bits/stdc++.h>

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

const ll LINF = 1e18;

void print(vector<ll> a) {
  for (ll x : a) printf("%lld ", x);
  printf("\n");
}

vector<ll> fast(int p, vector<pair<int, int>> a, int mx = 50) {
  vector<vector<int>> b(p);
  for (auto o : a) {
    b[o.first % p].push_back(o.second);
  }

  ll sum = 0;
  for (auto o : a) sum += o.second;
  int rem = 0;
  for (auto o : a) rem = (rem + o.first) % p;

  for (int i = 0; i < p; i++) {
    sort(b[i].begin(), b[i].end());
    if ((int)b[i].size() > mx) {
      b[i].resize(mx);
    }
  }

  vector<ll> mn(p, LINF);
  mn[0] = 0;
  for (int i = 0; i < p; i++) {
    vector<int> ind(p);
    iota(ind.begin(), ind.end(), 0);

    for (int x : b[i]) {
      vector<ll> nmn = mn;
      vector<int> nind;
      for (int j : ind) {
        int nj = (j + i) % p;
        if (nmn[nj] > mn[j] + x) {
          nmn[nj] = mn[j] + x;
          nind.push_back(nj);
        }
      }
      mn = nmn;
      ind = nind;
    }
  }

  vector<ll> ans(p);
  for (int i = 0; i < p; i++) {
    ans[i] = max(-1LL, sum - mn[(rem - i + p) % p]);
  }
  return ans;
}

vector<ll> slow(int p, vector<pair<int, int>> a) {
  vector<vector<int>> b(p);
  for (auto o : a) {
    b[o.first % p].push_back(o.second);
  }

  ll sum = 0;
  for (auto o : a) sum += o.second;
  int rem = 0;
  for (auto o : a) rem = (rem + o.first) % p;

  for (int i = 0; i < p; i++) {
    sort(b[i].begin(), b[i].end());
  }

  vector<ll> mn(p, LINF);
  mn[0] = 0;
  for (int i = 0; i < p; i++) {
    vector<int> ind(p);
    iota(ind.begin(), ind.end(), 0);

    for (int x : b[i]) {
      vector<ll> nmn = mn;
      for (int j : ind) {
        int nj = (j + i) % p;
        if (nmn[nj] > mn[j] + x) {
          nmn[nj] = mn[j] + x;
        }
      }
      mn = nmn;
    }
  }

  vector<ll> ans(p);
  for (int i = 0; i < p; i++) {
    ans[i] = max(-1LL, sum - mn[(rem - i + p) % p]);
  }
  return ans;
}

void test() {
  int n = 1e6;
  int p = 3e3;
  vector<pair<int, int>> a(n);
  for (int i = 0; i < n; i++) {
    a[i].first = rand() % ((int)1e9 + 1);
    a[i].second = rand() % ((int)1e9 + 1);
  }

  cerr << clock() / (double)CLOCKS_PER_SEC << endl;
  auto ans1 = fast(p, a);
  cerr << clock() / (double)CLOCKS_PER_SEC << endl;
  auto ans2 = slow(p, a);
  assert(ans1 == ans2);
  exit(0);
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  //freopen("d.out", "w", stdout);
#endif
  //test();

  int n, p;
  while (scanf("%d%d", &n, &p) == 2) {
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i].first);
    }
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i].second);
    }


    print(fast(p, a));
  }

  return 0;
}
