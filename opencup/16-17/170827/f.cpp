#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int N =1e5;

int n, m;
vector<int> c[N], w[N];

int x[N], d[N], p[N], size[N];
int T, t_in[N], t_out[N];
int cnt, no[N], pos[N], len[N], top[N];

struct SegmentTree {
  int n, *t;
  void build( int n ) {
    this->n = n, t = new int[2 * n]();
  }
  int getMax( int l, int r ) {
    int res = 0;
    for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
      if ((l & 1) == 1) res = max(res, t[l++]);
      if ((r & 1) == 0) res = max(res, t[r--]);
    }
    return res;
  }
  void change( int i, int x ) {
    t[i += n] = x;
    for (i >>= 1; i > 0; i >>= 1)
      t[i] = max(t[2 * i], t[2 * i + 1]);
  }
} s[N];

ll w_up[N];
ll w_sum[N];

void dfs( int v, int pr, int wpr = 0, int dep = 0 ) {
  t_in[v] = T++;

  p[v] = pr, w_up[v] = wpr, d[v] = dep, size[v] = 1;
  if (pr == -1)
  	w_sum[v] = 0;
  else
  	w_sum[v] = wpr + w_sum[pr];
  forn(i, c[v].size()) {
  	int x = c[v][i];
    if (x != pr)
      dfs(x, v, w[v][i], dep + 1), size[v] += size[x];
  }
  t_out[v] = T++;
}

int isAncestor( int a, int b ) {
  return t_in[a] <= t_in[b] && t_out[b] <= t_out[a];
}

void calc( int v ) {
  if (v == p[v] || 2 * size[v] < size[p[v]])
    no[v] = cnt++, top[no[v]] = v;
  else
    no[v] = no[p[v]];
  pos[v] = len[no[v]]++;
  for (int x : c[v])
    if (x != p[v])
      calc(x);
}

int getMax( int a, int b ) {
  int res = INT_MIN, v;
  forn(t, 2) {
    while (!isAncestor(v = top[no[a]], b))
      res = max(res, s[no[a]].getMax(0, pos[a])), a = p[v];
    swap(a, b);
  }
  return max(res, s[no[a]].getMax(min(pos[a], pos[b]), max(pos[a], pos[b])));
}

int LCA( int a, int b ) {
  int res = INT_MIN, v;
  forn(t, 2) {
    while (!isAncestor(v = top[no[a]], b))
      a = p[v];
    swap(a, b);
  }
  return d[a] > d[b] ? b : a;
}

struct Ant {
	int a, b;
	ll start_time;
	int id;
	bool operator < ( Ant a ) const { return id < a.id; }
};
vector<Ant> qp[N];
vector<Ant> qe[N];

ll weight_sum( int a, int b ) {
	if (d[a] > d[b]) swap(a, b);
	return w_sum[b] - w_sum[a];
}
void Split( Ant ant ) {
	int a, v;
	ll t;
	if (d[ant.a] > d[ant.b]) {
		a = ant.a;
		t = ant.start_time;
		while (!isAncestor(v = top[no[a]], ant.b)) {
			qp[no[a]].push_back({a, v, t, ant.id});
			t += weight_sum(a, v);
			qe[v].push_back({v, p[v], t, ant.id});
			a = p[v];
			t += w_up[v];
		}
		qp[no[a]].push_back({a, ant.b, t, ant.id});

	  // return max(res, s[no[a]].getMax(min(pos[a], pos[b]), max(pos[a], pos[b])));
	} else {
		a = ant.b;
		t = ant.start_time + weight_sum(ant.a, ant.b);
		while (!isAncestor(v = top[no[a]], ant.a)) {
			t -= weight_sum(a, v);
			qp[no[a]].push_back({v, a, t, ant.id});
			t -= w_up[v];
			qe[v].push_back({p[v], v, t, ant.id});
			a = p[v];
		}
		qp[no[a]].push_back({ant.a, a, t, ant.id});

	}
}

void build() {
  dfs(0, 0); 
  calc(0);
  forn(i, n)
    s[i].build(len[i]);
}

int ans[N];

struct Seg {
	ll x1, x2, y1, y2;
	int id;
};

void solve ( vector<Ant> &v ) {
	sort(v.begin(), v.end());
	int k = 0;
	forn(i, v.size()) {
		if (i + 1 < (int)v.size() && v[i].id == v[i + 1].id) {
			if (v[i].a == v[i].b)
				swap(v[i], v[i + 1]);
			v[k++] = v[i++];
		} else {
			v[k++] = v[i];
		}
	}
	vector<Seg> s;
	forn(i, k) {
		Ant a = v[i];
		s.push_back({
			a.start_time, a.start_time + weight_sum(a.a, a.b),
			w_sum[a.a], w_sum[a.b],
			a.id
		});
	}
	auto rot = [&]( ll &x, ll &y ) {
		ll z = x + y, t = x - y;
		x = z, y = t;
	};
	for (Seg &a : s) {
		rot(a.x1, a.y1);
		rot(a.x2, a.y2);
	}
	forn(_, 2) {
		// TODO
		for (Seg &a : s) {
			swap(a.x1, a.y1);
			swap(a.x2, a.y2);
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	forn(i, n - 1) {
		int a, b, x;
		scanf("%d%d%d", &a, &b, &x), a--, b--;
		c[a].push_back(b), w[a].push_back(x);
		c[b].push_back(a), w[b].push_back(x);
	}
	build();

	vector<Ant> v;
	forn(i, m) {
		int a, b;
		ll start_time;
		scanf("%d%d%lld", &a, &b, &start_time), a--, b--;
		if (!isAncestor(a, b) && !isAncestor(b, a)) {
			int c = LCA(a, b);
			v.push_back({a, c, start_time, i});
			v.push_back({c, b, start_time + (d[a] - d[c]), i});

		} else {
			v.push_back({a, b, start_time, i});
		}
	}
	for (Ant ant : v)
		Split(ant);
	forn(i, n) {
		solve(qe[i]);
		solve(qp[i]);
	}
	forn(i, n) printf("%d\n", ans[i]);
}
