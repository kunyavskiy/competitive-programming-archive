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

int randint(int l, int r) {
  int v = (rand() << 16) ^ rand();
  v %= r - l + 1;
  return l + abs(v);
}

int n;
vector<int> canChange;
vector<pair<int, int>> es;

vector<int> solve() {
  vector<int> deg(n);
  for (const auto &e : es) {
    deg[e.first]++;
    deg[e.second]++;
  }

  int needValue = n;
  vector<int> newId(n, -1);
  vector<int> toChange, toRandom;
  for (int i = 0; i < n; i++)
    if (deg[i] % 2) {
      if (canChange[i]) {
        toChange.push_back(i);
      } else {
        newId[i] = i + 1;
        needValue ^= newId[i];
      }
    } else {
      // Does not affect the answer
      if (canChange[i]) {
        toRandom.push_back(i);
      } else {
        newId[i] = i + 1;
      }
    }

  auto fillRandom = [&]() {
    set<int> vals(newId.begin(), newId.end());
    int ptr = 1;
    for (const int x : toRandom) {
      while (vals.count(ptr)) ptr++;
      newId[x] = ptr;
      vals.insert(ptr);
    }
  };

  if (toChange.empty()) {
    if (needValue) {
      return vector<int>();
    } else {
      fillRandom();
      return newId;
    }
  } else if (toChange.size() == 1) {
    if (!needValue || count(newId.begin(), newId.end(), needValue)) {
      return vector<int>();
    }
    newId[toChange[0]] = needValue;
    fillRandom();
    return newId;
  } else if (toChange.size() == 2 && needValue == 0) {
    return vector<int>();
  }

  vector<int> curIds;
  for (;;) {
    int curValue = 0;
    curIds.clear();
    set<int> attempt(newId.begin(), newId.end());
    attempt.erase(-1);
    attempt.insert(0);
    for (int i = 1; i < (int)toChange.size(); i++) {
      int val = randint(1, (1 << 29) - 1);
      if (attempt.count(val)) {
        i--;
        continue;
      }
      attempt.insert(val);
      curValue ^= val;
      curIds.push_back(val);
    }
    if (!attempt.count(curValue ^ needValue)) {
      attempt.insert(curValue ^ needValue);
      curIds.push_back(curValue ^ needValue);
      break;
    }
  }
  assert(curIds.size() == toChange.size());
  for (int i = 0; i < (int)curIds.size(); i++) {
    newId[toChange[i]] = curIds[i];
  }
  fillRandom();
  return newId;
}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  while (scanf("%d", &n) == 1) {
    canChange.resize(n);
    for (int &x : canChange) {
      scanf("%d", &x);
      assert(x == !!x);
    }
    es.resize(n - 1);
    for (auto &e : es) {
      scanf("%d%d", &e.first, &e.second);
      e.first--, e.second--;
    }
    vector<int> newIds = solve();
    if (newIds.empty()) {
      printf("-1\n");
    } else {
      set<int> vers(newIds.begin(), newIds.end());
      assert(!vers.empty());
      assert(*vers.begin() >= 1);
      assert(*--vers.end() <= 1000000000);
      assert((int)vers.size() == n);

      int val = 0;
      printf("%d\n", n); val ^= n;
      for (const auto &e : es) {
        int a = newIds.at(e.first);
        int b = newIds.at(e.second);
        val ^= a;
        val ^= b;
        printf("%d %d\n", a, b);
      }
      assert(val == 0);
    }
  }
  return 0;
}
