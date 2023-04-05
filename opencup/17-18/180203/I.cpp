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
#include <numeric>

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

#ifdef LOCAL
//#define MY_INTERACT
#endif

#ifdef MY_INTERACT
vector<vector<int>> ss;
#endif

int n, k;

bool readStart() {
#ifdef MY_INTERACT
  if (scanf("%d%d", &n, &k) != 2) {
    return false;
  }
  ss.resize(n, vector<int>(k));
  for (auto &s : ss)
    for (auto &x : s)
      assert(scanf("%d", &x) == 1);
  return true;
#else
  return scanf("%d%d", &n, &k) == 2;
#endif
}

vector<int> readArr() {
  vector<int> res(n);
#ifdef MY_INTERACT
  for (int i = 0; i < n; i++)
    res[i] = ss[i].empty() ? 0 : ss[i].back();
#else
  for (int i = 0; i < n; i++)
    assert(scanf("%d", &res[i]) == 1);
#endif
  return res;
}

enum InteractionResult { LE, GE, END };

InteractionResult query(int x) {
#ifdef MY_INTERACT
  int op = rand() % 2;
  if (op == 0) {
    eprintf("Choosing LE\n");
  } else {
    eprintf("Choosing GE\n");
  }
  bool end = true;
  for (int i = 0; i < n; i++) {
    if (ss[i].empty()) continue;
    bool todel;
    if (op == 0) {
      todel = ss[i].back() <= x;
    } else {
      todel = ss[i].back() >= x;
    }
    if (todel) {
      ss[i].pop_back();
    }
    end &= ss[i].empty();
  }
  if (end) return END;
  else return op == 0 ? LE : GE;
#else
  printf("%d\n", x);
  fflush(stdout);
  char op[5];
  assert(scanf("%s", op) == 1);
  if (!strcmp(op, "End")) return END;
  if (!strcmp(op, "<=")) return LE;
  if (!strcmp(op, ">=")) return GE;
  assert(false);
#endif
}

const double C = 4.4;

int main() {
#ifdef MY_INTERACT
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  while (readStart()) {
    eprintf("readStart %d %d\n", n, k);
    vector<int> rem(n, k);
    vector<int> tops = readArr();

    double prevWtf = -1;
    for (int ops = 0;; ops++) {
      eprintf("== OPS=%d\n", ops);
      assert(ops <= 49);
      double wtf = 0;
      for (int i = 0; i < n; i++)
        if (rem[i])
          wtf += pow(C, rem[i]);
      eprintf("WTF=%.4lf\n", wtf);
      if (prevWtf >= 0) {
        double k = prevWtf / wtf;
        eprintf("k=%.4lf\n", k);
        #ifdef LOCAL
        assert(k >= 2.0 * C / (C + 1) - 1e-7);
        #endif
      }
      prevWtf = wtf;
      #ifdef LOCAL
//      eprintf("tops: ");
//      for (int i = 0; i < n; i++)
//        eprintf("%2d%c", tops[i], "\n "[i + 1 < n]);
//      eprintf("rem:  ");
//      for (int i = 0; i < n; i++)
//        eprintf("%2d%c", rem[i], "\n "[i + 1 < n]);
      #endif

      vector<pair<int, double>> vals;
      for (int i = 0; i < n; i++) {
        assert(!!tops[i] == !!rem[i]);
        if (tops[i]) {
          vals.emplace_back(tops[i], pow(C, rem[i] - 1));
        }
      }
      assert(!vals.empty());
      sort(vals.begin(), vals.end());

      double rightw = 0;
      for (int i = 0; i < (int)vals.size(); i++) {
        rightw += vals[i].second;
      }
      double leftw = 0;
      int right_first = 0;
      while (right_first < (int)vals.size() && leftw < rightw) {
        leftw += vals[right_first].second;
        rightw -= vals[right_first].second;
        right_first++;
      }

      int x = vals[right_first - 1].first;
      eprintf("right_first=%d/%d (x=%d); %.4lf %.4lf\n", right_first, (int)vals.size(), x, leftw, rightw);
      InteractionResult res = query(x);
      eprintf("  res=%d\n", res);
      if (res == END) {
        #ifdef MY_INTERACT
        break;
        #else
        return 0;
        #endif
      }

      vector<int> newTops = readArr();
      for (int i = 0; i < n; i++) {
        bool deled;
        if (res == LE) deled = tops[i] <= x;
        else if (res == GE) deled = tops[i] >= x;
        else assert(false);
        if (!deled || tops[i] == 0) {
          assert(newTops[i] == tops[i]);
        } else {
          assert(rem[i]);
          rem[i]--;
        }
      }
      tops = newTops;
      #ifdef MY_INTERACT
      for (int i = 0; i < n; i++)
        assert(rem[i] == (int)ss[i].size());
      #endif
    }

#ifndef MY_INTERACT
    break;
#endif
  }

  return 0;
}
