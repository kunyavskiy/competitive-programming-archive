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
  freopen("i.in", "r", stdin);
//  freopen("i.out", "w", stdout);
#endif

  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    ll k;
    int m;
    scanf("%d%lld%d", &n, &k, &m);
    vector<pair<ll, int>> a(n);
    for (int i = 0; i < n; i++) {
      scanf("%lld", &a[i].first);
      a[i].second = i + 1;
    }
    sort(a.begin(), a.end());

    vector<ll> s(n + 1);
    for (int i = 0; i < n; i++) {
      s[i + 1] = s[i] + a[i].first;
    }


    vector<pair<int, ll>> ans;
    struct state {
      ll sum;
      vector<pair<int, int>> vct;

      bool operator< (const state &s) const {
        if (sum != s.sum) return sum < s.sum;
//        if (vct.size() != s.vct.size()) return vct.size() < s.vct.size();
//        for (int i = (int)vct.size() - 1; i >= 0; i--) {
//          if (vct[i].second != s.vct[i].second) {
//            return vct[i].second > s.vct[i].second;
//          }
//          if (vct[i].first != s.vct[i].first) {
//            return vct[i].first < s.vct[i].first;
//          }
//        }
        int i = (int)vct.size() - 1;
        int j = (int)s.vct.size() - 1;
        while (i >= 0 && j >= 0) {
          if (vct[i] != s.vct[j]) {
            if (vct[i].second != s.vct[j].second) {
              return vct[i].second < s.vct[j].second;
            }
            return vct[i].first > s.vct[j].first;
          } else {
            i--;
            j--;
          }
        }
        if (i >= 0) return 1;
        return 0;
      }
      bool operator== (const state &s) const {
        return vct == s.vct && sum == s.sum;
      }
      bool operator> (const state &s) const {
        return !(*this == s) && !(*this < s);
      }
    };
    auto make_state = [&](vector<pair<int, int>> vct) {
      state res;
      res.vct = vct;
      res.sum = 0;
      for (auto o : vct) {
        res.sum += s[o.second + 1] - s[o.first];
      }
      return res;
    };
    state last;

//    set<state> used;
    for (int cnt = n; cnt >= 1; cnt--) {
      priority_queue<state, vector<state>, greater<>> st;
      state cur = make_state(vector<pair<int, int>>(1, {0, cnt - 1}));
      if (cur.sum <= k) {
        st.push(cur);
      }

      while (!st.empty() && (int)ans.size() < m) {
        last = st.top();
        ans.emplace_back(cnt, last.sum);
        st.pop();
        while (!st.empty() && st.top() == last) {
          st.pop();
        }
//        auto cst = st;
//        db(last.sum);
//        while (!cst.empty()) {
//          db(cst.top().sum);
//          cst.pop();
//        }

        int csum = 0;
        for (int i = 0; i < (int)last.vct.size(); i++) {
          csum += last.vct[i].second - last.vct[i].first + 1;

          int x = last.vct[i].second;
          int y = i + 1 < (int)last.vct.size() ? last.vct[i + 1].first : n;
          if (x + 1 < y) {
            vector<pair<int, int>> nvct;
            if (csum > 1) {
              nvct.emplace_back(0, csum - 2);
            }
            nvct.emplace_back(x + 1, x + 1);
            for (int j = i + 1; j < (int)last.vct.size(); j++) {
              if (last.vct[j].first == nvct.back().second + 1) {
                nvct.back().second = last.vct[j].second;
              } else {
                nvct.push_back(last.vct[j]);
              }
            }
            auto nstate = make_state(nvct);
            if (nstate.sum <= k && last < nstate) {
              st.push(nstate);
//              db2(last.sum, nstate.sum);
            }
          }
        }
      }
    }
    printf("%d\n", (int)ans.size());
    if (!ans.empty()) {
      for (auto o : ans) printf("%d %lld\n", o.first, o.second);
      vector<int> v;
      for (auto o : last.vct) for (int i = o.first; i <= o.second; i++) v.push_back(a[i].second);
      for (int i = 0; i < (int)v.size(); i++) printf("%d%c", v[i], " \n"[i + 1 == (int)v.size()]);
    }
  }

  return 0;
}
