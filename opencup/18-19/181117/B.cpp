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

int queries;
int N;
vector<string> A;
map<vector<string>, int> mp;

int getN() {
  queries = 0;
  int n;
  mp.clear();
#ifdef LOCAL
  N = rand() % 60 + 1;
  A.assign(N, string(N, '0'));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      A[i][j] = rand() % 2 + '0';
    }
  }
  for (string t : A) db(t);
  n = N;
#else
  cin >> n;
#endif
  N = n;
  return n;
}


int ask(vector<string> a) {
  if (!mp.count(a)) {
    eprintf("%s\n", a[0].c_str());
    ++queries;
//    assert(queries <= 5 * N * N);
    int res = 0;
    int n = a.size(), m = a[0].size();
#ifdef LOCAL
    res = 0;
    for (int i = 0; i + n <= N; i++) {
      for (int j = 0; j + m <= N; j++) {
        bool ok = 1;
        for (int t = 0; t < n; t++) {
          ok &= A[i + t].substr(j, m) == a[t];
          if (!ok) break;
        }
        if (ok) res = 1;
        if (res) break;
      }
      if (res) break;
    }
#else
    cout << "? " << n << " " << m << endl;
    for (string s : a) cout << s << endl;
    cin >> res;
#endif
    mp[a] = res;
  }

  return mp[a];
}

void answer(vector<string> a) {
#ifdef LOCAL
  for (int i = 0; i < N; i++) assert(A[i] == a[i]);
#else
  cout << "! " << a.size() << " " << a[0].length() << endl;
  for (string s : a) cout << s << endl;
#endif
}

void solve() {
  int n = getN();
  db(n);

  /*
  set<string> st;
  function<bool(string, int)> rec1 = [&](string s, int dir) {
    if (!ask(vector<string>(1, s))) return false;

    if ((int)s.length() == n) {
      st.insert(s);
      return true;
    }
    if (dir == 0) {
      rec1(s + '0', 0);
      rec1(s + '1', 0);
      rec1(s, 1);
    } else {
      rec1("0" + s, 1);
      rec1("1" + s, 1);
    }
    return true;
  };
  rec1("", 0);
  db("found set");
  for (string s : st) db(s);
  db(queries);
  */

  set<string> have;
  set<string> not_have;
  set<pair<int, string>, greater<pair<int, string>>> queue;
  queue.insert({1, "0"});
  queue.insert({1, "1"});

  auto cached_ask = [&] (const string &s) {
    if ((int)s.size() > n) return 0;
    if (have.count(s)) return 1;
    for (int i = 0; i < (int)s.size(); i++) {
      for (int j = i + 1; j <= (int)s.size(); j++) {
        if (not_have.count(s.substr(i, j - i))) {
          return 0;
        }
      }
    }
    int res = ask(vector<string>(1, s));
    if (!res) {
      not_have.insert(s);
      return 0;
    } else {
      for (int i = 0; i < (int)s.size(); i++) {
        for (int j = i + 1; j <= (int)s.size(); j++) {
          if (have.insert(s.substr(i, j - i)).second) {
            queue.insert({j - i, s.substr(i, j - i)});
          }
        }
      }
      return 2;
    }
  };

  vector<string> st;
  while (!queue.empty() && (int)st.size() < n) {
    auto x = queue.rbegin()->second;
    if ((int)x.size() == n) {
      st.push_back(x);
    }
    queue.erase(*queue.rbegin());


    if (cached_ask(x + "0") != 2) {
      if (cached_ask(x + "1") != 2) {
        if (cached_ask("0" + x) != 2) {
          cached_ask("1" + x);
        } else {
          queue.insert({x.size(), x});
        }
      } else {
        queue.insert({x.size(), x});
      }
    } else {
      queue.insert({x.size(), x});
    }

  }

  int dir = 0;
  vector<string> a;
  while ((int)a.size() != n) {
    if (dir == 0) {
      bool any = 0;
      for (string s : st) {
        auto na = a;
        na.push_back(s);
        if (ask(na)) {
          any = 1;
          a = na;
          break;
        }
      }
      if (!any) {
        dir = 1;
      }
    }
    if (dir == 1) {
      bool any = 0;
      for (string s : st) {
        auto na = a;
        na.insert(na.begin(), s);
        if (ask(na)) {
          any = 1;
          a = na;
          break;
        }
      }
      assert(any);
    }
  }
  for (string s : A) db(s);
  db("");
  for (string s : a) db(s);
  answer(a);
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

#ifdef LOCAL
  while (1) {
    static int iter = 19;
    srand(iter);
    db(iter++);
    solve();
    db2(queries, 5 * N * N);
    assert(queries < 5 * N * N);
  }
#endif
  solve();

  return 0;
}
