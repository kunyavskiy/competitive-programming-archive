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

const ll INF = 1e18;

ll solve(ll d, string s, vector<int> t) {
  int n = s.length();

  vector<int> left(n), right(n);
  int last = -1;
  for (int i = 0; i < n; i++) {
    left[i] = last;
    if (s[i] == 'I' || s[i] == 'P') last = i;
  }
  last = n;
  for (int i = n - 1; i >= 0; i--) {
    right[i] = last;
    if (s[i] == 'I' || s[i] == 'P') last = i;
  }

  vector<vector<int>> e(n);
  vector<int> ref(n, 1);
  for (int i = 0; i < n; i++) {
    if (s[i] == 'P' || s[i] == 'B') {
      ref[left[i]]++;
      e[i].push_back(left[i]);
    }
    if (s[i] == 'B') {
      ref[right[i]]++;
      e[i].push_back(right[i]);
    }
  }

  vector<int> order, used(n);
  for (int i = 0; i < n; i++) {
    if (used[i]) continue;
    if (s[i] == 'B' && !used[right[i]]) {
      used[right[i]] = 1;
      order.push_back(right[i]);
    }
    used[i] = 1;
    order.push_back(i);
  }
  //dbv(order);

  auto true_rev = ref;

  ll l = 0, r = n + 1;
  while (r - l > 1) {
    ll m = (l + r) / 2;

    ref = true_rev;
    int decoded = 0;
    int in_progress = 1;
    ll decoding_finish = -INF + t[order[0]];
    ll next_show = 0;
    ll cur_memory = 1;
    bool ok = 0;
    vector<int> is_decoded(n, 0);

    //db(m);
    while (true) {
      ll cur_time = min(decoding_finish, next_show);
      //db2(cur_time, decoded);
      //dbv(is_decoded);
      //dbv(ref);
      if (decoding_finish <= next_show) { // TODO
        in_progress = 0;
        for (int from : e[order[decoded]]) {
          ref[from]--;
          if (ref[from] == 0) {
            cur_memory--;
          }
        }
        is_decoded[order[decoded]] = 1;
        decoded++;
        decoding_finish = INF;
      } else {
        int id = next_show / d;
        if (id == n) {
          ok = 1;
          break;
        }
        if (!is_decoded[id]) {
          ok = 0;
          break;
        }
        ref[id]--;
        if (ref[id] == 0) {
          cur_memory--;
        }
        cur_time = next_show;
        next_show += d;
      }

      if (!in_progress && cur_memory < m && decoded < n) {
        cur_memory++;
        decoding_finish = cur_time + t[order[decoded]];
        in_progress = 1;
      }
    }
    //db(cur_memory);
    if (ok) r = m;
    else l = m;
  }

  return r;
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n, d;
  while (scanf("%d%d", &n, &d) == 2) {
    string s;
    vector<int> t(n);
    for (int i = 0; i < n; i++) {
      char c;
      scanf(" %c%d", &c, &t[i]);
      s += c;
    }

    cout << solve(d, s, t) << endl;
  }

  return 0;
}
