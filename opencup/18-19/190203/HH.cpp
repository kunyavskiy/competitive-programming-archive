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

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl
#define pb push_back
#define sz(a) (int)(a).size()
#define all(a) (a).begin() (a).end()
#define pw(x) (1ll << (x))


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

int n, k;
int cur;
vector<int> a;

pair<int, int> init() {
#ifdef LOCAL
  n = 100;
  k = 1e9;
  set<int> st;
  if (rand() % 2) {
    while ((int)st.size() < n) st.insert(rand() % (int)k + 1);
  }
  else {
    for (int i = 0; i < n; i++) {
      st.insert(i + 1);
//    st.insert(k - i);
    }
  }
  a = vector<int>(st.begin(), st.end());
#else
  cin >> n >> k;
#endif
  cur = 0;
  return make_pair(n, k);
}


// a[i] < x -> -1
// a[i] = x -> 0
// a[i] > x -> 1

int nq;
int ask(int x) {
  nq++;
#ifdef LOCAL
  if (a[cur] < x) return -1;
  if (a[cur] == x) {
    cur++;
    return 0;
  }
//  db2(cur, a[cur]);
  if (a[cur] > x) return 1;
#else
    cout << x << endl;
  string s;
  cin >> s;
  if (s == "<") return -1;
  if (s == "=") {
    cur++;
    return 0;
  }
  if (s == ">") return 1;
#endif
  assert(0);
}

double find_p(int k) {
//  if (k > 10)
//    return 1.0 / (k + 1) * 0.5;
//  return 1.0 / (k + 1);
  double L = 0;
  double R = 1;

  for (int i = 0; i < 60; i++) {
    double mid = (L + R) / 2;
    double f = 1;
    for (int j = 0; j < k; j++) f *= 1 - mid;
    if (mid > f) {
      R = mid;
    }
    else {
      L = mid;
    }
  }
  return (L + R) / 2;
}

void check_dbl(double x) {
  assert(fpclassify(x) != FP_INFINITE && fpclassify(x) != FP_NAN);
}


double find_p_2(int k, int n, int T) {
//  if (k > 10)
//    return 1.0 / (k + 1) * 0.5;
//  return 1.0 / (k + 1);
//  db3(k, n, T);
  double L = 0;
  double R = 1;

  for (int i = 0; i < 60; i++) {
    double p = (L + R) / 2;
//    db2(i, p);
    double sl = log(p * T) + (k - 1) * log(n);
    double sr = log(T * (1 - p)) + (k - 1) * log(n - T * p);
//    db2(sl, sr);
    check_dbl(sl);
    check_dbl(sr);
//    assert(fpclassify)
//    db2(sl, sr);
    if (sl > sr) {
      R = p;
    }
    else {
      L = p;
    }
  }
  if (T < 10) return 0.5;
//  if (T < 10 && abs((L + R) / 2 - 0.5) > 0.05) {
//      db2(L, R);
//      db3(k, n, T);
//      assert(false);
//  }
  return (L + R) / 2;
}




void solve2() {
  nq = 0;
  auto o = init();
  int n = o.first;
  int k = o.second;
  ll last = 0;
  for (int i = 0; i < n; i++) {
//    db(i);
    ll L = last + 1;
    ll R = k + 1;
    int have = n - i;
    bool win = 0;
    while (true) {
//      db3(L, R, have);
      assert(L + have <= R);
      double p = find_p(have);
      ll mid = (L * (1 - p) + R * p);
      assert(L <= mid && mid < R);
      int res = ask(mid);
//      db(res);
      if (res == 0) {
        last = mid;
        win = 1;
        break;
      }
      if (res == -1) {
        R = mid - 1;
        break;
      }
      assert(res == 1);
      L = mid + 1;
    }
    if (win) continue;
//    db("done");
    while (true) {
//      dbv(a);
//      db2(L, R);
      assert(L <= R);
      double pp = find_p_2(have, k - L + 1, R - L + 1);
      ll mid = (L * (1 - pp) + R * pp);
      assert(L <= mid && mid <= R);
      int res = ask(mid);
      if (res == 0) {
        last = mid;
        break;
      }
      if (res == -1) {
        R = mid - 1;
      }
      else {
        L = mid + 1;
      }
    }

  }



  db(nq);

}

void solve() {
  auto o = init();
  int n = o.first;
  int k = o.second;

  nq = 0;
  int mn = 1, mx = k;
  for (int i = 0; i < n; i++) {
    int L = mn, R = mx;

    int found = -1;
    int iter = 0;
    while (1) {
      assert(L <= R);
      int M;
      if (iter++ < 0) {
        M = (L + L + R) / 3;
      } else {
        M = (L + R) / 2;
      }

      int res = ask(M);
      if (res == 0) {
        found = M;
        break;
      } else {
        if (res < 0) R = M - 1;
        else L = M + 1;
      }
    }
    db(iter);
    mn = found + 1;
  }
  db(nq);
  assert(nq <= 26 * 100);
}

int main() {
//  db(find_p(1));
//  db(find_p(10));
//  db(find_p(100));
//  db(find_p_2(100, 1e9, 1e8));
//  db(find_p_2(100, 1e9, 1e7));
//  db(find_p_2(100, 1e9, 1e6));
//  db(find_p_2(100, 1e9, 1e3));
//  db(find_p_2(2, 1e9, 1e7));
//  db(find_p_2(2, 1e9, 1e6));
//  db(find_p_2(1, 1e6, 6));
//  db(find_p_2(2, 1e9, 7));
//  db(find_p_2(3, 1e9, 5));
//  db(find_p_2(3, 1e9, 5));
//  db(find_p_2(30, 1e9, 5));
//  db(find_p_2(100, 1e9, 5));
//  exit(0);
  for (int i = 1; i < 100; i++) {
    for (int j = i; j < 100; j++) {
      for (ll k = 10; k < 1e9; k *= 1.5) {
        if (k >= j) {
          find_p_2(i, k, j);
        }
      }
    }
  }
//  exit(0);


#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
  srand(19);

  while (1) {
    solve2();
  }
#endif

  solve2();

  return 0;
}


