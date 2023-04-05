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

#define MAXN (400*1000)
#define MAX_NODES_COUNT (2 * MAXN + 100)

typedef struct _node{
  _node *l, *r, *p;
  int size;
  _node();
  explicit _node(nullptr_t){
    l = r = p = this;
    size = 0;
  }
  void update();
}* Node;
Node None = new _node(nullptr);
_node nodes[MAX_NODES_COUNT];
_node::_node(){
  l = r = p = None;
  size = 1;
}
void _node::update(){
  size = (this != None) + l->size + r->size;
  l->p = r->p = this;
}
void rotate(Node v){
  assert(v != None && v->p != None);
  Node u = v->p;
  if (v == u->l)
    u->l = v->r, v->r = u;
  else
    u->r = v->l, v->l = u;
  swap(u->p,v->p);
  if (v->p != None){
    assert(v->p->l == u || v->p->r == u);
    if (v->p->r == u) v->p->r = v;
    else v->p->l = v;
  }
  u->update(); v->update();
}
void bigRotate(Node v){
  assert(v->p != None);
  if (v->p->p != None){
    if ((v->p->l == v) ^ (v->p->p->r == v->p))
      rotate(v->p);
    else
      rotate(v);
  }
  rotate(v);
}
inline void Splay(Node v){
  while (v->p != None) bigRotate(v);
}

int NN = 0;

Node createNode() {
  static int nodes_cnt = 0;
  assert(nodes_cnt < MAX_NODES_COUNT);
  Node node = &nodes[nodes_cnt++];
  *node = _node();
  return node;
}

#define CNT(T) (T->size)

Node getByPos(Node T, int pos) {
  Node res;
  while (1) {
    if (T->l->size == pos) {
      res = T;
      break;
    }
    if (T->l->size < pos) {
      pos -= T->l->size + 1;
      T = T->r;
    } else {
      T = T->l;
    }
  }
  Splay(res);
  return res;
}

Node insert(Node T, int pos, Node n) {
  if (T == None) {
    return n;
  }
  if (T->size == pos) {
    n->l = T;
    n->update();
    return n;
  }
  Node x = getByPos(T, pos);
  n->l = x->l;
  n->r = x;
  x->l = None;
  x->update();
  n->update();
  return n;
}

int getPos(Node node) {
  Splay(node);
  return node->l->size;
}

int findNeigh(Node team, Node &q, int a) {
  int ans = -1;
  while (team != None) {
    int posQ = getPos(team + 1); // hack
    q = team + 1;
    if (posQ <= a) {
      ans = (team - nodes) / 2;
      team = team->r;
    } else {
      team = team->l;
    }
  }
  return ans;
}

void insertQueue(Node &q, Node &team, int id, Node nt, Node nq, int a) {
  int posQ = getPos(&nodes[2 * id + 1]);
  q = &nodes[2 * id + 1];
  assert(posQ <= a);
  int posT = getPos(&nodes[2 * id]);
  team = &nodes[2 * id];

  if (posQ < a) {
    posQ += 1;
    posT += 1;
  }
  q = insert(q, posQ, nq);
  team = insert(team, posT, nt);
}

void _printTree(Node T) {
  if (T != None) {
    _printTree(T->r);
    printf("%d ", (int)(T - nodes) / 2 + 1);
    _printTree(T->l);
  }
}

void printTree(Node T) {
  _printTree(T);
  printf("\n");
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector <Node> teams(n, None);
  Node q = None;
  int trash = 0;
  for (int i = 0; i < n; ++i) {
    int c, a;
    scanf("%d%d", &c, &a);
    Node nt = createNode();
    Node nq = createNode();

    --c;
    int id = findNeigh(teams[c], q, a);
    eprintf("c %d a %d id %d\n", c, a, id);
    if (id == -1) {
      teams[c] = insert(teams[c], 0, nt);
//      printf("==== %p %p\n", q, nq);
//      printTree(q);
      q = insert(q, 0, nq);
//      printTree(q);
//      printf("==== %p %p\n", q, nq);
    } else {
      insertQueue(q, teams[c], id, nt, nq, a);
    }

    NN++;
    trash += c + a;
#ifdef LOCAL2
    printTree(q);
#endif
  }
  eprintf("trash = %d\n", trash);

  printTree(q);

  return 0;
}
