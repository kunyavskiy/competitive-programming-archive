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

vector<int> pf(const string &s) {
    vector<int> p(s.size());
    int cur = 0;
    for (int i = 1; i < (int) s.size(); i++) {
        for (; cur && s[cur] != s[i]; cur = p[cur - 1]) {}
        if (s[cur] == s[i]) cur++;
        p[i] = cur;
    }
    return p;
}

vector<int> rpf(const string &s, const string& t, const vector<int>& p) {
    vector<int> pp(t.size() + 1);
    int cur = 0;
    for (int i = 0; i < (int) t.size(); i++) {
        for (; cur && s[cur] != t[i]; cur = p[cur - 1]) {}
        if (s[cur] == t[i]) cur++;
        pp[i + 1] = cur;
    }
    return pp;
}

struct Solver {
    int n;
    explicit Solver(int n) : n(n), qs(0) {}

    struct event {
        int x;
        int ly, ry;
        int id;
    };
    vector<event> events;
    int qs;

    void addQuery(int x, int y, int id) {
        events.push_back(event{x, y, y, id});
        qs++;
    }
    void addRect(int lx, int rx, int ly, int ry) {
        events.push_back(event{lx, ly, ry, -1});
        events.push_back(event{rx, ly, ry, -2});
    }

    vector<int> solve() {
        sort(events.begin(), events.end(), [](const event& a, const event& b) {
            return std::tie(a.x, a.id) < std::tie(b.x, b.id);
        });
        vector<int> ans(qs);
        vector<int> bit(n);
        auto add = [&](int pos, int v) {
            while (pos < n) {
                bit[pos] += v;
                pos = pos | (pos + 1);
            }
        };

        auto get = [&](int pos) {
            int res = 0;
            while (pos != -1) {
                res += bit[pos];
                pos = (pos & (pos + 1)) - 1;
            }
            return res;
        };
        for (auto e : events) {
            if (e.id == -1) {
                add(e.ly, 1);
                add(e.ry, -1);
            } else if (e.id == -2) {
                add(e.ly, -1);
                add(e.ry, 1);
            } else {
                ans[e.id] = get(e.ly);
            }
        }
        return ans;
    }
};


vector<pair<int, int>> order(vector<int> p) {
    vector<vector<int>> g(p.size() + 1);
    for (int i = 0; i < (int)p.size(); i++) {
        g[p[i]].push_back(i + 1);
    }
    vector<pair<int, int>> ans(p.size() + 1);
    int timer = 0;
    auto dfs = [&](auto dfs, int v) -> void {
        ans[v].first = timer++;
        for (int u : g[v]) {
            dfs(dfs, u);
        }
        ans[v].second = timer;
    };
    dfs(dfs, 0);
    return ans;
}

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  string s, t, p;
  while (cin >> s >> t >> p) {
      string rs = s;
      reverse(rs.begin(), rs.end());
      string rt = t;
      reverse(rt.begin(), rt.end());
      string rp = p;
      reverse(rp.begin(), rp.end());

      vector<int> pp = pf(p);
      vector<int> rpp = pf(rp);

      vector<int> sp = rpf(p, s, pp);
      vector<int> rsp = rpf(rp, rs, rpp);
      reverse(rsp.begin(), rsp.end());

      vector<pair<int, int>> po = order(pp);
      vector<pair<int, int>> rpo = order(rpp);

      Solver solver(p.size() + 1);
      for (int i = 0; i <= (int) s.size(); i++) {
          eprintf("[%d,%d] ", sp[i], rsp[i]);
          solver.addQuery(po[sp[i]].first, rpo[rsp[i]].first, i);
      }
      eprintf("\n");

      auto addRect = [&](int pref, int suf) {
          eprintf("Good if (pref = %d, suf = %d)\n", pref, suf);
          solver.addRect(po[pref].first, po[pref].second, rpo[suf].first, rpo[suf].second);
      };

      {
          //          ii
          // sssssttt[ttsss]ss
          vector<int> tp = rpf(p, t, pp);
          for (int i = tp.back(); i != 0; i = pp[i - 1]) {
              if (i != (int) p.size()) {
                  addRect(0, p.size() - i);
              }
          }
      }

      {
          //       iii
          // sss[ssttt]ttsssss
          vector<int> tp = rpf(rp, rt, rpp);
          for (int i = tp.back(); i != 0; i = rpp[i - 1]) {
              if (i != (int) p.size()) {
                  addRect(p.size() - i, 0);
              }
          }
      }
      {
          //     iiiiiii
          // sss[sstttttss]sss
          vector<int> tp = rpf(t, p, pf(t));
          for (int i = 0; i <= (int) p.size(); i++) {
              if (tp[i] == (int) t.size()) {
                  if (i != (int) t.size() && i != (int) p.size()) {
                      addRect(i - t.size(), p.size() - i);
                  }
              }
          }
      }

      vector<int> ans = solver.solve();
#ifdef LOCAL
      for (int x : ans) eprintf("%d ", x);
      eprintf("\n");
#endif
      {
          vector<int> tp = rpf(p, t, pp);
          int PinT = count(tp.begin(), tp.end(), p.size());
          for (int i = 0; i <= (int) s.size(); i++) {
              ans[i] += PinT;
          }
      }

      {
          int cur = 0;
          for (int i = 0; i <= (int) s.size(); i++) {
              if (sp[i] == (int) p.size()) cur++;
              ans[i] += cur;
          }
      }

      {
          int cur = 0;
          for (int i = (int)s.size(); i >= 0; i--) {
              if (rsp[i] == (int) p.size()) cur++;
              ans[i] += cur;
          }
      }
#ifdef LOCAL
      for (int i = 0; i <= (int) s.size(); i++) {
           string temp = s.substr(0, i) + t + s.substr(i);
           eprintf("%s should have %d time of %s\n", temp.c_str(), ans[i], p.c_str());
           vector<int> ppp = rpf(p, temp, pp);
           assert(ans[i] == count(ppp.begin(), ppp.end(), p.size()));
      }
#endif

      int max = *max_element(ans.begin(), ans.end());
      int count = 0, first = -1, last = -1;
      for (int i = 0; i < (int)ans.size(); i++) {
          if (ans[i] == max) {
              count++;
              if (first == -1) first = i;
              last = i;
          }
      }

      printf("%d %d %d %d\n",
             max, count, first, last
      );


  }

  return 0;
}
