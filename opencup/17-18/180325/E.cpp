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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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

const int MOD = 1000000007;

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
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  char s[1000002];

  int n, k;
  scanf("%d%d", &n, &k);
  vector<string> w(n);

  for (int i = 0; i < n; i++) {
    scanf("%s", s);
    w[i] = s;
  }

  sort(w.begin(), w.end());

  vector<vector<int>> tr(1, vector<int>(26, -1));
  vector<int> term(1);
  for (int i = 0; i < n; i++) {
    int c = 0;
    for (int j = 0; j < w[i].length(); j++) {
      int &cc = tr[c][w[i][j] - 'a'];
      if (cc == -1) {
        cc = tr.size();
        tr.push_back(vector<int>(26, -1));
        term.push_back(-1);
      }
      c = cc;
    }
    term[c] = i;
  }

  scanf("%s", s);

  vector<int> pp;
  int c = 0;
  for (int i = 0; s[i]; i++) {
    c = tr[c][s[i] - 'a'];
    if (term[c] >= 0) {
      pp.push_back(term[c]);
      c = 0;
    }
  }

//  for (int i : pp) {
//    cout << i << endl;
//  }

  vector<int> fact(n + 1);
  vector<int> invfact(n + 1);
  fact[0] = invfact[0] = 1;
  for (int i = 1; i <= n; i++) {
    fact[i] = mul(fact[i - 1], i);
    invfact[i] = minv(fact[i]);
  }

  vector<int> f(n + 1);

  int res = 0;
  for (int i = 0; i < k; i++) {
    int q = 0;
    int j = pp[i];
    while (j >= 0) {
      q += f[j];
      j = (j & (j + 1)) - 1;
    }
//    int cc = mul(fact[n - i - 1], mul(invfact[n - k], invfact[k - i - 1]));
    int cc = mul(fact[n - i - 1], invfact[n - k]);
    int w = pp[i];
    sub(w, q);
//    cout << w << " ";
    w = mul(w, cc);
//    cout << w << endl;
    add(res, w);
    j = pp[i];
    while (j <= n) {
      f[j]++;
      j = j | (j + 1);
    }
  }
  add(res, 1);
  cout << res << endl;

  return 0;
}
