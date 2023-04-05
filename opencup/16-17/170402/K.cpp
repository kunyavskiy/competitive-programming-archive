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

#define TASKNAME "K"

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

typedef pair<int,int> pii;

const int INF = int(1e9) + 100;

struct RangeTree {
  int kk;
  vector <pii> minVal;
  vector <pii> maxVal;

  RangeTree(vector <int> a) {
    int n = int(a.size());
    kk = 1;
    while (kk < n) {
      kk *= 2;
    }

    minVal.assign(2 * kk + 10, pii(INF, -1));
    maxVal.assign(2 * kk + 10, pii(-INF, -1));
    for (int i = 0; i < n; ++i) {
      minVal[i + kk] = pii(a[i], i);
      maxVal[i + kk] = pii(a[i], i);
    }
    for (int i = kk - 1; i >= 1; --i) {
      update(i);
    }
  }

  int get(int pos) {
    return minVal[pos + kk].first;
  }

  void increment(int pos, int delta) {
      set(pos, get(pos) + delta);
  }

  void set(int pos, int value) {
    eprintf("set pos %d value %d\n", pos, value);
    int t = pos + kk;
    minVal[t] = pii(value, pos);
    maxVal[t] = pii(value, pos);
    while (t > 0) {
      t /= 2;
      update(t);
    }
  }

  pii getMinPos(int L, int R) {
    return getMinPos(1, 0, kk - 1, L, R);
  }

  pii getMinPos(int t, int Lt, int Rt, int L, int R) {
    if (Rt < L || R < Lt) {
      return pii(INF, -1);
    }
    if (L <= Lt && Rt <= R) {
      return minVal[t];
    }
    int Mt = (Lt + Rt) / 2;
    return min(getMinPos(2 * t, Lt, Mt, L, R), getMinPos(2 * t + 1, Mt + 1, Rt, L, R));
  }

  int getRightestPos(int L, int R, int maxV) {
    eprintf("%s L %d R %d maxV %d\n", __func__, L, R, maxV);
    int res = getRightestPos(1, 0, kk - 1, L, R, maxV);
    eprintf("%s L %d R %d maxV %d res %d\n", __func__, L, R, maxV, res);
    if (get(res) > maxV) {
      res++;
    }
    return res;
  }

  int getRightestPos(int t, int Lt, int Rt, int L, int R, int minV) {
//    eprintf("%s t %d Lt %d Rt %d maxVal[t] %d L %d R %d maxV %d\n", __func__, t, Lt, Rt, maxVal[t].first, L, R, minV);
    if (Rt < L || R < Lt) {
      return -1;
    }
//    if (L <= Lt && Rt <= R) {
      if (maxVal[t].first < minV) {
        return -1;
      }
//    }
    if (Lt == Rt) {
      assert(maxVal[t].first >= minV);
      return maxVal[t].second;
    }
    int Mt = (Lt + Rt) / 2;
    int res = getRightestPos(2 * t + 1, Mt + 1, Rt, L, R, minV);
    if (res != -1) { return res; }
    res = getRightestPos(2 * t, Lt, Mt, L, R, minV);
    return res;
  }

  void update(int t) {
    minVal[t] = min(minVal[2 * t], minVal[2 * t + 1]);
    maxVal[t] = max(maxVal[2 * t], maxVal[2 * t + 1]);
  }
};


int main() {
#ifdef LOCAL
    assert(freopen(TASKNAME".in", "r", stdin));
    assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  vector<int> h(n + 1);
  vector<int> a(n + 1, 0);
  h[0] = m + 2 - 0;
  ll sum = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    sum += a[i];
    h[i] = 0 - i;
  }

  RangeTree tree1(a);
  reverse(a.begin() + 1, a.begin() + n + 1);
  RangeTree tree2(a);
  RangeTree h1Tree(h);
  RangeTree h2Tree(h);
  int k;
  scanf("%d", &k);
  for (int i= 0; i < k; ++i) {
    int col, x;
    scanf("%d%d", &col, &x);
//    int curH = h1Tree.get(col) + col;
    int curH = m;
    int L = h1Tree.getRightestPos(0, col, curH - col);

    int col2 = n - col + 1;
    int R = h2Tree.getRightestPos(0, col2, curH - col2);
    R = n - R + 1;

    eprintf("L %d R %d\n", L, R);

    pii posR = tree1.getMinPos(col, R);
    pii posL = tree2.getMinPos(col2, n - L + 1);

    posL.second = n - posL.second + 1;
    eprintf("posL (%d, %d), posR (%d, %d)\n", posL.first, posL.second, posR.first, posR.second);

    pii posMin = posL;
    if (posR.first < posL.first || (posR.first == posL.first && posR.second - col < col - posL.second)) {
      posMin = posR;
    }
//    pii posMin = tree.getMinPos(L, R);
    sum -= posMin.first;
    sum += x;
    printf("%lld\n", sum);

    int pos = posMin.second;
    eprintf("pos %d\n", pos);

    tree1.set(pos, x);
    h1Tree.increment(pos, 1);
    pos = n - pos + 1;
    tree2.set(pos, x);
    h2Tree.increment(pos, 1);
  }

  return 0;
}
