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

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
//  freopen("j.out", "w", stdout);
#endif


  int n, x;
  bool first = 1;
  while (cin >> n >> x) {
    if (first) first = 0;
    else cout << endl;

    vector<int> a(n - 1);
    for (int i = 0; i < n - 1; i++) cin >> a[i];
    int k = 0;
    while ((1 << k) < n) k++;

    auto al = a;
    al.push_back(0);
    auto ar = a;
    ar.insert(ar.begin(), 0);

    vector<vector<double>> left(n, vector<double>(k + 1));
    vector<vector<double>> right(n, vector<double>(k + 1));
    for (int i = 0; i < n; i++) {
      left[i][0] = 1;
      right[i][0] = 1;
    }

    auto calc = [&](int i, int j, int val, vector<vector<double>> &pl, vector<int> &al, vector<vector<double>> &pr, vector<int> &ar) {
      double res = 0;

      j--;
      int x = i / (1 << j);
      int l = (x ^ 1) * (1 << j);
      int r = ((x ^ 1) + 1) * (1 << j);
      for (int t = l; t < r; t++) {
        double prob;
        int oth;
        if (x & 1) {
          prob = pl[t][j];
          oth = al[t];
        } else {
          prob = pr[t][j];
          oth = ar[t];
        }
        prob *= 1.0 * val / (val + oth);
        res += prob;
      }
//      db3(i, j, val);
//      db(res);
      return res;
    };

    for (int j = 1; j <= k; j++) {
      for (int i = 0; i < n; i++) {
        left[i][j] = left[i][j - 1] * calc(i, j, al[i], left, al, left, al);
        right[i][j] = right[i][j - 1] * calc(i, j, ar[i], right, ar, right, ar);
      }
    }

    for (int pos = 0; pos < n; pos++) {
      double prob = 1;
      for (int j = 1; j <= k; j++) {
        prob *= calc(pos, j, x, left, al, right, ar);
      }
      printf("%.17f\n", prob);
    }
  }

  return 0;
}
