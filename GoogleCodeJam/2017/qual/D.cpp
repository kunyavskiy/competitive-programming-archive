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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME ""
#define TASKMOD "dbg"

typedef long long ll;
typedef long double ld;

class Matching {
  vector<vector<int>> g;
  vector<int> mt;
  vector<bool> used;
  vector<int> lockl, lockr;
  int n;

  bool dfs(int v) {
    if (used[v]) { return false; }
    used[v] = true;
    for (int u : g[v]) {
      if (mt[u] == -1 || dfs(mt[u])) {
        mt[u] = v;
        return true;
      }
    }
    return false;
  }
public: 

  Matching(int n) {
    this->n = n;
    g.resize(n);
    mt.resize(n, -1);
    lockl = lockr = vector<int>(n, -1);
  }

  void lock(int l, int r) {
    lockl[l] = r;
    lockr[r] = l;
  }

  void addEdge(int a, int b) {
    if (lockl[a] != -1 && lockl[a] != b) return;
    if (lockr[b] != -1 && lockr[b] != a) return;
    g[a].push_back(b);
  }


  vector<pair<int, int>> get() {
    for (int i = 0; i < n; i++) {
      used = vector<bool>(n, false);
      dfs(i);
    }
    vector<pair<int, int>> res;
    for (int i = 0; i < n; i++) {
      if (mt[i] != -1) {
        res.push_back({mt[i], i});
      }
    }
    return res;
  }
};


void PreCalc(){
}

int s[200][200];
int ns[200][200];

const char *names = ".x+o";

void solve(){
  int n, k;
  scanf("%d%d", &n, &k);
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      ns[i][j] = s[i][j] = 0;
    }
  }

  Matching h(n), d(2 * n - 1);
  
  for (int i = 0; i < k; i++) {
    char c;
    int x, y;
    scanf(" %c %d %d", &c, &x, &y);
    --x, --y;
    s[x][y] = strchr(names, c) - names;
  }


  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (s[i][j] & 1) {
        h.lock(i, j);
      }
      if (s[i][j] & 2) {
        d.lock(i + j, i - j + n - 1);
      }
    }
  }
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      h.addEdge(i, j);
      d.addEdge(i + j, i - j + n - 1);
    }
  }

  for (const auto& x: h.get()) {
    ns[x.first][x.second] |= 1;
  }
  for (const auto& x: d.get()) {
    ns[(x.first + x.second - n + 1) / 2][(x.first - x.second + n - 1) / 2] |= 2;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      fprintf(stderr, "%c", names[ns[i][j]]);
    }
    fprintf(stderr, "\n");
  }
  
  int res = 0, cnt = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      res += __builtin_popcount(ns[i][j]);
      cnt += ns[i][j] != s[i][j];
    }
  }

  printf("%d %d\n", res, cnt);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (ns[i][j] != s[i][j]) {
        assert((ns[i][j] & s[i][j]) == s[i][j]);
        printf("%c %d %d\n", names[ns[i][j]], i + 1, j + 1);
      }
    }
  }
}


int main(){
  //freopen(TASKNAME"-"TASKMOD".in","r",stdin);
  //freopen(TASKNAME"-"TASKMOD".out","w",stdout);
	
  PreCalc();
  TIMESTAMP(PreCalc);	

  char buf[1000];
  int testNum;
  fgets(buf, sizeof buf, stdin);
  sscanf(buf,"%d",&testNum);

  for (int testId = 1; testId <= testNum; testId++){
  	if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
	  	TIMESTAMPf("Test %d",testId);
  	printf("Case #%d: ",testId);
  	solve();                        
  }
      
  TIMESTAMP(end);
  return 0;
}
