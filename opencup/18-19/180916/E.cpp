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

//#undef LOCAL
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

const int N = 1000;

string s;
vector<int> sum;
int queries;

void gen() {
  int n = N;
  s = "";
  for (int i = 0; i < n; i++) {
    s += (char)('0' + rand() % 2);
    //s += (char)('0' + rand() % 1);
  }
  sum.resize(n + 1);
  sum[0] = 0;
  for (int i = 0; i < n; i++) {
    sum[i + 1] = sum[i] + (s[i] == '1');
  }
}

map<pair<int, int>, int> mp;

int ask(int l, int r) {
  assert(queries++ < 18000);

  if (mp.count({l, r})) return mp[{l, r}];
  int res = -1;
#ifdef LOCAL
  int tp = rand() % 2;
  int csum = sum[r + 1] - sum[l];
  if (tp == 0) {
    res = csum;
  } else {
    res = csum;
    while (res == csum) {
      res = rand() % (r - l + 1 + 1);
    }
  }
#else
  cout << "? " << l + 1 << " " << r + 1 << endl;
  cin >> res;
#endif
  return mp[{l, r}] = res;
}

void answer(string ans) {
#ifdef LOCAL
  //db(ans);
  //db(s);
  assert(ans == s);
#else
  cout << "! " << ans << endl;
#endif
}

const int C = 50;

void solve() {
  queries = 0;
  mp.clear();

  int n = N;
  int mid = n / 2;

  string ans(n, '?');

  for (int it = 0; it < 2; it++) {
    auto task = [&](int l, int r) {
      if (it == 1) {
        l = n - 1 - l;
        r = n - 1 - r;
        swap(l, r);
      }
      return ask(l, r);
    };

    vector<pair<int, int>> cand;
    for (int i = 0; i < C; i++) {
      cand.push_back({i, task(i, mid - 1)});
    }
    vector<int> was(n + 1);
    for (auto o : cand) {
      was[o.second]++;
    }

    int best = -1, bsum = -1;
    for (int i = 0; i < n - C; i++) {
      int csum = 0;
      for (int j = 0; j < C; j++) csum += was[i + j];

      if (bsum < csum) {
        best = i;
        bsum = csum;
      }
    }

    vector<pair<int, pair<int, int>>> ncand;
    for (auto o : cand) {
      if (best <= o.second && o.second < best + C) {
        ncand.push_back({0, o});
      }
    }
    //db(ncand.size());
    //for (auto o : ncand) db2(o.second.first, o.second.second);

    int sumR = 0;
    for (int i = mid; i < n; i++) {
      int cur0 = 0;
      int cur1 = 0;
      sort(ncand.begin(), ncand.end());
      bool found = 0;
      for (int j = 0; j < (int)ncand.size(); j++) {
        int cres = task(ncand[j].second.first, i);
        int should_be = ncand[j].second.second + sumR;
        if (cres == should_be) {
          cur0++;
          ncand[j].first -= n;
        } else if (cres == should_be + 1) {
          cur1++;
          ncand[j].first -= n;
        } else ncand[j].first++;

        if (abs(cur0 - cur1) > 4) {
          int id = i;
          if (it == 1) id = n - 1 - id;
          if (cur0 > cur1) {
            ans[id] = '0';
          } else {
            ans[id] = '1';
            sumR++;
          }
          found = 1;
          break;
        }
      }
      if (!found) {
        int id = i;
        if (it == 1) id = n - 1 - id;
        if (cur0 > cur1) {
          ans[id] = '0';
        } else {
          ans[id] = '1';
          sumR++;
        }
        found = 1;
      }

      assert(found == 1);
    }
  }
  answer(ans);
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

#ifdef LOCAL
  if (1) {
    int test = 0;
    while (1) {
      srand(test);
      db(test++);
      gen();
      solve();
    }
  }
#endif

  solve();

  return 0;
}
