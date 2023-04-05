#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef unsigned long long ull;

const int P = 1e9 + 7;
ull Pow( ull x, int n ) {
	ull r = 1;
	for (; n; n >>= 1) {
		if (n & 1)
			r *= x;
		x *= x;
	}
	return r;
}

class Treap {
  struct tree;
  typedef tree* ptree;

  struct tree {
    static ptree Null;

    ptree l, r;
    int x, y;
    ull data, sum;

    tree() { l = r = this, sum = 0; }
    tree( int tx, int tdata ) { l = r = Null, x = tx, data = tdata, calc(), y = rand(); }
    tree( int tx, int tdata, ptree tl, ptree tr ) { l = tl, r = tr, x = tx, data = tdata, calc(), y = rand(); }

    void calc() { sum = data ^ l->sum ^ r->sum; }
  };

  void Split( ptree t, ptree &l, ptree &r, int x ) {
    if (t == tree::Null)
      l = r = tree::Null;
    else if (t->x < x)
      Split(t->r, t->r, r, x), (l = t)->calc();
    else
      Split(t->l, l, t->l, x), (r = t)->calc();
  }

  void Merge( ptree &t, ptree l, ptree r ) {
    if (l == tree::Null)
      t = r;
    else if (r == tree::Null) 
      t = l;
    else if (l->y < r->y)
      Merge(l->r, l->r, r), (t = l)->calc();
    else
      Merge(r->l, l, r->l), (t = r)->calc();
  }

  ull Sum( ptree t, int vl, int vr, int l, int r ) {
    if (t == tree::Null || vl > r || l > vr)
      return 0;
    if (l <= vl && vr <= r)
      return t->sum;
    return Sum(t->l, vl, t->x - 1, l, r) ^ Sum(t->r, t->x + 1, vr, l, r) ^ (l <= t->x && t->x <= r ? t->data : 0);
  }

  void Out( ptree t, int dep ) {
    if (t == tree::Null)
      return;
    Out(t->l, dep + 1);
    printf("%*sx = %d, y = %d, data = %llu, xor = %llu\n", 2 * dep, "", t->x, t->y, t->data, t->sum);
    Out(t->r, dep + 1);
  }

  ptree root;

public:
  static const int inf = 2e9 + 1;

  Treap() { root = tree::Null; }

  void Add( int x, int data ) {
    ptree a, b;
    Split(root, a, b, x);
    Merge(a, a, new tree(x, data));
    Merge(root, a, b);
  }

  void Del( int x ) {
    ptree a, b, c;
    Split(root, a, b, x);
    Split(b, b, c, x + 1);
    Merge(root, a, c);
  }

  ull Sum( int l, int r ) {
    return Sum(root, -inf, inf, l, r);
  }

  void Out() {
    Out(root, 0);
  }
};

Treap::ptree Treap::tree::Null = new tree();

const int N = 1 << 17;

int n, a[N];
Treap t[2 * N];

void add( int value, int pos ) {
	ull A = Pow(P, value);
	// printf("add: value=%d, pos=%d, A=%llu\n", value, pos, A);
	for (int v = value + N; v >= 1; v /= 2)
		t[v].Add(pos, A);
}
void del( int value, int pos ) {
	// printf("del: value=%d, pos=%d\n", value, pos);
	for (int v = value + N; v >= 1; v /= 2)
		t[v].Del(pos);
}

int main() {
	int n;
	scanf("%d", &n);
	forn(i, n) {
		scanf("%d", &a[i]);
		add(a[i], i);
	}

	int q;
	while (scanf("%d", &q) == 1 && q) {
		while (q--) {
			int type;
			scanf("%d", &type);
			if (type == 1) {
				int i, A;
				scanf("%d%d", &i, &A), i--;
				del(a[i], i);
				add(a[i] = A, i);
			} else {
				int l, r;
				scanf("%d%d", &l, &r), l--, r--;
				if (t[1].Sum(l, r) == 0) {
					puts("-1");
					continue;
				}
				int v = 1;
				while (v < N)
					v = t[2 * v].Sum(l, r) ? 2 * v : 2 * v + 1;
				printf("%d\n", v - N);
			}
			// for (int i = 1; i < 2 * N; i++)
			// 	printf("tree[%d] = \n", i), t[i].Out();
		}
		fflush(stdout);
	}
}
