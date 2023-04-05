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

void print(vector<string> a) {
  for (string s : a) cout << s << endl;
}

int sign(char c) {
  return c == '+' ? 1 : -1;
}

int qmark(string s) {
  int res = 0;
  for (char c : s) res += c == '?';
  return res;
}

const int Z = 40;
vector<int> autocorel(string s) {
  vector<int> a(s.length());
  for (int i = 0; i < (int)a.size(); i++) a[i] = sign(s[i]);

  vector<int> res;
  for (int d = 1; d <= Z; d++) {
    int cur = 0;
    for (int i = 0; i + d < (int)a.size(); i++) {
      cur += a[i] * a[i + d];
    }
    res.push_back(cur);
  }
  return res;
}

vector<int> mul(vector<int> a, int d) {
  for (int &x : a) x *= d;
  return a;
}

vector<int> sum(vector<int> a, vector<int> b) {
  assert(a.size() == b.size());
  for (int i = 0; i < (int)a.size(); i++) a[i] += b[i];
  return a;
}

struct item {
  string s;
  int coef;
  int id;

  bool operator< (const item &it) const {
    if (qmark(s) != qmark(it.s)) return qmark(s) < qmark(it.s);
    return id < it.id;
  }
};

pair<int, int> divide(vector<item> a) {
  int best = 1e9;
  int best_mask = -1;
  int all = 0;
  for (int i = 0; i < 4; i++) all += qmark(a[i].s);

  for (int mask = 0; mask < (1 << 4); mask++) {
    int cur = 0;
    for (int i = 0; i < 4; i++) if (mask & (1 << i)) cur += qmark(a[i].s);
    if (cur * 2 >= all && cur < best) {
      best = cur;
      best_mask = mask;
    }
  }

  return {best, best_mask};
}

vector<string> solve1(vector<item> a) {
  vector<string> ans;

  auto o = divide(a);
  int best_mask = o.second;

  vector<vector<pair<int, int>>> pos(2);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < (int)a[i].s.length(); j++) if (a[i].s[j] == '?') {
        pos[(best_mask >> i) & 1].push_back({i, j});
      }
  }

  vector<vector<pair<vector<int>, int>>> vct(2);
  for (int it = 0; it < 2; it++) {
    for (int mask = 0; mask < (1 << ((int)pos[it].size())); mask++) {
      for (int i = 0; i < (int)pos[it].size(); i++) {
        a[pos[it][i].first].s[pos[it][i].second] = "-+"[(mask >> i) & 1];
      }
      vector<int> bal(Z, 0);
      for (int i = 0; i < 4; i++) if (((best_mask >> i) & 1) == it) bal = sum(bal, mul(autocorel(a[i].s), a[i].coef));

      if (it == 1) bal = mul(bal, -1);
      vct[it].push_back({bal, mask});
    }
    sort(vct[it].begin(), vct[it].end());
  }

  int j = 0;
  for (int i = 0; i < (int)vct[0].size(); i++) {
    while (j < (int)vct[1].size() && vct[1][j].first < vct[0][i].first) j++;
    if (j < (int)vct[1].size() && vct[1][j].first == vct[0][i].first) {
      ans.resize(4);

      vector<int> cmask = {vct[0][i].second, vct[1][j].second};
      for (int it = 0; it < 2; it++) {
        for (int l = 0; l < (int)pos[it].size(); l++) {
          a[pos[it][l].first].s[pos[it][l].second] = "-+"[(cmask[it] >> l) & 1];
        }
      }
      for (int l = 0; l < 4; l++) ans[a[l].id] = a[l].s;
      break;
    }
  }
  return ans;
}

vector<string> solve2(vector<item> a) {
  vector<string> ans;

  auto was = a;
  vector<int> pos_0;
  for (int i = 0; i < (int)a[0].s.length(); i++) {
    if (a[0].s[i] == '?') {
      pos_0.push_back(i);
    }
  }
  vector<pair<int, int>> pos_oth;
  for (int i = 1; i <= 3; i++) {
    for (int j = 0; j < (int)a[i].s.length(); j++) {
      if (a[i].s[j] == '?') {
        pos_oth.push_back({i, j});
      }
    }
  }

  int cnt1 = 0, cnt2 = 0;
  for (int i = 0; i < (int)a[0].s.length(); i++) {
    if (i * 2 <= (int)a[0].s.length() - 1) cnt1 += a[0].s[i] == '?';
    if (i * 2 >= (int)a[0].s.length() - 1) cnt1 += a[0].s[i] == '?';
  }

  if (cnt1 <= cnt2) {
    for (int i = 0; i < (int)a[0].s.length(); i++) {
      if (i * 2 <= (int)a[0].s.length() - 1 && a[0].s[i] == '?') {
        pos_oth.push_back({0, i});
      }
    }
  } else {
    for (int i = 0; i < (int)a[0].s.length(); i++) {
      if (i * 2 >= (int)a[0].s.length() - 1 && a[0].s[i] == '?') {
        pos_oth.push_back({0, i});
      }
    }
  }

  for (int mask = 0; mask < (1 << ((int)pos_oth.size())); mask++) {
    a = was;
    for (int i = 0; i < (int)pos_oth.size(); i++) {
      assert(a[pos_oth[i].first].s[pos_oth[i].second] == '?');
      a[pos_oth[i].first].s[pos_oth[i].second] = "-+"[(mask >> i) & 1];
    }

    vector<int> bal(Z, 0);
    for (int i = 1; i <= 3; i++) {
      bal = sum(bal, mul(autocorel(a[i].s), a[i].coef));
    }
    bool fail = 0;
    for (int d = Z; d > 0; d--) {
      int val = bal[d - 1];

      int qpos = -1;
      int qcoef = -1;
      for (int i = 0; i < (int)a[0].s.length(); i++) {
        int j = i + d;
        if (j < (int)a[0].s.length()) {
          assert(a[0].s[i] != '?' || a[0].s[j] != '?');
          if (a[0].s[i] == '?') {
            assert(qpos == -1);
            qpos = i;
            qcoef = sign(a[0].s[j]);
          } else if (a[0].s[j] == '?') {
            qpos = j;
            qcoef = sign(a[0].s[i]);
          } else {
            val += sign(a[0].s[i]) * sign(a[0].s[j]) * a[0].coef;
          }
        }
      }
      if (qpos != -1) {
        if (abs(val) == a[0].coef) {
          val *= qcoef;
          assert(a[0].s[qpos] == '?');
          if (val > 0) a[0].s[qpos] = '-';
          else a[0].s[qpos] = '+';
          val = 0;
        } else {
          fail = 1;
          break;
        }
      }
      fail |= val != 0;
    }
    if (!fail) {
      ans.resize(4);
      for (int i = 0; i < 4; i++) ans[a[i].id] = a[i].s;
      break;
    }
  }
  return ans;
}

vector<string> solve(vector<string> aa) {
  vector<item> a;
  a.push_back({aa[0], 1, 0});
  a.push_back({aa[1], 1, 1});
  a.push_back({aa[2], 2, 2});
  a.push_back({aa[3], 2, 3});
  sort(a.begin(), a.end());
  reverse(a.begin(), a.end());

//  auto o = divide(a);

  vector<string> ans;
  if (qmark(a[0].s) <= 20) {
    ans = solve1(a);
  } else {
    ans = solve2(a);
  }

  db(clock() / (double)CLOCKS_PER_SEC);
  assert(!ans.empty());

  vector<int> bal(Z, 0);
  for (int i = 0; i < 4; i++) {
    assert(ans[i].length() == aa[i].length());
    for (int j = 0; j < (int)aa[i].size(); j++) {
      assert(ans[i][j] != '?');
      if (aa[i][j] != '?') {
        assert(aa[i][j] == ans[i][j]);
      }
    }
    bal = sum(bal, mul(autocorel(ans[i]), 1 + i / 2));
  }
//  dbv(bal);
  for (int i = 0; i < Z; i++) assert(bal[i] == 0);
  return ans;
}

void test() {
  vector<string> a(4);
  for (int i = 0; i < 4; i++) {
    a[i] = string(36, "-+"[i % 2]);
    int need = 10 * (int)(i < 3);
    for (int j = 0; j < need; j++) {
      if (j % 2 == 0) a[i][j / 2] = '?';
      else a[i][a[i].length() - 1 - j / 2] = '?';
    }
  }
  solve(a);
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
//  freopen("b.out", "w", stdout);
#endif

  test();

  vector<string> a(4);
  while (cin >> a[0]) {
    for (int i = 1; i < 4; i++) cin >> a[i];
    print(solve(a));

#ifdef LOCAL
    auto aa = a;
    for (int it = 0; it < 10; it++) {
      a = aa;
      int cnt = 0;
      for (int i = 0; i < 4; i++) cnt += qmark(a[i]);

      for (int i = 0; i < 20 - cnt; i++) {
        int id = rand() % 4;
        int j = rand() % a[id].length();
        a[id][j] = '?';
      }
      print(solve(a));
    }
#endif
  }

  return 0;
}
