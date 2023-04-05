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

struct Node {
  int id, y;
  int cnt;
  Node *L, *R, *par;

  Node() {}
  Node(int id, int y) : id(id), y(y) {
    cnt = 1;
    L = R = NULL;
    par = NULL;
  }
};

#define MAXN (400*1000)
#define MAX_NODES_COUNT (2 * MAXN + 100)
Node nodes[MAX_NODES_COUNT];

Node *createNode(int id) {
  static int nodes_cnt = 0;
  assert(nodes_cnt < MAX_NODES_COUNT);
  Node *node = &nodes[nodes_cnt++];
  *node = Node(id, rand());
  return node;
}

#define CNT(T) ((T) ? (T)->cnt : 0)

void update(Node *T) {
  if (!T) { return; }
  T->cnt = CNT(T->L) + CNT(T->R) + 1;
  if (T->L) {
    T->L->par = T;
  }
  if (T->R) {
    T->R->par = T;
  }
}

Node *merge(Node *L, Node *R) {
  if (!L) { return R; }
  if (!R) { return L; }
  if (L->y > R->y) {
    L->R = merge(L->R, R);
    update(L);
    return L;
  } else {
    R->L = merge(L, R->L);
    update(R);
    return R;
  }
}

void split(Node *T, int pos, Node *&L, Node *&R) {
  if (!T) {
    L = R = NULL;
    return;
  }
  int cntL = CNT(T->L);
  if (pos <= cntL) {
    split(T->L, pos, L, T->L);
    update(T);
    R = T;
  } else {
    split(T->R, pos - cntL - 1, T->R, R);
    update(T);
    L = T;
  }
}

int getPos(Node* node) {
  assert(node);
  int res = CNT(node->L);
  while (node->par) {
    if (node->par->L == node) {
      node = node->par;
    } else {
      node = node->par;
      res += CNT(node->L) + 1;
    }
  }
  return res;
}

int findNeigh(Node *team, Node *q, int a) {
  (void)q;
  int ans = -1;
  while (team) {
    int posQ = getPos(team + 1); // hack
    if (posQ <= a) {
      ans = team->id;
      team = team->R;
    } else {
      team = team->L;
    }
  }
  return ans;
}

Node *insertNeigh(Node *T, Node *neigh, Node *n, bool flag) {
  int pos = getPos(neigh);
  Node *L, *R;
  split(T, pos + (flag ? 0 : 1), L, R);
  return merge(L, merge(n, R));
}

void insertQueue(Node *&q, Node *&team, int id, Node *nt, Node *nq, int a) {
  Node *neighQ = &nodes[2 * id + 1];
  int pos = getPos(neighQ);
  assert(pos <= a);
  bool flag = (pos == a);
  q = insertNeigh(q, &nodes[2 * id + 1], nq, flag);
  team = insertNeigh(team, &nodes[2 * id], nt, flag);
}

void _printTree(Node *T) {
  if (T) {
    _printTree(T->R);
    printf("%d ", T->id + 1);
    _printTree(T->L);
  }
}

void printTree(Node *T) {
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
  vector <Node*> teams(n, NULL);
  Node *q = NULL;
  for (int i = 0; i < n; ++i) {
    int c, a;
    scanf("%d%d", &c, &a);
    Node *nt = createNode(i);
    Node *nq = createNode(i);

    --c;
    int id = findNeigh(teams[c], q, a);
    //eprintf("c %d a %d id %d\n", c, a, id);
    if (id == -1) {
      teams[c] = merge(nt, teams[c]);
      q = merge(nq, q);
    } else {
      insertQueue(q, teams[c], id, nt, nq, a);
    }
#ifdef LOCAL2
    printTree(q);
#endif
  }

  printTree(q);

  return 0;
}
