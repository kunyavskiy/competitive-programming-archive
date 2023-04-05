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

const int N = 450100;
const int LOG = 20;

char s[N];
int n;

vector<int> buildSuffixArray(const char *s, int n)
{
  vector <int> cnt(256, 0);
  vector <int> color(n);
  for (int i = 0; i < n; ++i)
    ++cnt[color[i] = s[i]];

  vector <int> h(256, 0);
  h[0] = 0;
  for (int i = 1; i < 256; ++i)
    h[i] = h[i - 1] + cnt[i - 1];

  vector <int> arr(n);
  for (int i = 0; i < n; ++i)
    arr[h[color[i]]++] = i;

  h[0] = 0;
  for (int i = 1; i < 256; ++i)
    h[i] = h[i - 1] + cnt[i - 1];

  vector <int> newColor(n);
  vector <int> newArr(n);

  for (int l = 1; l < n; l *= 2)
  {
    for (int i = 0; i < n; ++i)
    {
      int j = arr[i] - l;
      if (j < 0)
        j += n;
      newArr[h[color[j]]++] = j;
    }
    newColor[newArr[0]] = 0;
    h.clear();
    h.push_back(0);
    for (int i = 1; i < n; ++i)
    {
      int j1 = newArr[i] + l;
      if (j1 >= n) j1 -= n;

      int j2 = newArr[i - 1] + l;
      if (j2 >= n) j2 -= n;

      if (color[newArr[i]] == color[newArr[i - 1]] && color[j1] == color[j2])
        newColor[newArr[i]] = newColor[newArr[i - 1]];
      else
      {
        newColor[newArr[i]] = newColor[newArr[i - 1]] + 1;
        h.push_back(i);
      }
    }

    newColor.swap(color);
    newArr.swap(arr);

    if (color[arr.back()] == n - 1)
      break;
  }

  return arr;
}
int mins[LOG][N];


vector <int> num;

vector <int> buildLcp(const char * s, int n, const vector <int> & arr)
{
  vector <int> lcp(n - 1);
  num.resize(n);
  for (int i = 0; i < n; ++i)
    num[arr[i]] = i;

  int z = 0;
  for (int i = 0; i < n; ++i)
  {
    int j = num[i];
    if (j == n - 1)
      continue;
    while (s[i + z] == s[arr[j + 1] + z])
      ++z;
    lcp[j] = z;
    if (z > 0)
      --z;
  }

  for (int i = 0; i < n - 1; i++) {
    mins[0][i] = lcp[i];
  }
  for (int j = 1; j < LOG; j++) {
    int len = n - (1 << j);
    for (int i = 0; i < len; i++) {
      mins[j][i] = min(mins[j - 1][i], mins[j - 1][i + (1 << (j - 1))]);
    }
  }

  return lcp;
}

int calclcp(int x, int y) {
  if (x == y) {
    return n - x;
  }
  x = num[x];
  y = num[y];
  if (y < x) {
    int t = x;
    x = y;
    y = t;
  }
  int d = y - x;
  int k = 0;
  while (1 << (k + 1) <= d) k++;
  return min(mins[k][x], mins[k][y - (1 << k)]);
}

vector<vector<int>> child;
vector<ll> c;
ll m;

void dfs(int x) {
  ll ss = 1;
  for (int y: child[x]) {
    dfs(y);
    ss = (ss * c[y]) % m;
  }
  c[x] = (c[x] + ss) % m;
}

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  int q;
  scanf("%d%d", &n, &q);
  scanf(" %s", s);

  vector <int> arr = buildSuffixArray(s, n + 1);
  vector <int> lcp = buildLcp(s, n + 1, arr);

  for (int iii = 0; iii < q; iii++) {
    int k;
    scanf("%d%lld", &k, &m);
    vector<pair<int, int>> p(k);
    for (int i = 0; i < k; i++) {
      scanf("%d%d", &p[i].first, &p[i].second);
      p[i].second = p[i].second - p[i].first + 1;
      p[i].first = num[p[i].first - 1];
    }
    sort(p.begin(), p.end());
    map<int, int> path;
    vector<int> parent(1, -1);
    c.clear();
    c.resize(1);
    int nv = 1;
    path[0] = 0;
    int ps = 0;
    int plen = 0;
    for (auto pp : p) {
      int s = arr[pp.first];
      int len = pp.second;
      int pref = calclcp(s, ps);
//      cout << string(::s + s, ::s + s + len) << " " << string(::s + ps, ::s + ps + plen) << " " << pref << endl;
      pref = min(pref, len);
      pref = min(pref, plen);
      auto it = path.lower_bound(pref);
      int v;
      if (it->first == pref) {
        v = it->second;
      } else {
        auto it0 = it;
        --it0;
        int prev = it0->second;
        int next = it->second;
        parent.push_back(prev);
        c.push_back(0);
        parent[next] = nv;
        path[pref] = nv;
        v = nv;
        nv++;
      }
      if (pref == len) {
        c[v]++;
      } else {
        while (path.rbegin()->second != v) {
          auto it = path.end();
          --it;
          path.erase(it);
        }
        parent.push_back(v);
        c.push_back(1);
        path[len] = nv;
        nv++;
        ps = s;
        plen = len;
      }
//      for (int i = 0; i < nv; i++) {
//        cout << parent[i] << " " << c[i] << endl;
//      }
//      cout << " " << len << " " << pref << endl;

    }
    child.clear();
    child.assign(nv, vector<int>(0));
    for (int i = 1; i < nv; i++) {
      child[parent[i]].push_back(i);
    }
    dfs(0);
    cout << (c[0] % m) << endl;
  }

  return 0;
}
