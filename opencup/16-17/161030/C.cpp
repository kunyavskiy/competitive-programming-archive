//#include <iostream>
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
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "C"

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

typedef vector<vector<int>> vvi;

vvi create(int size) {
  return vvi(size, vector<int>(size, 1e9));
}

ll compress(vvi &v) {
  ll ans = 0;
  while (v.size() > 10u) {
    int id = 5;
    int mid = min_element(v[id].begin(), v[id].end()) - v[id].begin();
    assert(id != mid);
    ans += v[id][mid];
    for (int i = 0; i < (int)v[mid].size(); i++) {
      v[mid][i] = v[i][mid] = min(v[mid][i], v[id][i]);
    }
    v[mid][mid] = 1e9;
    v.erase(v.begin() + id);
    for (int i = 0; i < (int)v.size(); i++) {
      v[i].erase(v[i].begin() + id);
    }
  }
  return ans;
}

ll compress2(vvi &v) {
  ll ans = 0;
  while (v.size() > 1u) {
    int id = 0;
    int mid = min_element(v[id].begin(), v[id].end()) - v[id].begin();
    ans += v[id][mid];
    for (int i = 0; i < (int)v[mid].size(); i++) {
      v[mid][i] = v[i][mid] = min(v[mid][i], v[id][i]);
    }
    v[mid][mid] = 1e9;
    v.erase(v.begin() + id);
    for (int i = 0; i < (int)v.size(); i++) {
      v[i].erase(v[i].begin() + id);
    }
  }
  return ans;
}



vvi join(const vvi &l, const vvi& m, const vvi&r) {
  vvi res = create(l.size() + r.size());

  for (int i = 0; i < (int)l.size(); i++){
    for (int j = 0; j < (int)l.size(); j++) {
      res[i][j] = l[i][j];
    }
  }
  
  for (int i = 0; i < (int)r.size(); i++){
    for (int j = 0; j < (int)r.size(); j++) {
      res[i + l.size()][j + l.size()] = r[i][j];
    }
  }

  for (int i = 0; i < (int)m.size(); i++) {
    for (int j = 0; j < (int)m.size(); j++) {
      int idi = l.size() - m.size() + i;
      int idj = l.size() + j;
      if (idi >= 0 && idj < (int)res.size()) {
        res[idi][idj] = m[i][j];
        res[idj][idi] = m[i][j];
      }
    }
  }

  return res;
}

const int LIMIT = 64;

void solve(int N, int seed)
{
  int n = min(N, LIMIT);
  vvi g = create(n);

  int x = seed;
  for (int i = 1; i < n; i++)
  {
    x=x * 907 % 2333333;
    int T = x;
    for (int j = max(0, i - 5); j <= i-1; j++)
    {
      x = x * 907 % 2333333;
      int w = T ^ x;
      g[i][j] = g[j][i] = w;
    }
  }
  if (n < LIMIT) {
    ll ans = compress(g);
    printf("%lld\n", ans + compress2(g));
    return;
  }

  vvi inner = create(5);
  vvi start = create(5);
  vvi common = create(54);
  vvi end = create((N - 5) % 54);


  for (int i = 0; i < 54; i++) {
    for (int j = 0; j < 54; j++) {
      common[i][j] = g[i + 5][j + 5];
      if (i < (int)end.size() && j < (int)end.size()) {
        end[i][j] = g[i + 5][j + 5];
      }
    }
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      inner[i][j] = g[59 - 5 + i][59 + j];
    }
  }
  
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      assert(inner[i][j] == g[5 - 5 + i][5 + j]);
    }
  }
  
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      start[i][j] = g[i][j];
    }
  }
  
  int cnt = (N - 5) / 54;

  vector<vvi> parts;
  parts.push_back(start);


  long long ans = 0;
  ans += compress(common) *  cnt;

  while (cnt > 0) {
    if (cnt & 1) {
      parts.push_back(common);
    }
    common = join(common, inner, common);
    cnt /= 2;
    ans += compress(common) * cnt;
  }
    
  while (cnt--) {
    parts.push_back(common);
  }

  parts.push_back(end);

  vvi res = parts[0];
  for (int i = 1; i < (int)parts.size(); i++) {
    res = join(res, inner, parts[i]);  
  }

/*  while (parts.size() > 1) {
    vvi a = parts.back();
    parts.pop_back();
    vvi b = parts.back();
    parts.pop_back();
    vvi res = join(b, inner, a);
    ans += compress(res);
    parts.push_back(res);
  }*/

  ans += compress2(res);
  
  printf("%lld\n", ans);

  return;
}



int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
#endif
  
  int t;
  scanf("%d", &t);

  while (t-- > 0) {
    int n, seed;
    scanf("%d%d", &n, &seed);
    solve(n, seed);
  }

  return 0;
}
