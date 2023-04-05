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

ll calc(vector<pair<int, int>> &a) {
  int n = (int)a.size();
  vector<ll> d(n);
  vector<ll> s(n);
  vector<ll> dd(n);
  for (int i = 0; i < n; i++) {
    d[i] = a[i].second;
    s[i] = a[i].second;
  }
  for (int l = 1; l < n; l++) {
    for (int i = 0; i + l < n; i++) {
      s[i] += a[i + l].second;
    }
    for (int i = 0; i < n - l; i++) {
      dd[i] = max(d[i] + s[i], d[i + 1] + s[i]);
    }
    for (int i = 0; i < n - l; i++) {
      d[i] = dd[i];
    }
  }
  return d[0];
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    a[i]--;
  }

  vector<bool> was(m);
  vector<pair<int, int>> st;
  ll res = 0;
  for (int i = 0; i < n; i++) {
    if (st.size() > 0 && st[st.size() - 1].first == a[i]) {
      st[st.size() - 1].second++;
    } else {
      if (was[a[i]]) {
        vector<pair<int, int>> temp;
        int s = 0;
        while (st[st.size() - 1].first != a[i]) {
          temp.push_back(st[st.size() - 1]);
          s += st[st.size() - 1].second;
          st.pop_back();
        }
        st[st.size() - 1].second += (s + 1);
        res += calc(temp);
      } else {
        st.push_back({a[i], 1});
        was[a[i]] = true;
      }
    }
  }
  res += calc(st);

  cout << res << endl;

  return 0;
}
