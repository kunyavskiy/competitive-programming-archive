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
#include <random>

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
typedef long double dbl;
const dbl EPS = 1e-8;

vector<double> solve(int y, int c, int q, vector<double> r, vector<vector<double>> p, vector<int> A, vector<int> B) {
  // variables:
  // a: 0..c-1
  // b: c..c+c-1
  // r: c+c..c+c+y-1

  int m = c + c + y;
  vector<vector<dbl>> a;

  bool anyR = 0;

  a.push_back(vector<dbl>(m + 1));
  a.back()[c + c + 0] = 0;

  for (int i = 0; i < y - 1; i++) {
    if (r[i] < -0.5) continue;
    anyR = 1;

    a.push_back(vector<dbl>(m + 1));
    a.back()[c + c + i] = -1;
    a.back()[c + c + i+1] = 1;
    a.back()[m] = log(r[i]);
  }
  if (!anyR && y > 1) {
    a.push_back(vector<dbl>(m + 1));
    a.back()[c + c + 1] = 0;
  }

  for (int i = 0; i < y; i++) {
    for (int j = 0; j < c; j++) {
      if (p[i][j] < -0.5) continue;

      a.push_back(vector<dbl>(m + 1));
      a.back()[j] = 1;
      a.back()[c + j] = i;
      a.back()[c + c + i] = 1;
      a.back()[m] = log(p[i][j]);
    }
  }

  if (y == 1) {
    for (int i = 0; i < c; i++) {
      a.push_back(vector<dbl>(m + 1));
      a.back()[c + i] = 1;
      a.back()[m] = 0;
    }
  }


  int sz = a.size();

  for (int i = 0; i < y; i++) {
    for (int j = 0; j < c; j++) {
      a.push_back(vector<dbl>(m + 1));
      a.back()[j] = 1;
      a.back()[c + j] = i;
      a.back()[c + c + i] = 1;
    }
  }


  for (int i = 0; i < sz; i++) {
    int ch = -1;
    for (int j = 0; j < m; j++) {
      if (!(fabs(a[i][j]) < EPS) && (ch == -1 || fabs(a[i][j]) > fabs(a[i][ch]))) {
        ch = j;
      }
    }
    if (ch == -1) continue;
    dbl coef = a[i][ch];
    for (int j = 0; j <= m; j++) a[i][j] /= coef;

    for (int row = i + 1; row < (int)a.size(); row++) {
      coef = a[row][ch];
      for (int j = 0; j <= m; j++) {
        a[row][j] -= a[i][j] * coef;
      }
    }
  }

  vector<double> res;
  for (int i = 0; i < q; i++) {
    A[i]--; B[i]--;
    int row = sz + B[i] * c + A[i];

    bool ok = 1;
    for (int j = 0; j < m; j++) ok &= fabs(a[row][j]) < EPS;

    if (ok) res.push_back((double)exp(-a[row][m]));
    else res.push_back(-1);
  }
  return res;
}

void stress() {
  for (int it = 0;; it++) {
    cerr << it << endl;
    mt19937 rnd(it);
    auto nextDouble = [&]() {
      return rnd() * 1.0 / (1ULL << 31);
    };

    int y = rnd() % 10 + 1;
    int c = rnd() % 10 + 1;

    vector<double> a(c), b(c), nr(y);
    for (int i = 0; i < c; i++) {
      a[i] = nextDouble();
      b[i] = nextDouble();
    }
    for (int i = 0; i < y; i++) {
      if (i == 0) {
        nr[i] = 1;
      } else {
        nr[i] = nr[i - 1] + nextDouble();
      }
    }
    vector<double> r(y - 1, -1);
    for (int i = 0; i < y - 1; i++) {
      if (rnd() % 2) {
        r[i] = nr[i + 1] / nr[i];
      }
    }
    vector<vector<double>> p(y, vector<double>(c));
    for (int i = 0; i < y; i++) {
      for (int j = 0; j < c; j++) {
        if (rnd() % 2) {
          p[i][j] = exp(log(a[j]) + j * log(b[i]) + log(nr[j]));
        }
      }
    }

    vector<int> A, B;
    for (int i = 1; i <= y; i++) for (int j = 1; j <= c; j++) {
      A.push_back(j);
      B.push_back(i);
    }
    int q = A.size();


    auto ans = solve(y, c, q, r, p, A, B);
    assert(!ans.empty());
  }
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
//  freopen("c.out", "w", stdout);
#endif
//  stress();

  int y, c, q;
  while (cin >> y >> c >> q) {
    vector<double> r(y - 1);
    for (int i = 0; i < y - 1; i++) cin >> r[i];

    vector<vector<double>> p(y, vector<double>(c));
    for (int i = 0; i < y; i++) {
      for (int j = 0; j < c; j++) {
        cin >> p[i][j];
      }
    }
    vector<int> A(q), B(q);
    for (int i = 0; i < q; i++) {
      cin >> A[i] >> B[i];
    }

    auto res = solve(y, c, q, r, p, A, B);
    for (double x : res) {
      if (x < -0.5) printf("-1.0\n");
      else printf("%.17f\n", x);
    }
  }

  return 0;
}
