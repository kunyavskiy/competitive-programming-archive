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
#include <random>

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


mt19937 rnd;

enum type {
  ADD, DELETE
};

struct op {
  type t;
  int x;
};

int n;
vector<int> p;
vector<op> ops;
int cur_op;
vector<vector<int>> ls;
set<int> cur;

int readN() {
#ifdef LOCAL
  assert(cur.empty());
  n = rnd() % 1000 + 1;
  p.resize(n);
  iota(p.begin(), p.end(), 0);
  shuffle(p.begin(), p.end(), rnd);
  vector<int> a(n * 2);
  for (int i = 0; i < n * 2; i++) a[i] = i / 2;
  shuffle(a.begin(), a.end(), rnd);
  vector<int> was(n);
  ops.clear();
  for (int i = 0; i < n * 2; i++) {
    if (!was[a[i]]) {
      ops.push_back({ADD, a[i]});
      was[a[i]] = 1;
    } else {
      ops.push_back({DELETE, a[i]});
    }
  }
  cur_op = 0;
#else
  int n;
  cin >> n;
#endif
  ls.assign(n, vector<int>(n, -1));
  return n;
}

op get_op() {
#ifdef LOCAL
  auto res = ops[cur_op++];
//  db3(cur_op, res.t, res.x);
  if (res.t == ADD) {
    cur.insert(p[res.x]);
  } else {
    cur.erase(p[res.x]);
  }
  return res;
#else
  string s;
  int x;
  cin >> s;
  cin >> x;
  op res;
  res.t = s == "add" ? ADD : DELETE;
  res.x = x - 1;
  return res;
#endif
}


// ls[i][j] == 1 <=> p[i] < p[j]
int cmp(int i, int j) {
  assert(i == n || i != j);
  if (i == n) return 0;
  if (j == n) return 1;

  assert(ls[i][j] != -1);
  return ls[i][j];
}

void ask(vector<int> v) {
  assert(v.size() <= 30);
  assert(set<int>(v.begin(), v.end()).size() == v.size());
  for (int x : v) assert(0 <= x && x < n);

  vector<int> res(v.size());
#ifdef LOCAL
  res = v;
  sort(res.begin(), res.end(), [&](int i, int j) {
    return p[i] < p[j];
  });
#else
  cout << v.size();
  for (int x : v) cout << " " << x + 1;
  cout << endl;

  for (int i = 0; i < (int)res.size(); i++) {
    cin >> res[i];
    res[i]--;
  }
#endif
  for (int i = 0; i < (int)res.size(); i++) {
    for (int j = 0; j < (int)res.size(); j++) {
      ls[res[i]][res[j]] = i < j;
    }
  }
}

void answer(int x) {
#ifdef LOCAL
  if (x == n) assert(cur.empty());
  else assert(!cur.empty() && p[x] == *cur.begin());
#else
  if (x == n) x = -2;
  cout << x + 1 << endl;
#endif
}

void solve() {
  n = readN();

  struct node {
    int val{0};
    int rg{0};
    node* par{nullptr};
    vector<node*> ch;
  };

  int cnode = 0;
  vector<node> nodes(n + 1);
  node* root = &nodes[n];
  vector<node*> ptr(n);

//  vector<node*> roots;

  auto fix = [&](node *r) {
    vector<int> cur;
    for (auto v : r->ch) if (v->val != n) cur.push_back(v->val);
    ask(cur);

    vector<node*> nch;
    while (!r->ch.empty()) {
      if (r->ch.size() == 1 || r->ch.back()->rg != r->ch[(int)r->ch.size() - 2]->rg) {
        nch.push_back(r->ch.back());
        r->ch.pop_back();
        continue;
      }
      auto v1 = r->ch.back();
      r->ch.pop_back();
      auto v2 = r->ch.back();
      r->ch.pop_back();
      if (cmp(v2->val, v1->val)) swap(v1, v2);
      v1->rg++;
      v1->ch.push_back(v2);
      v2->par = v1;
      r->ch.push_back(v1);

      sort(r->ch.begin(), r->ch.end(), [&](node* x, node* y) {
        return x->rg > y->rg;
      });
    }
    reverse(nch.begin(), nch.end());
    r->ch = nch;

    vector<int> rgs;
    for (auto to : r->ch) rgs.push_back(to->rg);
//    dbv(rgs);
  };

  for (int ii = 0; ii < 2 * n; ii++) {
    auto op = get_op();

//    db2(op.t, op.x);
    switch (op.t) {
      case ADD: {
        ptr[op.x] = &nodes[cnode++];
        ptr[op.x]->val = op.x;
        ptr[op.x]->par = root;
        root->ch.push_back(ptr[op.x]);

//        db2("fix-add", root->ch.size());
        fix(root);
        break;
      }
      case DELETE: {
        auto v = ptr[op.x];
        assert(v->val == op.x);
        for (auto to : v->ch) {
          v->par->ch.push_back(to);
          to->par = v->par;
        }
        v->par->ch.erase(find(v->par->ch.begin(), v->par->ch.end(), v));
        sort(v->par->ch.begin(), v->par->ch.end(), [&](node* x, node* y) {
          return x->rg > y->rg;
        });
//        db2("fix-add", v->par->ch.size());
        fix(v->par);
        break;
      }
      default:
        assert(0);
    }
    int ans = n;
    for (int i = 0; i < (int)root->ch.size(); i++) {
      if (cmp(root->ch[i]->val, ans)) {
        ans = root->ch[i]->val;
      }
    }
    answer(ans);
  }
}

int main() {
#ifdef LOCAL
  for (int it = 14;; it++) {
    db(it);
    rnd = mt19937(it);
    solve();
  }
#endif

  solve();



  return 0;
}
