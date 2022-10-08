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


const int MAXN = 1100000;

typedef struct _node{
  _node *l, *r, *p, *pp;
  int size; int w; bool rev;
  _node();
  explicit _node(nullptr_t){
    l = r = p = pp = this;
    size = w = 0;
    rev = 0;
  }
  void push(){
    if (rev){
      l->rev ^= 1; r->rev ^= 1;
      rev = false; swap(l,r);
    }
  }
  void update();
}* node;
node None = new _node(nullptr);
node v2n[MAXN];
_node::_node(){
  l = r = p = pp = None;
  size = 1; w = 0; rev = false;
}
void _node::update(){
  size = this->w + l->size + r->size;
  l->p = r->p = this;
}
void rotate(node v){
  assert(v != None && v->p != None);
  assert(!v->rev); assert(!v->p->rev);
  node u = v->p;
  if (v == u->l)
    u->l = v->r, v->r = u;
  else
    u->r = v->l, v->l = u;
  swap(u->p,v->p); swap(v->pp,u->pp);
  if (v->p != None){
    assert(v->p->l == u || v->p->r == u);
    if (v->p->r == u) v->p->r = v;
    else v->p->l = v;
  }
  u->update(); v->update();
}
void bigRotate(node v){
  assert(v->p != None);
  v->p->p->push();
  v->p->push();
  v->push();
  if (v->p->p != None){
    if ((v->p->l == v) ^ (v->p->p->r == v->p))
      rotate(v->p);
    else
      rotate(v);
  }
  rotate(v);
}
inline void Splay(node v){
  while (v->p != None) bigRotate(v);
}
inline void splitAfter(node v){
  v->push();
  Splay(v);
  v->r->p = None;
  v->r->pp = v;
  v->r = None;
  v->update();
}
void expose(int x){
  node v = v2n[x];
  splitAfter(v);
  while (v->pp != None){
    assert(v->p == None);
    splitAfter(v->pp);
    assert(v->pp->r == None);
    assert(v->pp->p == None);
    assert(!v->pp->rev);
    v->pp->r = v;
    v->pp->update();
    v = v->pp;
    v->r->pp = None;
  }
  assert(v->p == None);
  Splay(v2n[x]);
}
inline void makeRoot(int x){
  expose(x);
  assert(v2n[x]->p == None);
  assert(v2n[x]->pp == None);
  assert(v2n[x]->r == None);
  v2n[x]->rev ^= 1;
}
inline void link(int x,int y){
  eprintf("+ %d %d\n", x, y);
  makeRoot(x); v2n[x]->pp = v2n[y];
}
inline void cut(int x,int y){
  eprintf("- %d %d\n", x, y);
  expose(x);
  Splay(v2n[y]);
  if (v2n[y]->pp != v2n[x]){
    swap(x,y);
    expose(x);
    Splay(v2n[y]);
    assert(v2n[y]->pp == v2n[x]);
  }
  v2n[y]->pp = None;
}

_node mem[MAXN];
int n;

int any(node v) {
  if (v->w == 1) {
    assert(v - mem >= n);
    return v - mem - n;
  }
  if (v->l->size) {
    return any(v->l);
  }
  assert(v->r->size);
  return any(v->r);
}

void dump_int(node v) {
  if (v == None) return;
  v->push();
  dump_int(v->l);
  eprintf(" %d[%d:%d]", (int)(v - mem), v->w, v->size);
  dump_int(v->r);
}

void dump(node v) {
  dump_int(v);
  eprintf("\n");
}

inline int get(int x,int y){
  if (x == y) return 0;
  makeRoot(x);
  expose(y); expose(x);
  Splay(v2n[y]);
//  dump(v2n[y]);
  assert(v2n[y]->pp == v2n[x]);
  assert(v2n[y]->size);
  return any(v2n[y]);
}
// END ALGO


vector<tuple<int, int, int>> x;


int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  scanf("%d", &n);
  for (int i = 0; i < 2 * n - 1; i++) {
    v2n[i] = &mem[i];
    v2n[i]->w = v2n[i]->size = i >= n;
  }


  vector<vector<int>> g(n);
  vector<vector<int>> g2(n);

  for (int i = 0; i < n - 1; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  vector<int> a(n - 1);
  vector<int> b(n - 1);
  for (int i = 0; i < n - 1; i++) {
    scanf("%d%d", &a[i], &b[i]);
    --a[i], --b[i];
    link(a[i], i + n);
    link(b[i], i + n);
    g2[a[i]].emplace_back(i);
    g2[b[i]].emplace_back(i);
  }

  printf("%d\n", n - 1);

  auto merge = [&](int u, int v) {
    int id = get(v, u);
    printf("%d %d %d %d\n", u + 1, v + 1, a[id] + 1, b[id] + 1);
    cut(u, id + n);
    cut(v, id + n);
    a[id] = b[id] = -1;
    link(u, v);
    if (g[u].size() > g[v].size()) {
      swap(u, v);
    }
    bool found = false;
    for (auto x : g2[u]) {
      if (x == id) {
        found = true;
      }
      if (a[id] == -1) continue;
      cut(u, x + n);
      g2[v].push_back(x);
      link(v, x + n);
    }
    assert(found);
    g2[u].clear();
  };

  function<void(int, int)> dfs = [&](int v, int p) {
    for (int u : g[v]) {
      if (u == p) continue;
      merge(u, v);
      dfs(u, v);
    }
  };

  dfs(0, -1);


  return 0;
}
