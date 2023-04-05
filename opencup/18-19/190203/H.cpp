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
    db("rand");
    while ((int)st.size() < n) st.insert(rand() % (int)k + 1);
  }
  else {
    db("1..n");
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
  if (nq > 2600) {
    db("FAIL");
    db(nq);
    while (true);
  }
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

double log_c(int n, int k) {
  if (n < k) return -1e100;
  double ans = 0;
  for (int i = 0; i < k; i++) {
    ans += log(n - i);
    ans -= log(i + 1);
  }
  return ans;
}

double log_sum(double x, double y) {
  if (y > x) swap(x, y);
  return x + (log(1 + exp(y - x)));
}

int find_p_3(int k, int n, int T) {
  int L = 0;
  int R = T;
  double target = log_sum(log_c(n, k), log_c(n - T, k)) - log(2);
  while (R - L > 1) {
    int mid = (L + R) / 2;
    double val = log_c(n - mid, k);

    if (val <= target) {
      R = mid;
    } else {
      L = mid;
    }
  }
//  db3(L, R, T);
//  exit(0);
  return L;
}

void solve2() {
  nq = 0;
  auto o = init();
  int n = o.first;
  int k = o.second;
  ll last = 0;
  for (int i = 0; i < n; i++) {
    ll L = last + 1;
    ll R = k;
//    db(log_c(k - L + 1, n - i) / log(2) + nq);
    int have = n - i;
    while (true) {
      assert(L <= R);
      ll pp = find_p_3(have, k - L + 1, R - L + 1);
      ll mid = L + pp;
//      db3(L, R, mid);
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

int main() {
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
