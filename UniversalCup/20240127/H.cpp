#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

const int MAXL = 1'100'000; // maximal length, without trailing \0

struct node {
  map<int, node*> next;
  node *link = nullptr;
  int len = 0;
  int count = 0;
  int max = std::numeric_limits<int>::min(), min = std::numeric_limits<int>::max();
  bool used = false;
  void update(int v) {
    min = std::min(v, min);
    max = std::max(v, max);
  }
};
node mem[2 * MAXL];
int memptr; node *root, *last;

bool isEqual(map<int, node*> &x, int key, node* val) {
  auto it = x.find(key);
  if (it == x.end()) return val == nullptr;
  return it->second == val;
}

void add(int c){
  node* nlast = &mem[memptr++];
  *nlast = node();
  nlast->len = last->len + 1;
  node* p = last;
  for (;p && isEqual(p->next, c, nullptr); p = p->link)
    p->next[c] = nlast;
  if (!p){
    nlast->link = root;
  } else {
    node* q = p->next[c];
    if (q->len == p->len + 1){
      nlast->link = q;
    } else {
      node* clone = &mem[memptr++];
      *clone = node();
      clone->next = q->next;
      clone->link = q->link;
      clone->len = p->len + 1;
      q->link = nlast->link = clone;
      for (;p && isEqual(p->next, c, q); p = p->link)
        p->next[c] = clone;
    }
  }
  last = nlast;
}

int main() {
  #ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
  #endif

  static char s[MAXL];
  int n;
  while (scanf("%d", &n) == 1) {
    memptr = 0;
    last = root = &mem[memptr++];
    *root = node();

    for (int i = 0; i < n; i++) {
      scanf("%s", s);
      for (int j = 0; s[j]; j++) {
        add(s[j] - 'a');
      }
      add(26 + i);
    }

    ll ans = 0;


    vector<node*> ts;

    auto dfs = [&](auto dfs, node *ptr) {
      if (ptr->used)
        return;
      ptr->used = true;
      for (auto [key, next] : ptr->next) {
        if (key < 26) {
          eprintf("#%ld #%ld by %d\n", ptr - mem, next - mem, key);
          dfs(dfs, next);
          ptr->update(next->min);
          ptr->update(next->max);
        } else {
          ptr->update(key);
        }
      }
      ts.push_back(ptr);
    };

    dfs(dfs, root);

    reverse(ts.begin(), ts.end());
    root->count = 1;
    for (node* ptr: ts) {
      for (auto [key, next]: ptr->next) {
        next->count += ptr->count;
      }
    }


    for (node* ptr : ts) {
      eprintf("ptr = #%ld, min = %d, max = %d, lens = %d..%d, l = %d\n", ptr - mem, ptr->min, ptr->max,  ptr->len, (ptr->link ? ptr->link->len : 0), ptr->len - (ptr->link ? ptr->link->len : 0));
      if (ptr->min == ptr->max && ptr != root) {
        ans += ptr->count;
      }
    }

    printf("%lld\n", ans);
  }

  return 0;
}
