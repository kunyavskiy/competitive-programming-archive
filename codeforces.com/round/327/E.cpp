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

#define TASKNAME "E"

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

#define NO_NODE -2
#define MANY_NODES -1

const int MAXLEN = 10000100;
const int MAXNEXTS = 26*1000;

struct node {
  int lnk;
  int next;
  int nextc;
  int id;
};

int nexts[MAXNEXTS];
node ns[MAXLEN];
int nsptr;
int nexts_ptr;

int get_node() {
  ns[nsptr].lnk = -1;
  ns[nsptr].next = -1;
  ns[nsptr].nextc = NO_NODE;
  ns[nsptr].next = -1;
  return nsptr++;
}

int go(int id, int c, int force) {
  if (ns[id].nextc == NO_NODE) {
    if (!force) return -1;
    ns[id].nextc = c;
    return ns[id].next = get_node();
  }
  if (ns[id].nextc == MANY_NODES) {
    assert(ns[id].next != -1);
    int& nv = nexts[ns[id].next + c];
    if (!force) return nv;
    return nv = get_node();
  }
  if (ns[id].nextc == c)
    return ns[id].next;
  if (!force) {
    return -1;
  }
  int tmp = ns[id].next;
  ns[id].next = nexts_ptr;
  memset(nexts + nexts_ptr, -1, 26 * sizeof(nexts[0]));
  nexts_ptr += 26;
  assert(nexts_ptr <= MAXNEXTS);
  nexts[ns[id].next + ns[id].nextc] = tmp;
  ns[id].nextc = MANY_NODES;
  return nexts[ns[id].next + c] = get_node();
}

int root;

void add(char* s, int id) {
  int cur = root;
  for (int i = 0; s[i]; i++) {
    cur = go(cur, s[i] - 'a', 1);
  }
  ns[cur].id = id;
}

void get_lnk(int v, int p, int c) {
  eprintf("get_link(%d, %d, %d)\n", v, p, c);
  int cur = ns[p].lnk;
  while (cur != root) {
    int nv = go(cur, c, 0);
    if (nv != -1) {
      ns[v].lnk = cur;
      if (ns[v].id == -1 && ns[ns[v].lnk].id != -1) {
        ns[v].id = ns[ns[v].lnk].id;
      }
    }
  }
}

void build() {
  queue<int> q;
  ns[root].lnk = root;
  for (int i = 0; i < 26; i++){
    int nv = go(root, i, 0);
    if (nv != -1) {
      q.push (nv);
      ns[nv].lnk = root;
    }
  }

  while (!q.empty()) {
    int v = q.front();
    assert(v != root);
    q.pop();
    assert(ns[v].lnk != -1);
    if (ns[v].nextc == NO_NODE) continue;
    if (ns[v].nextc == MANY_NODES) {
      for (int i = 0; i < 26; i++) {
        int nv = go(root, i, 0);
        if (nv != -1) {
          eprintf("%d,%d -> %d\n", v, i, nv);
          q.push (nv);
          get_lnk (nv, v, i);
        }
      }
      continue;
    }
    int i = ns[v].nextc;
    int nv = go(root, i, 0);
    eprintf("%d,%d -> %d\n", v, i, nv);
    assert(nv != -1);
    q.push(nv);
    get_lnk(nv, v, i);
  }
}

char buf[MAXLEN];
const int MAXN = 750;
string s[MAXN];

int have[MAXN][MAXN];

int main() {
  #ifdef LOCAL
  assert(freopen (TASKNAME".in", "r", stdin));
  assert(freopen (TASKNAME"out", "w", stdout));
  #endif

  root = get_node ();
  int n;
  scanf ("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf ("%s", buf);
    s[i] = buf;
    add(buf, i);
  }

  build();
  eprintf("builded\n");

  for (int i = 0; i < n; i++) {
    int len = (int)s[i].size();
    int cur = root;
    for (int j = 0; j < len; j++) {
      int nv = -1;
      while (cur != root) {
        nv = go(cur, s[i][j] - 'a', 0);
        if (nv != -1) {
          break;
        }
        cur = ns[cur].lnk;
      }
      if (nv == -1) {
        cur = root;
        continue;
      }
      cur = nv;
      if (ns[cur].id != -1) {
        have[i][ns[cur].id] = 1;
      }
    }
  }

  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        have[i][j] |= have[i][k] && have[k][j];

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      printf("%d%c", have[i][j], " \n"[j==n-1]);
  
      
  return 0;
}
