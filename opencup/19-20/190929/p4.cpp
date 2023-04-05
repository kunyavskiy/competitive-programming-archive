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

map<string, int> mem;
vector<string> nam;
int get_num(string s) {
  if (mem.find(s) == mem.end()) {
    nam.push_back(s);
    mem[s] = mem.size();
  }
  return mem[s];
}

//struct mybitset {
//  vector<unsigned long long> a;
//  int n;
//  mybitset(int n): n(n) {
//    a.resize((n >> 6) + 1);
//  }
//  void set(int i) {
//    a[i >> 6] |= 1ull << (i & 63);
//  }
//};
const int N = 1000;
int n;
vector<bitset<N>> d(n);

vector<vector<int>> tree(1, {-1, -1});
vector<int> ask(1, -1);
vector<int> ans(1, -1);
void go(bitset<N> cur, int v) {
  int cn = cur.count();
  if (cn == 1) {
    ans[v] = cur._Find_first();
    return;
  }
  int u = -1;
  int best = -1;
  for (int i = 0; i < n; i++) {
    if (cur[i]) {
      bitset<N> nx = cur & d[i];
      int ccn = nx.count();
      ccn = max(ccn, cn - ccn);
      if (u == -1 || ccn < best) {
        u = i;
        best = ccn;
      }
    }
  }
  int vl = tree.size();
  tree.push_back({-1, -1});
  ans.push_back(-1);
  ask.push_back(-1);
  int vr = tree.size();
  tree.push_back({-1, -1});
  ans.push_back(-1);
  ask.push_back(-1);
  tree[v][0] = vl;
  tree[v][1] = vr;
  ask[v] = u;
  go(cur & d[u], vl);
  go(cur & (~d[u]), vr);
}

int main() {
//#ifdef LOCAL
//  freopen("p4.in", "r", stdin);
//  freopen("p4.out", "w", stdout);
//#endif

  ios_base::sync_with_stdio(false);
  cin >> n;
  vector<vector<int>> g(n);
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    int x = get_num(s);
    int k;
    cin >> k;
    for (int j = 0; j < k; j++) {
      cin >> s;
      int y = get_num(s);
      g[x].push_back(y);
    }
  }
  d.resize(n);
  for (int i = 0; i < n; i++) {
    d[i][i] = 1;
  }
  for (int i = 0; i < n; i++) {
    for (int j : g[i]) {
      d[i] |= d[j];
    }
  }

  bitset<N> st;
  for (int i = 0; i < n; i++) st[i] = 1;

  go(st, 0);

  while (true) {
    string s;
    cin >> s;
    assert(s == "bug");
    cin >> s;
    if (s == "000000") break;
    int c = 0;
    while (ans[c] == -1) {
      int u = ask[c];
      cout << "check " << nam[u] << endl;
      cin >> s;
      if (s == "bad") {
        c = tree[c][0];
      } else {
        c = tree[c][1];
      }
    }
    cout << "fix " << nam[ans[c]] << endl;
  }

  return 0;
}
