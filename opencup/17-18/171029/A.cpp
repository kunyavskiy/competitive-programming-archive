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

int eoff;

void eprintoff() {
  for (int i = 0; i < eoff; i++)
    eprintf(" ");
}

#ifdef LOCAL
#define eoprintf(...) do { eprintoff(); fprintf(stderr,__VA_ARGS__); } while (0)
#else
#define eoprintf(...)
#endif

typedef long long ll;
typedef long double ld;

class fenv_tree {
public:
  fenv_tree(int n = 0) : tr(n + 1, 0) {}
  void add(int i, ll x) {
    for (i++; i < (int)tr.size(); i += f(i)) {
      tr[i] += x;
    }
  }
  ll get(int l, int r) {
    return get_(r) - get_(l - 1);
  }

private:
  vector<ll> tr;
  static int f(int i) { return i & -i; }
  ll get_(int i) {
    ll res = 0;
    for (i ++; i > 0; i -= f(i))
      res += tr[i];
    return res;
  }
};

class Magic {
public:
  Magic(int n = 0) : tr(n), vals(n, 0) {
    for (int i = 0; i < n; i++)
      zeros.insert(i);
    zeros.insert(-1);
    zeros.insert(n);
  }

  ll set_val(int i, ll nval) {
    tr.add(i, nval - vals[i]);
    vals[i] = nval;
    if (nval) zeros.erase(i);
    else zeros.insert(i);

    auto ne = zeros.lower_bound(i);
    assert(ne != zeros.end());
    if (*ne == i) {
      eoprintf("!!! m.set_val(%d, %lld) = 0?\n", i, nval);
      return 0;
    }
    int r = *ne - 1;
    assert(ne != zeros.begin());
    ne--;
    int l = *ne + 1;
    assert(l <= r);
    ll res = tr.get(l, r);
    eoprintf("!!! m.set_val(%d, %lld) = %lld\n", i, nval, res);
    return res;
  }

  void debug() {
    eprintf("vals:");
    set<int> zeros2 = {-1, static_cast<int>(vals.size())};
    for (int i = 0; i < (int) vals.size(); i++) {
      eprintf(" %lld", vals[i]);
      if (vals[i] == 0) zeros2.insert(i);
      assert(tr.get(i, i) == vals[i]);
    }
    eprintf("\n");
    assert(zeros == zeros2);
  }

private:
  fenv_tree tr;
  vector<ll> vals;
  set<int> zeros;
};

const int INF = int(1e9) + 10;

class Solver {
public:
  struct Cancel {
    bool should_cancel;
    int i;
    ll oldMinv, oldMaxv;
  };

  Solver() {}
  Solver(int n, ll k_) : k(k_), minv(n, 0), maxv(n, INF), m(n) {}

  bool enter_cond(int i, int l, int r, Cancel &c) {
    c.should_cancel = false;
    assert(l <= r);
    if (l > maxv.at(i)) {
      return false;
    }
    if (r < minv.at(i)) {
      return false;
    }
    c.should_cancel = true;
    c.i = i;
    c.oldMinv = minv[i];
    c.oldMaxv = maxv[i];
    minv[i] = max(minv[i], (ll)l);
    maxv[i] = min(maxv[i], (ll)r);
    ll new_sum = m.set_val(i, minv[i]);
    if (new_sum > k) {
      exit_cond(c);
      assert(!c.should_cancel);
      return false;
    }
    return true;
  }

  void exit_cond(Cancel &c) {
    if (!c.should_cancel) {
      return;
    }
    minv[c.i] = c.oldMinv;
    maxv[c.i] = c.oldMaxv;
    ll set_result = m.set_val(c.i, minv[c.i]);
    assert(set_result <= k);
    c.should_cancel = false;
  }

  void debug() {
    eprintf("debug:");
    for (int i = 0; i < (int)minv.size(); i++)
      eprintf("a[%d]: %lld..%lld\n", i, minv[i], maxv[i]);
    m.debug();
  }

private:
  ll k;
  vector<ll> minv, maxv;
  Magic m;
};

deque<string> tokens;

bool readToken(const char *s) {
  if (tokens.empty()) return false;
  if (tokens.front() != s) return false;
  tokens.pop_front();
  return true;
}

int readInt() {
  assert(!tokens.empty());
  int res = 0;
  for (char c : tokens.front()) {
    assert('0' <= c && c <= '9');
    res = res * 10 + c - '0';
  }
  tokens.pop_front();
  return res;
}

Solver s;
set<int> reachable;

void readOneStatement(bool isok) {
  if (readToken("art")) {
    int id = readInt();
    eoprintf("art(%d); isok=%d\n", id, isok);
    if (isok) {
      reachable.insert(id);
    }
  } else if (readToken("if")) {
    assert(readToken("a"));
    int id = readInt() - 1;
    int x = readInt();
    {
      eoprintf("if (a[%d] >= %d) enter\n", id, x);
      eoff += 2;
      Solver::Cancel c;
      bool isok2 = isok;
      if (!s.enter_cond(id, x, INF, c)) {
        eoprintf("it's unreachable-1\n");
        isok2 = false;
      }
      readOneStatement(isok2);
      s.exit_cond(c);
      eoff -= 2;
    }
    if (readToken("else")) {
      eoprintf("if (a[%d] < %d) enter\n", id, x);
      eoff += 2;
      Solver::Cancel c;
      bool isok2 = isok;
      if (!s.enter_cond(id, 0, x - 1, c)) {
        eoprintf("it's unreachable-2\n");
        isok2 = false;
      }
      readOneStatement(isok2);
      s.exit_cond(c);
      eoff -= 2;
    }
  } else if (readToken("{")) {
    while (!readToken("}")) {
      readOneStatement(isok);
    }
  } else {
    assert(!tokens.empty());
    eprintf("stuck at token '%s'\n", tokens.front().c_str());
    assert(false);
  }
}

int getClass(char c) {
  if (c >= 'a' && c <= 'z') return 'a';
  if (c >= '0' && c <= '9') return '0';
  if (strchr(" \r\n\t,;()>=[]", c)) return ' ';
  if (strchr("{}", c)) return '{';
  assert(false);
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  static const int MAXL = int(10e6);
  static char buf[MAXL + 1];
  {
    size_t l = fread(buf, 1, MAXL, stdin);
    assert(l < MAXL);
    buf[l] = 0;
  }

  {
    for (int i = 0; buf[i]; i++) {
      int cls = getClass(buf[i]);
      if (cls == ' ') continue;
      if (cls == '{') {
        tokens.emplace_back(1, buf[i]);
        continue;
      }
      string tok = "";
      for (; buf[i] && getClass(buf[i]) == cls; i++) {
        tok += buf[i];
      }
      tokens.push_back(tok);
    }
  }

  for (const auto &t : tokens) {
    eprintf("%s ", t.c_str());
  }
  eprintf("\n");

  while (readToken("game")) {
    eprintf("==========\n");
    int n = readInt();
    int k = readInt();

    s = Solver(n, k);
    reachable.clear();
    readOneStatement(true);

    eprintf("reachable:");
    for (int x : reachable)
      eprintf(" %d", x);
    eprintf("\n");
    printf("%d\n", static_cast<int>(reachable.size()));
  }

  return 0;
}
