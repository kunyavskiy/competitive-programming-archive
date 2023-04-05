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

const int MAXN = 1100000;

typedef struct _node{
  _node *l, *r, *p, *pp;
  int size; bool rev;
  int max, value;
  _node();
  explicit _node(nullptr_t){
    l = r = p = pp = this;
    size = rev = 0;
    max = -1;
  }
  void push(){
    if (rev){
      l->rev ^= 1; r->rev ^= 1;
      rev = 0; swap(l,r);
    }
  }
  void update();
}* node;
node None = new _node(nullptr);
node v2n[MAXN];

_node::_node(){
  l = r = p = pp = None;
  size = 1; rev = false;
}
void _node::update(){
  size = (this != None) + l->size + r->size;
  if (this != None) {
    max = std::max(value, std::max(l->max, r->max));
  }
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
vector<vector<int>> g;
int n;

inline void link(int x,int y){
//  eprintf("add %d %d\n", x, y);
  if (x > y) swap(x, y);
  if (y != n) g[y].push_back(x);
  makeRoot(x); v2n[x]->pp = v2n[y];
}
inline void cut(int x,int y){
//  eprintf("cut %d %d\n", x, y);
  if (x > y) swap(x, y);
  if (y != n) {
    auto it = find(g[y].begin(), g[y].end(), x);
    assert(it != g[y].end());
    g[y].erase(it);
  }
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
inline int get(int x,int y){
  if (x == y) return 0;
  makeRoot(x);
  expose(y); expose(x);
  Splay(v2n[y]);
  if (v2n[y]->pp != v2n[x]) return -1;
  return v2n[y]->size;
}

inline void print(node n) {
  if (n == None) return;
  if (n->rev) {
    print(n->r);
  } else {
    print(n->l);
  }
  eprintf("%d ", n->value);
  if (n->rev) {
    print(n->l);
  } else {
    print(n->r);
  }
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  int q;
  scanf("%d%d", &n, &q);
  vector<set<int>> sets(n);
  vector<int> cur(n);

  for (int i = 0; i < n; i++) {
    scanf("%d", &cur[i]);
    sets[cur[i]].insert(i);
  }

  for (int i = 0; i <= n; i++) {
    v2n[i] = new _node();
    v2n[i]->value = i;
    v2n[i]->update();
  }

  auto upper = [&](int v, int l) {
    if (v >= n)
      return n;
    auto it = sets[v].upper_bound(l);
    if (it == sets[v].end()) {
      return n;
    }
    return *it;
  };

  auto prev = [&](int v, int l) {
    if (v == -1)
      return -1;
    auto it = sets[v].lower_bound(l);
    if (it == sets[v].begin()) {
      return -1;
    }
    return *(--it);
  };


  auto get_edge = [&](int i) {
    return min(upper(cur[i], i), upper(cur[i] + 1, i));
  };

  g.resize(n);

  for (int i = 0; i < n; i++) {
    int id = get_edge(i);
    link(i, id);
  }

  for (int i = 0; i < q; i++) {
    int ty;
    scanf("%d", &ty);
    if (ty == 1) {
      int x, y;
      scanf("%d%d", &x, &y);
      vector<int> to_recalc = g[x];
      to_recalc.push_back(x);
      int pv = prev(y, x);
      int pv1 = prev(y - 1, x);
      if (pv != -1) to_recalc.push_back(pv);
      if (pv1 != -1) to_recalc.push_back(pv1);
      sort(to_recalc.begin(), to_recalc.end());
      to_recalc.erase(unique(to_recalc.begin(), to_recalc.end()), to_recalc.end());

      for (int v : to_recalc) {
        cut(v, get_edge(v));
      }

      sets[cur[x]].erase(x);
      cur[x] = y;
      sets[cur[x]].insert(x);

      for (int v : to_recalc) {
        link(v, get_edge(v));
      }

    } else {
      int l, r, k;
      scanf("%d%d%d", &l, &r, &k);
      makeRoot(n);
      int start = upper(k, l - 1);
      expose(start);
      node nd = v2n[start];
//      print(n);
//      eprintf("\n");
      node pn = nd;
      node ans = nd;
      while (true) {
        nd->push();
        if (nd->value >= r) {
          nd = nd->r;
        } else {
          ans = nd;
          nd = nd->l;
        }
        if (nd == None) {
          Splay(pn);
          break;
        } else {
          pn = nd;
        }
      }
      printf("%d\n", (ans->value == n) ? -1 : cur[ans->value]);
    }
  }

  return 0;
}
