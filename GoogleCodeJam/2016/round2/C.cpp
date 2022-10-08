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
#include <stdarg.h>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if (_WIN32 || __WIN32__)
  #define LLD "%I64d"
#else
  #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "C"
#define TASKMOD "small"

typedef long long ll;
typedef long double ld;

vector<int> perm;
int r, c;

bool match(int x, int y) {
  if (x == -1 && y == -1) return true;
  if (x == -1 || y == -1) return false;
  return perm[x] == y;
}

int getDown(int y) {
  return c + r + c - y - 1;
}

int getRight(int x) {
  return c + x;
}

int getLeft(int x) {
  return c + r + c + r - x - 1;
}

struct state {
  vector<int> values;
  state *p;
  int x, y;
  char pc;

  state* alloc(char c) {
    state* ns = new state;
    ns->values = values;
    ns->p = this;
    ns->x = x;
    ns->y = y + 1;
    ns->pc = c;
    return ns;
  }

  void next_row() {
    rotate(values.begin(), values.begin()+1, values.end());
    x++;
    values[0] = getLeft(x);
    y = 0;

  }

  state* next_left() {
    if (y == c - 1 && !match(values.back(), getRight(x)))
      return NULL;
    if (x == r - 1 && !match(values[y], getDown(y)))
      return NULL;
    state *next = alloc('\\');
    if (x == r - 1 ) {
      next->values[y] = -1;
    }
    if (y != c - 1) {
      return next;
    } else {
      next->values[y + 1] = -1;
    }
    next->next_row();
    return next;
  }

  state* next_right() {
    if (!match(values[y], values[y + 1]))
      return NULL;
    state *next = alloc('/');
    next->values[y] = next->values[y + 1] = -1;
    if (x == r - 1) {
      next->values[y + 1] = getDown(y);
    }
    if (y == c - 1) {
      next->values[y] = getRight(x);
      next->next_row();
    }
    return next;
  }

  void dump() {
    eprintf("%d %d\n", x, y);
    for (int i : values) {
      eprintf("%d ", i);
    }
    eprintf("\n");
  }
};


void read() {
  scanf("%d%d", &r, &c);
  perm.resize(2 * (r + c));
  for (int i = 0; i < r+c; i++) {
    int a, b;
    scanf("%d%d",&a,&b);
    --a, --b;
    perm[a] = b;
    perm[b] = a;
  }
}

vector<vector<char>> ans;

void restore(state *q) {
  char prevc = 0;
  while (q != NULL) {
    if (q->y < c && q->x < r) {
      ans[q->x][q->y] = prevc;
    }
    prevc = q->pc;
    q = q->p;
  }
}

void solve() {
  bool inv = false;
  if (r < c) {
    swap(r, c);
    inv = true;
    for (int i = 0; i < (int)perm.size(); i++)
      perm[i] = (int)perm.size() - perm[i] - 1;
    reverse(perm.begin(), perm.end());
  }
  ans = vector<vector<char>>(r, vector<char>(c));
  state *init = new state;
  init->p = NULL;
  init->x = 0;
  init->y = 0;
  init->values.resize(c + 1);
  init->values[0] = 2 * (r + c) - 1;
  for (int i = 1; i <= c; i++) {
    init->values[i] = i - 1;
  }

  queue<state *> q;
  q.push(init);

  while (!q.empty()) {
    state *s = q.front();
    q.pop();
    if (s->x == r) {
      restore(s);
      if (inv) {
        for (int i = 0; i < c; i++) {
          for (int j = 0; j < r; j++) {
            printf("%c", ans[j][i]);
          }
          printf("\n");
        }
      } else {
        for (int i = 0; i < r; i++) {
          for (int j = 0; j < c; j++) {
            printf("%c", ans[i][j]);
          }
          printf("\n");
        }
      }
      return;
    }
    eprintf("============\n");
    s->dump();
    state* ns = s->next_left();
    if (ns) {
      q.push(ns);
      eprintf("Left\n");
      ns->dump();
    }
    ns = s->next_right();
    if (ns) {
      q.push(ns);
      eprintf("Right\n");
      ns->dump();
    }
  }
  printf("IMPOSSIBLE\n");
}

int main() {
  freopen(TASKNAME "-" TASKMOD ".in", "r", stdin);
  freopen(TASKNAME "-" TASKMOD ".out", "w", stdout);

  char buf[1000];
  int testNum;
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &testNum);

  for (int testId = 1; testId <= testNum; testId++) {
    if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
      TIMESTAMPf("Test %d", testId);
    printf("Case #%d:\n", testId);
    read();
    solve();
  }

  TIMESTAMP(end);
  return 0;
}