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

typedef pair<int,int> pii;

const int P = int(1e9) + 7;

int add(int a, int b) {
  if ((a += b) >= P) {
    a -= P;
  }
  return a;
}

int prod(int a, int b) {
  return ll(a) * b % P;
}

void genPerms(const vector<int> & a,
              const vector<int> & b,
              const vector<int> & p1,
              const vector<int> & p2,
              int L, int R,
              vector<pii> &sums,
              int X, int Y) {
  vector <int> perm;
  for (int i = L; i < R; ++i) {
    perm.push_back(i);
  }

  int num = 0;
  do {
    int sum = 0;
    for (int i = 0; i < int(perm.size()); ++i) {
      int i1 = i + L;
      int i2 = perm[i];
      sum = add(sum, prod(a[p1[i1]], b[p2[i2]]));
    }
    sum = add(Y, prod(sum, X));
    sums.push_back(pii(sum, num));
    num++;
  } while (next_permutation(perm.begin(), perm.end()));
  sort(sums.begin(), sums.end());
}

pair<int, pii> find_optimal(const vector<int> & a,
                 const vector<int> & b,
                 const vector<int> & p1,
                 const vector<int> & p2,
                 int n1, int n2,
                 int sum3) {
  vector <pii> sums1, sums2;
  genPerms(a, b, p1, p2, 0, n1, sums1, 1, sum3);
  genPerms(a, b, p1, p2, n1, n1 + n2, sums2, P - 1, 0);

  int ans = P;
  int best1, best2;
  best1 = best2 = -1;
  for (int i = 0, j = 0; i < int(sums1.size()); ++i) {
    while (j < int(sums2.size()) && sums2[j].first <= sums1[i].first) {
      ++j;
    }
    int prevJ = (j == 0 ? int(sums2.size()) - 1 : j - 1);
    int cur = sums1[i].first - sums2[prevJ].first;
    if (cur < 0) {
      cur += P;
    }
    assert(0 <= cur && cur < P);
    if (cur < ans) {
      ans = cur;
      best1 = sums1[i].second;
      best2 = sums2[prevJ].second;
    }
  }
  return make_pair(ans, pii(best1, best2));
}

vector <int> get_perm(int num, int n) {
  int tot = 1;
  for (int i = 1; i <= n; ++i) {
    tot *= i;
  }

  vector <int> used(n, true);
  vector <int> perm;
  for (int i = n; i >= 1; --i) {
    tot /= i;
    int k = num / tot;
    num %= tot;

    int x = -1;
    for (int j = 0; j < n; ++j) {
      if (used[j]) {
        if (k == 0) {
          x = j;
          break;
        }
        --k;
      }
    }
    assert(x != -1);
    used[x] = false;
    perm.push_back(x);
  }
  return perm;
}

vector<int> getRes(const vector <int> & p1, const vector <int> & p2,
              int n1, int n2, pii perms) {
  vector<int> q1 = get_perm(perms.first, n1);
  vector<int> q2 = get_perm(perms.second, n2);

  int n = int(p1.size());
  vector <int> invP1(n);
  for (int i = 0; i < n; ++i) {
    invP1[p1[i]] = i;
  }

  vector <int> res;
  for (int i = 0; i < n; ++i) {
    int i1 = invP1[i];
    int i2;
    if (i1 < n1) {
      i2 = p2[q1[i1]];
    } else if (i1 < n1 + n2) {
      i2 = p2[q2[i1 - n1] + n1];
    } else {
      i2 = p2[i1];
    }
    res.push_back(i2);
  }
  return res;
}

void printRes(int sum, const vector<int> & perm,
              const vector<int> & a,
              const vector<int> & b) {
  int exp = 0;
  for (int i = 0; i < int(a.size()); ++i) {
    exp = add(exp, prod(a[i], b[perm[i]]));
  }

  printf("%d\n", sum);
  for (int x : perm) {
    printf("%d ", x + 1);
  }
  printf("\n");

  assert(sum == exp);
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  double start = clock() * 1.0 / CLOCKS_PER_SEC;


  int n;
  scanf("%d", &n);
  bool random = false;
  if (n < 0) {
    n = -n;
    random = true;
  }
  vector<int> a(n);
  vector<int> b(n);
  for (int i = 0; i < n; ++i) {
    if (random) {
      a[i] = rand() % P;
    } else {
      scanf("%d", &a[i]);
    }
  }
  for (int i = 0; i < n; ++i) {
    if (random) {
      b[i] = rand() % P;
    } else {
      scanf("%d", &b[i]);
    }
  }

  const int K = 8;
  if (n < 14) {
    int ans = P;
    int best_mask = -1;
    pii best(-1, -1);
    vector<int> p1(n);
    for (int i = 0; i < n; ++i) {
      p1[i] = i;
    }
    int n1 = n / 2;
    int n2 = n - n1;
    for (int mask = 0; mask < (1 << n); ++mask) {
      vector<int> p2;
      for (int i = 0; i < n; ++i) {
        if (mask & (1 << i)) {
          p2.push_back(i);
        }
      }
      if (p2.size() != n1) { continue; }
      for (int i = 0; i < n; ++i) {
        if (!(mask & (1 << i))) {
          p2.push_back(i);
        }
      }

      auto x = find_optimal(a, b, p1, p2, n1, n2, 0);
      if (ans > x.first) {
        ans = x.first;
        best = x.second;
        best_mask = mask;
      }
    }

    assert(best_mask != -1);
    vector<int> p2;
    for (int i = 0; i < n; ++i) {
      if (best_mask & (1 << i)) {
        p2.push_back(i);
      }
    }
    assert(p2.size() == n1);
    for (int i = 0; i < n; ++i) {
      if (!(best_mask & (1 << i))) {
        p2.push_back(i);
      }
    }
    printRes(ans, getRes(p1, p2, n1, n2, best), a, b);
  } else {
    vector<int> p1(n), p2(n);
    for (int i = 0; i < n; ++i) {
      p1[i] = p2[i] = i;
    }

    int ans = P;
    vector <int> res;
    while (1) {
      random_shuffle(p1.begin(), p1.end());
      random_shuffle(p2.begin(), p2.end());

      int n1 = min(n, K);
      int n2 = min(n - K, K);
      int sum3 = 0;
      for (int i = n1 + n2; i < n; ++i) {
        sum3 = add(sum3, prod(a[p1[i]], b[p2[i]]));
      }

      auto x = find_optimal(a, b, p1, p2, n1, n2, sum3);
      if (x.first < ans) {
        ans = x.first;
        res = getRes(p1, p2, n1, n2, x.second);
      }
      eprintf("%.10lf %.10lf\n", clock() * 1.0 / CLOCKS_PER_SEC, start);
      if (x.first == 0 || clock() * 1.0 / CLOCKS_PER_SEC > start + 4.5) {
        break;
      }
    }
    printRes(ans, res, a, b);
  }

  return 0;
}
