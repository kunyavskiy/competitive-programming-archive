#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

#define sz(a) (int)(a).size()

typedef long long ll;
typedef unsigned long long ull;

const int P = max(239, rand());
struct num {
  static const int MA = 1e9 + 7, MB = 1e9 + 9;

  int a, b;

  num() { }
  num( int x ) : a(x), b(x) { }
  num( int a, int b ) : a(a), b(b) { }

  num operator + ( const num &x ) const { return num((a + x.a) % MA, (b + x.b) % MB); }
  num operator - ( const num &x ) const { return num((a + MA - x.a) % MA, (b + MB - x.b) % MB); }
  num operator * ( int x ) const { return num(((ll)a * x) % MA, ((ll)b * x) % MB); }
  num operator * ( const num &x ) const { return num(((ll)a * x.a) % MA, ((ll)b * x.b) % MB); }
  bool operator == ( const num &x ) const { return a == x.a && b == x.b; }

  explicit operator ll () const { return (ll)a * MB + b + 1; } // > 0
};

const int LEN = 1e6;

num deg[LEN + 1];

struct node {
  int left, right;
  num hash;
};

int a[LEN];
vector<node> tree;

void recalc(node& n, int rlen) {
  n.hash = tree[n.left].hash * deg[rlen] + tree[n.right].hash;
}

int build(int l, int r) {
  node n;
  if (r == l + 1) {
    n.left = n.right = -1;
    n.hash = num(a[l]);
  } else {
    int m = (l + r) / 2;
    n.left = build(l, m);
    n.right = build(m, r);
    recalc(n, r - m);
  }
  tree.push_back(n);
  return (int)tree.size() - 1;
}

int setval(int nn, int p, int x, int l, int r) {
  node n;
  if (r == l + 1) {
    n.left = n.right = -1;
    n.hash = num(x);
  } else {
    int m = (l + r) / 2;
    if (p < m) {
      n.left = setval(tree[nn].left, p, x, l, m);
      n.right = tree[nn].right;
      recalc(n, r - m);
    } else {
      n.right = setval(tree[nn].right, p, x, m, r);
      n.left = tree[nn].left;
      recalc(n, r - m);
    }
  }
  tree.push_back(n);
  return (int)tree.size() - 1;
}

int n;

bool cmp2(const node &a, const node &b, int l, int r) {
  if (r == l + 1) {
    return a.hash.a < b.hash.a;
  } else {
    int m = (l + r) / 2;
    if (tree[a.left].hash == tree[b.left].hash) {
      return cmp2(tree[a.right], tree[b.right], m, r);
    } else {
      return cmp2(tree[a.left], tree[b.left], l, m);
    }
  }
}

bool cmp(pair<int, int> a, pair<int, int> b) {
  return cmp2(tree[a.second], tree[b.second], 0, n);
}

int main() {
  //freopen("input.txt", "r", stdin);
  deg[0] = 1;
  forn(i, LEN)
    deg[i + 1] = deg[i] * num(P);

  int m;
  scanf("%d%d", &n, &m);

  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  vector<pair<int, int>> r(m);
  r[0] = {0, build(0, n)};
  for (int i = 0; i < m - 1; i++) {
    int p, x;
    scanf("%d%d", &p, &x);
    r[i + 1] = {i + 1, setval(r[i].second, p - 1, x, 0, n)};
  }
  stable_sort(r.begin(), r.end(), cmp);
  for (auto p : r) {
    cout << p.first + 1 << " ";
  }
  cout << "\n";
}
