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

const char card_names[] = "23456789TJQKA";

const int K = 5;
const int N = 13;

map<vector<int>, int> num;
vector<vector<int>> st;
vector<vector<int>> g;

int get_num(const vector<int>& v) {
  auto it = num.find(v);
  if (it != num.end()) {
    return it->second;
  }
  int x = num.size();
  g.push_back(vector<int>());
  st.push_back(v);
  return num[v] = x;
}

void print(const vector<int>& v, int off) {
  for (int i = 0; i < off; i++) eprintf(" ");
  for (int i : v) eprintf("%d ", i);
  eprintf("\n");
}

void go(vector<int> v, int n) {
  if (v.size() == n) {
    print(v, 0);
    int id = get_num(v);

    int lf = -1;
    for (int i = 1; i < n; i++) {
      if (v[i] < v[0]) {
        lf = max(lf, v[i]);
      }
    }

    int rg = N;
    for (int i = 1; i < n; i++) {
      if (v[i] > v[0]) {
        rg = min(rg, v[i]);
      }
    }


    for (int i = 0; i < N; i++) {
      if ((i < lf || i > rg) && find(v.begin(), v.end(), i) == v.end()) {
        int oldv = v[0];
        v[0] = i;
        rotate(v.begin(), v.end() - 1, v.end());
        int to = get_num(v);
        print(v, 2);
        rotate(v.begin(), v.begin() + 1, v.end());
        v[0] = oldv;
        g[id].push_back(to);
      }
    }
    return;
  }
  for (int i = 0; i < N; i++) {
    if (find(v.begin(), v.end(), i) == v.end()) {
      v.push_back(i);
      go(v, n);
      v.pop_back();
    }
  }
}

vector<int> ans;

int dfs(int v) {
  assert(v < (int)ans.size());
  if (ans[v] >= -1) return ans[v];
  if (ans[v] == -3) {
    return ans[v] = -1;
  }
  ans[v] = -3;
  int res = 1;
  for (int u : g[v]) {
    int r = dfs(u);
    if (r == -1) return ans[v] = -1;
    res = max(res, r + 1);
  }
  return ans[v] = res;
}

void solve(int n) {
  vector<int> real(n);
  for (int i = 0; i < n; ++i) {
    char ch;
    scanf(" %c", &ch);
    int j = 0;
    while (card_names[j] != ch) {
      assert(card_names[j]);
      ++j;
    }
    real[i] = j;
  }
  int ans = -1;
  for (int i = 0; i < n; i++) {
    int r = dfs(get_num(real));
    if (r != -1) {
      if (ans == -1 || ans > r + i) {
        ans = r + i;
      }
    }
    rotate(real.begin(), real.begin() + 1, real.end());
  }
  printf("%d\n", ans);
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int k, tt;
  scanf("%d%d", &k, &tt);
  vector<int> v;
  go(v, k);
  ans.resize(num.size(), -2);
  eprintf("%d\n", (int)num.size());
  for (int i = 0; i < tt; ++i) {
    solve(k);
  }

  return 0;
}
