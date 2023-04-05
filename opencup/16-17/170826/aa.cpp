#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int N = 1 << 18;

struct SegmentTreeMin {
  int n, mi[2 * N], add[2 * N];

  void build( int _n, int *a ) { build(n = _n, a, 1); } // O(n)
  void build( int n, int *a, int v ) {
    add[v] = 0;
    if (n == 1)
      mi[v] = a[0];
    else {
      int m = (n + 1) / 2;
      build(m, a, 2 * v);
      build(n - m, a + m, 2 * v + 1);
      mi[v] = min(mi[2 * v], mi[2 * v + 1]);
    }
  }
  int pos() {
  	int v = 1, vl = 0, vr = n - 1;
  	while (vl != vr) {
  		int vm = (vl + vr) / 2;
  		if (mi[2 * v] + add[v] == mi[v])
  			v = 2 * v, vr = vm;
  		else
  			v = 2 * v + 1, vl = vm + 1;
  	}
  	return vl;
  }
  int get_min( int l, int r ) { return get_min(l, r, 1, 0, n - 1); } 
  int get_min( int l, int r, int v, int vl, int vr ) { // O(logn)
    if (vr < l || r < vl)
      return INT_MAX;
    if (l <= vl && vr <= r)
      return mi[v];
    int vm = (vl + vr) / 2;
    int a = get_min(l, r, 2 * v, vl, vm);
    int b = get_min(l, r, 2 * v + 1, vm + 1, vr);
    return add[v] + min(a, b);
  }
  void set_x( int i, int x ) { 
  	add_x(i, i, x - get_min(i, i));
  }
  void add_x( int l, int r, int x ) { add_x(l, r, x, 1, 0, n - 1); }
  void add_x( int l, int r, int x, int v, int vl, int vr ) { // O(logn)
    if (vr < l || r < vl)
      return;
    if (l <= vl && vr <= r) {
      add[v] += x, mi[v] += x;
      return;
    }
    int vm = (vl + vr) / 2;
    add_x(l, r, x, 2 * v, vl, vm);
    add_x(l, r, x, 2 * v + 1, vm + 1, vr);
    mi[v] = min(mi[2 * v], mi[2 * v + 1]) + add[v];
  }
};

int main() {
	int n;
	scanf("%d", &n);
	struct Pair {
		int l, r, i;
	} p[n];
	forn(i, n) {
		scanf("%d%d", &p[i].l, &p[i].r);
		p[i].l--, p[i].r--;
		p[i].i = i;
	}
	auto less_l = [&]( Pair a, Pair b) { return a.l < b.l; };
	auto less_r = [&]( Pair a, Pair b) { return a.r < b.r; };

	int id[n], value[n];
	sort(p, p + n, less_r);
	forn(i, n)
		id[p[i].i] = i;
	forn(i, n)
		value[i] = p[i].r - i;

	SegmentTreeMin t1, t2;
	t1.build(n, value);
	forn(i, n)
		value[i] = 1e9;
	t2.build(n, value);

	sort(p, p + n, less_l);
	int i = 0;
	vector<int> ans;
	forn(l, n) {
		for (; i < n && p[i].l == l; i++) {
			t2.set_x(id[p[i].i], p[i].i);
		}
		if (t1.mi[1] < 0) {
			puts("-1");
			return 0;
		}
		int pos = t1.pos();
		if 	(t1.mi[1] > 0)
			pos = n - 1;
		int min_value = t2.get_min(0, pos);
		if (min_value > n) {
			puts("-1");
			return 0;
		}
		ans.push_back(min_value);
		t1.add_x(0, id[min_value], -1);
		t1.set_x(id[min_value], 1e9);
		t2.set_x(id[min_value], 1e9);
	}
	for (int x : ans)
		printf("%d ", x + 1);
	puts("");
}
