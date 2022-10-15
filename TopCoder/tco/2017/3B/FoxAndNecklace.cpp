#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <functional>
#include <bitset>
#include <ctime>
#include <cassert>
#include <numeric>

#define pb push_back
#define mp make_pair      
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
 
typedef long long ll;
typedef long double ld;

const ll INF = (ll)(1e15);

ll smul(ll a, ll b) {
  if (a >= INF / b) return INF;
  return a * b;
}

ll sadd(ll a, ll b) {
  if (a >= INF - b) return INF;
  return a + b;
}

ll ssub(ll a, ll b) {
  return max(-1LL, a - b);
}

const int MAXN = 100;
const int BUBEN = 4;
const int MAXW = 100000100;

class FoxAndNecklace {
  ll cnk[MAXN][MAXN];

  ll limit;
  vector<int> v;
  vector<int> vsum;

  vector<int> have[MAXN];

  void go(int pos, int k, int minv) {
    if (k == BUBEN) {
      for (int i = 0; i < pos; i++) {
        limit = ssub(limit, have[i].end() - lower_bound(have[i].begin(), have[i].end(), minv));
      }
      return;
    }
    if (minv <= 0) {
      limit = ssub(limit, cnk[pos][k]);
      return;
    }
    if (k == 0 || limit < 0 || pos < k) {
      return;
    }
    if (vsum[pos] - vsum[pos - k] < minv) {
      return;
    }
    go(pos - 1, k, minv);
    go(pos - 1, k - 1, minv - v[pos - 1]);
  }

  void get_buben(int pos, int k, int sum) {
    if (k == BUBEN) {
      have[pos - 1].push_back(sum);
      return;
    }
    if (pos == (int)v.size()) {
      return;
    }
    get_buben(pos + 1, k, sum);
    get_buben(pos + 1, k + 1, sum + v[pos]);
  }

public:
  string possible(vector<int> v, int k, int minv, ll d) {
    cnk[0][0] = 1;
    for (int i = 0; i < MAXN; i++) {
      for (int j = 0; j < MAXN; j++) {
        if (i) cnk[i][j] = sadd(cnk[i][j], cnk[i - 1][j]);
        if (i && j) cnk[i][j] = sadd(cnk[i][j], cnk[i - 1][j - 1]);
      }
    }

    ll x = 1;
    for (int i = 3; i < k; i++) {
      x = smul(x, i);
    }
    limit = (d + x - 1) / x;
    sort(v.begin(), v.end());
    this->v = v;
    vsum = vector<int>(v.size() + 1);
    for (int i = 0; i < (int)v.size(); i++) {
      vsum[i + 1] = vsum[i] + v[i];
    }

    get_buben(0, 0, 0);
    for (int i = 0; i < (int)v.size(); i++) {
      sort(have[i].begin(), have[i].end());
    }
    go((int)v.size(), k, minv);
    return limit > 0 ? "Impossible" : "Possible";
  }
};










