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

#ifdef LOCAL2
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
typedef pair<int, int> pii;

class Generator {
public:
  Generator(FILE *f, int mod_) : mod(mod_) {
    assert(fscanf(f, "%d%d%d", &r, &a, &b) == 3);
  }

  int operator()() {
    int res = r;
    r = ((ll)r * a + b) % mod;
//    eprintf("gen returns %d\n", res);
    return res;
  }

  int mod;
private:
  int r, a, b;
};

vector <int> genAll(Generator &gen, int & p, int &q) {
  vector <int> used(gen.mod, -1);
  vector <int> res;
  while (true) {
    int x = gen();
    if (used[x] != -1) {
      p = used[x];
      q = int(res.size()) - used[x];

      eprintf("p %d q %d ", p, q);
      for (int y : res) {
        (void)y;
        eprintf("%d ", y);
      }
      eprintf("\n");
      return res;
    }
    used[x] = (int)res.size();
    res.push_back(x);
  }
  assert(0);
  return res;
}

ll getC(ll len) {
  return len * (len + 1) / 2;
}

int opers = 0;

struct Set {
  int m;
  set <int> xx;
  ll sum;

  Set(int m) : m(m) {
    eprintf("new set size %d\n", m);
    xx.insert(-1);
    xx.insert(m);
    sum = getC(m);
  }

  void add(int x) {
    opers++;
//    assert(opers < int(1e6));
    eprintf("add %d\n", x);
    auto itL = xx.lower_bound(x);
    auto itR = itL;
    assert(itR != xx.end());
    assert(itR != xx.begin());
    assert(*itR != x);
    --itL;

    sum -= getC(*itR - *itL - 1);
    sum += getC(x - *itL - 1);
    sum += getC(*itR - x - 1);
    xx.insert(x);
  }

  void erase(int x) {
    opers++;
//    assert(opers < int(1e6));
    eprintf("erase %d\n", x);
    auto it = xx.find(x);
    assert(it != xx.end());
    auto itL = it;
    auto itR = it;
    --itL;
    ++itR;
    sum -= getC(x - *itL - 1);
    sum -= getC(*itR - x - 1);
    sum += getC(*itR - *itL - 1);
    xx.erase(x);
  }

  ll getSum() const {
#ifdef LOCAL
    ll sum2 = 0;
    int prev = -1;
    for (int x : xx) {
      if (x != -1) {
        eprintf("[%d, %d] ", prev, x);
        sum2 += getC(x - prev - 1);
      }
      prev = x;
    }
    eprintf("sum %lld sum2 %lld\n", sum, sum2);
    assert(sum2 == sum);
#endif
    return sum;
  }
};

int getIndex(int p, int q, ll index) {
  if (index < p) {
    return (int)index;
  }
  return (int)((index - p) % q + p);
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n, m;
  ll k;
  while (scanf("%d%d%lld", &n, &m, &k) == 3 && n != 0) {
    Generator genX(stdin, n);
    Generator genY(stdin, m);

    int xp, xq;
    vector<int> xx = genAll(genX, xp, xq);
    int yp, yq;
    vector<int> yy = genAll(genY, yp, yq);

#ifdef LOCAL2
    vector <pii> ps;
    for (int i = 0; i < k; ++i) {
      ps.push_back(pii(xx[getIndex(xp, xq, i)], yy[getIndex(yp, yq, i)]));
    }
    for (auto p : ps) {
      eprintf("%d %d\n", p.first, p.second);
    }
    eprintf("-----\n");
    sort(ps.begin(), ps.end());
    for (auto p : ps) {
      eprintf("%d %d\n", p.first, p.second);
    }
#endif

    vector <bool> used(xq + xp, false);
    ll ans = (n - (xp + xq)) * getC(m);
    for (int i = 0; i < xp; ++i) {
      ans += getC(yy[i]);
      ans += getC(m - yy[i] - 1);
      used[i] = true;
    }

    vector <int> first(xp + xq, -1);
    vector <vector<int>> starts(yp + yq);
    for (int i = xp; i < xq + xp; ++i) {
      int j = i;
      if (j < yp) {
        int k = (yp - j) / xq + 1;
        j += k * xq;
        while (j >= yp) {
          j -= xq;
        }
        while (j < yp) {
          j += xq;
        }
      }
      first[i] = j;
      eprintf("first[%d] = %d\n", i, first[i]);
      starts[getIndex(yp, yq, j)].push_back(i);
    }
    for (int i = xp; i < xq + xp; ++i) {
      int curX = i;
      Set curSet(m);
      ll curL = first[i];
      ll curR = curL;
      while (!used[curX]) {
        used[curX] = true;
        while (curL < curR && curR >= k) {
          curR -= xq;
          curSet.erase(yy[getIndex(yp, yq, curR)]);
        }
        while (curR < k) {
          curSet.add(yy[getIndex(yp, yq, curR)]);
          curR += xq;
        }
        while (curL - xq >= xp) {
          curL -= xq;
          curSet.add(yy[getIndex(yp, yq, curL)]);
        }
        eprintf("curX %d range(%lld, %lld, %d)\n", curX, curL, curR, xq);

        ans += curSet.getSum();
        if (curL < yp) {
          curSet.erase(yy[getIndex(yp, yq, curL)]);
          curL += xq;
        }
        assert(curL == first[curX]);

        while (curL < curR) {
          int j = getIndex(yp, yq, curL);
          if (starts[j].empty()) {
            curSet.erase(yy[getIndex(yp, yq, curL)]);
            curL += xq;

          } else {
            curX = starts[j].back();
            starts[j].pop_back();

            ll yi = first[curX];
            ll deltaY = curL - yi;
            eprintf("xi %lld yi %lld deltaY %lld\n", (ll)curX, yi, deltaY);
            assert(deltaY % yq == 0);

            curL -= deltaY;
            curR -= deltaY;

            eprintf("nextX %d range(%lld, %lld, %d)\n", curX, curL, curR, xq);
          }
        }
      }
//      assert(curX == i);
    }
    for (int i = 0; i < xq + xp; ++i) {
      assert(used[i]);
    }
    printf("%lld\n", ans);
//    break;
  }
  return 0;
}
