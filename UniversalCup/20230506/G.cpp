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

struct vtx {
   int l, r;
   unsigned long long hash;
};

vector<vtx> v;

bool isPrime(int x) {
   for (int i = 2; i * i <= x; i++)
     if (x % i == 0)
       return false;
   return true;
}
/*
class MyMap {
 public:
   vector<int> ids;

   void clear() { ids.clear(); }
   void rehash(int size) {
    size *= 2;
    while (!isPrime(size))
      size++;
    ids.resize(size, -1);
  }

   int get(int l, int r) {
      int pos = (((ll)l << 32) | r) % ids.size();
      while (true) {
        if (ids[pos] == -1) {
          ids[pos] = v.size();
          v.push_back({l, r});
          return v.size() - 1;
        }

        if (v[ids[pos]].l == l && v[ids[pos]].r == r) {
          return ids[pos];
        }
        pos++;
        if (pos == (int)ids.size()) pos = 0;
      }
   }
};

MyMap m;
 */
int n;

int getVtx(int l, int r) {
   assert(l != -1);
   assert(r != -1);
   v.push_back({l, r, v[l].hash * 1000000009 + v[r].hash});
   return v.size() - 1;
}

bool is_less(int a, int b) {
  if (a <= n) {
    assert(b <= n);
    return a < b;
  }
  if (v[a].hash != v[b].hash) {
    return is_less(v[a].r, v[b].r);
  }
  return is_less(v[a].l, v[b].l);
}

int add1(int id, int pos, int k) {
  assert(pos < (1 << k));
  if (k == 0) {
    assert(id < n);
    return id + 1;
  }
  if (pos < (1 << (k - 1))) {
    return getVtx(add1(v[id].l, pos, k - 1), v[id].r);
  }
  return getVtx(v[id].l, add1(v[id].r, pos - (1 << (k - 1)), k - 1));
}

void collect(int id, int pos, int k, vector<int>& res) {
  if (id <= n) {
    for (int i = 0; i < id; i++) res.push_back(pos);
  } else {
    collect(v[id].r, pos + (1 << (k - 1)), k - 1, res);
    collect(v[id].l, pos, k - 1, res);
  }
}

void solve() {
  int l, r;
  const int K = 21;

  scanf("%d%d%d", &n, &l, &r);
  v.clear();
  v.reserve((K + 2) * n);
  for (int i = 0; i <= n; i++) v.push_back({-1, -1, (unsigned long long)i});
  //m.clear();
  //m.rehash((K + 2) * n);

  vector<int> x(n), a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &x[i]);
  }
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  vector<int> ans(n);
  vector<int> q;
  int qptr = 0;
  int ptl = 0;
  int ptr = 0;


  auto add = [&](int id) {
    assert(ans[id] != -1);
    while ((int)q.size() > qptr && is_less(ans[q.back()], ans[id]))
      q.pop_back();
    q.push_back(id);
  };
  auto remove = [&](int id) {
    if (qptr < (int)q.size() && q[qptr] == id)
      qptr++;
  };
  auto get = [&]() {
    if ((int)q.size() == qptr)
      return -1;
    return q[qptr];
  };

  {
    int st = 0;
    for (int i = 0; i < K; i++) {
      st = getVtx(st, st);
    }
    ans[0] = add1(st, a[0], K);
  }

  for (int i = 1; i < n; i++) {
    while (ptl < i && x[ptl] <= x[i] - l) {
      if (ans[ptl] != -1) add(ptl);
      ptl++;
    }
    while (ptr < i && x[ptr] < x[i] - r) {
      remove(ptr);
      ptr++;
    }
    int best = get();
    if (best == -1) {
      ans[i] = -1;
    } else {
      ans[i] = add1(ans[best], a[i], K);
    }
  }

  if (ans[n - 1] == -1) {
    printf("-1\n");
  } else {
    vector<int> res;
    collect(ans[n - 1], 0, K, res);
    printf("%d\n", (int)res.size());
    for (int val : res) {
      printf("%d ", val);
    }
    printf("\n");
  }
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; i++) {
    solve();
  }
  return 0;
}
