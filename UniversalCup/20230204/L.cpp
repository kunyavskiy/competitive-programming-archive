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



bool solve() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    vector<int> a(n);
    for (int& x: a) { scanf("%d", &x); x--;}
    vector<int> b(m);
    for (int& x: b) { scanf("%d", &x); x--;}
    multiset<int> s;
    for (int i = 0; i < k; i++) {
        int l; scanf("%d", &l);
        s.insert(l);
    }
    vector<bool> is_removed(n);
    int ptr = 0;
    for (int i = 0; i < n; i++) {
        if (ptr < m && b[ptr] == a[i]) {
            ptr++;
        } else {
            is_removed[i] = true;
        }
    }
    if (ptr != m) {
        return false;
    }

    auto get_len = [&] {
        vector<int> stack;
        vector<int> pos;
        stack.push_back(std::numeric_limits<int>::max());
        pos.push_back(-1);
        vector<int> lf(n);
        for (int i = 0; i < n; i++) {
             if (is_removed[i]) {
                 lf[i] = pos[lower_bound(stack.begin(), stack.end(), a[i], greater<>()) - stack.begin() - 1];
             } else {
                 while (stack.back() < a[i]) {
                     stack.pop_back();
                     pos.pop_back();
                 }
                 stack.push_back(a[i]);
                 pos.push_back(i);
             }
        }
        return lf;
    };

    vector<int> bit(n);
    auto add = [&](int pos) {
        while (pos < n) {
            bit[pos]++;
            pos = pos | (pos + 1);
        }
    };
    auto get = [&](int pos) {
        int ans = 0;
        while (pos != -1) {
            ans += bit[pos];
            pos = (pos & (pos + 1)) - 1;
        }
        return ans;
    };

    vector<int> lf = get_len();
    reverse(a.begin(), a.end());
    reverse(is_removed.begin(), is_removed.end());
    vector<int> rg = get_len();
    reverse(rg.begin(), rg.end());
    reverse(a.begin(), a.end());
    reverse(is_removed.begin(), is_removed.end());
    for (int& x : rg) x = n - x - 1;
    vector<pair<int, int>> todo;

    for (int i = 0; i < n; i++) {
        if (is_removed[i]) {
            todo.emplace_back(a[i], i);
        }
    }
    eprintf("=====");

    sort(todo.rbegin(), todo.rend());
    for (auto [val, pos] : todo) {
        int len = rg[pos] - lf[pos] - 1 - (get(rg[pos] - 1) - get(lf[pos]));
        eprintf("%d by at most %d [%d, %d]\n", val, len, lf[pos], rg[pos]);
        auto it = s.upper_bound(len);
        if (it == s.begin()) return false;
        eprintf("%d\n", *it);
        --it;
        s.erase(it);
        add(pos);
    }
    return true;
}

int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
      if (solve()) printf("YES\n"); else printf("NO\n");
  }

  return 0;
}
