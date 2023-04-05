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

struct node{
  int next[2], link;
  int len; bool term;
  node(){
    memset(next,0,sizeof(next));
    len = 0; link = 0; term = 0;
  }
};

const int MAXL = 5000000;

node A[2 * MAXL + 10];
int memptr;

struct Automaton {
  int root, last;

  int it, itlen;

  void init() {
    root = last = memptr++;
    A[root] = node();
    it = root;
    itlen = 0;
  }

  void add(int c){
    int nlast = memptr++;
    A[nlast] = node();
    A[nlast].len = A[last].len + 1;
    int p = last;
    for (;p && A[p].next[c] == 0; p = A[p].link)
      A[p].next[c] = nlast;
    if (!p){
      A[nlast].link = root;
    } else {
      int q = A[p].next[c];
      if (A[q].len == A[p].len + 1){
        A[nlast].link = q;
      } else {
        int clone = memptr++;
        memcpy(&A[clone], &A[q], sizeof(node));
        A[clone].link = A[q].link;
        A[clone].len = A[p].len + 1;
        A[q].link = A[nlast].link = clone;
        for (;p && A[p].next[c] == q; p = A[p].link)
          A[p].next[c] = clone;
        if (it == q && itlen <= A[clone].len) {
          it = clone;
        }
      }
    }
    last = nlast;
  }

  void go(int c) {
    while (it != root && A[it].next[c] == 0) {
      it = A[it].link;
      itlen = A[it].len;
    }
    if (A[it].next[c]) {
      itlen++;
      it = A[it].next[c];
    }
  }
};

const int MOD1 = 1000000007;
const int MOD2 = 1000000009;

struct HV {
  int f, s;

  bool operator<(const HV &rhs) const {
    if (f != rhs.f)
      return f < rhs.f;
    return s < rhs.s;
  }

  bool operator==(const HV& x) const {
    return f == x.f && s == x.s;
  }
};

HV operator+(const HV &a, const HV &b) {
  return {(a.f + b.f) % MOD1, (a.s + b.s) % MOD2};
}

HV operator-(const HV &a, const HV &b) {
  return {(a.f - b.f + MOD1) % MOD1, (a.s - b.s + MOD2) % MOD2};
}

HV operator*(const HV &a, const HV &b) {
  return {(int)((a.f * 1LL * b.f) % MOD1), (int)((a.s * 1LL * b.s) % MOD2)};
}

HV deg[MAXL];

HV h[2][MAXL];

inline HV get_hash(int id, int l, int r) {
  return h[id][r] - h[id][l] * deg[r - l];
}

int len[2];


char inp[MAXL];

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  deg[0] = {1, 1};
  deg[1] = {29, 31};
  for (int i = 2; i < MAXL; i++) {
    deg[i] = deg[i - 1] * deg[1];
  }

  memptr = 1;
  Automaton a[2];

  a[0].init();
  a[1].init();

  int n;
  scanf("%d%s", &n, inp);

  int x = 0;
  ll ans = 0;

  h[0][0] = h[1][0] = {0, 0};

  for (int i = 0; i < n; i++) {
    int num = (x ^ (inp[i] - '0')) % 2;
    int c = ((x ^ (inp[i] - '0')) / 2) % 2;

    a[num].add(c);
    a[num ^ 1].go(c);
    len[num]++;

    h[num][len[num]] = h[num][len[num] - 1] * deg[1] + HV({c, c});

    int l = a[num].itlen;
    int r = min(len[0], len[1]) + 1;

    while (r - l > 1) {
      int m = (l + r) / 2;
      if (get_hash(0, len[0] - m, len[0]) == get_hash(1, len[1] - m, len[1])) {
        l = m;
      } else {
        r = m;
      }
    }

    if (l > a[num].itlen) {
      a[num].it = a[num].last;
      a[num].itlen = l;
    }

    x = max(x, a[0].itlen);
    x = max(x, a[1].itlen);

    ans += x;
  }

  printf("%lld\n", ans);

  return 0;
}
