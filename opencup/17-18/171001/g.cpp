// #define _GLIBCXX_DEBUG

#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define forab(i, l, r) for (int i = (l); i <= (r); i++)

typedef long long ll;
typedef long double dbl;

const dbl eps = 1e-6;

dbl readDouble() {
	double x;
	scanf("%lf", &x);
	return x;
}

struct pnt {
  dbl x, y, z;

  pnt( dbl _x, dbl _y, dbl _z ) : x(_x), y(_y), z(_z) { }
  pnt() { }

  pnt operator + ( pnt p ) const { return pnt(x + p.x, y + p.y, z + p.z); }
  pnt operator - ( pnt p ) const { return pnt(x - p.x, y - p.y, z - p.z); }
  pnt operator * ( dbl k ) const { return pnt(x * k, y * k, z * k); }
  pnt operator / ( dbl k ) const { return pnt(x / k, y / k, z / k); }
  pnt operator - () const { return pnt(-x, -y, -z); }

  pnt operator * ( pnt p ) const {
    return pnt(y * p.z - z * p.y,
               z * p.x - x * p.z,
               x * p.y - y * p.x); 
  }
  dbl operator ^ ( pnt p ) const { return x * p.x + y * p.y + z * p.z; }

  bool operator == ( pnt p ) const { return fabs(x - p.x) + fabs(y - p.y) + fabs(z - p.z) < eps; }
  bool operator != ( pnt p ) const { return fabs(x - p.x) + fabs(y - p.y) + fabs(z - p.z) > eps; }
  bool operator < ( pnt p ) const { 
    if (fabs(x - p.x) > eps) return x < p.x;
    if (fabs(y - p.y) > eps) return y < p.y;
    return z < p.z;
  }

  void read() { 
  	x = readDouble();
  	y = readDouble();
  	z = readDouble();
  }

  dbl d2() const { return x * x + y * y + z * z; }
  dbl d() const { return sqrt(d2()); }

  pnt norm() const { return *this / d(); }

  void out() {
  	printf("%.15f %.15f %.15f\n", (double)x, (double)y, (double)z);
  }
};

const int N = 51;

vector<int> cell[N][N][N];

pnt norm( pnt a, pnt b, pnt c ) {
	return (c - a) * (b - a);
}
dbl area( pnt a, pnt b, pnt c ) {
	dbl sqr = norm(a, b, c).d2();
	if (sqr > eps) sqr = sqrt(sqr);
	return sqr;
}
bool is_in( pnt a, pnt b, pnt c, pnt p ) {
	dbl x = area(p, b, c), y = area(a, p, c), z =  area(a, b, p);
	dbl tmp =  x + y + z;
	// if (fabs(x) < eps || fabs(y) < eps || fabs(z) < eps)
	// 	return 0;
	return fabs(area(a, b, c) - tmp) < eps;
}

int main() {
	int g;
	scanf("%d", &g);
	vector<vector<pnt>> p(g);
	vector<vector<vector<int>>> t(g);
	forn(i, g) {
		int n, m;
		scanf("%d%d", &n, &m);
		p[i].resize(n);
		forn(j, n)
		 	p[i][j].read();
		t[i].assign(m, vector<int>(3));
		forn(j, m)
			forn(k, 3)
				scanf("%d", &t[i][j][k]), t[i][j][k]--;
	}

	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	int num = n * m * k, d = max(max(n, m), k);
	struct Object {
		int i;
		pnt center;
	};
	vector<Object> os(num);
	forn(i, num) {
		Object &o = os[i];
		scanf("%d", &o.i), o.i--;
		o.center.read();
		cell
			[(int)round(o.center.x)]
			[(int)round(o.center.y)]
			[(int)round(o.center.z)]
		.push_back(i);
	}

	int q, cc = 0;
	scanf("%d", &q);
	vector<int> used(num);
	while (q--) {
		cc++;
		pnt o, v;
		o.read();	
		v.read();
		const dbl inf = 1e9;
		dbl opt_d = inf;
		auto process = [&]( Object &obj ) {
			for (auto &tr_ind : t[obj.i]) {
				pnt tr[3];
				forn(j, 3)
					tr[j] = p[obj.i][tr_ind[j]] + obj.center;

				pnt no = norm(tr[0], tr[1], tr[2]);
				dbl div = no ^ v;
				if (fabs(div) < eps)
					continue;
				dbl t = (no ^ (tr[0] - o)) / div;
				pnt candidate = o + v * t;
				// assert(fabs((candidate - tr[0]) ^ no) < eps);
				if (t >= -eps && is_in(tr[0], tr[1], tr[2], candidate))
					opt_d = min(opt_d, t);
			}
		};
		// for (auto &obj : os) 
		// 	process(obj);
		forn(i, d + 1) {
			if (i > opt_d + 2)
				break;
			pnt cur_p = o + v * i;
			int x = round(cur_p.x);
			int y = round(cur_p.y);
			int z = round(cur_p.z);
			forab(dx, -2, 2)
				forab(dy, -2, 2)
					forab(dz, -2, 2) {
						int x1 = x + dx;
						int y1 = y + dy;
						int z1 = z + dz;
						if (0 <= x1 && x1 <= n &&
							0 <= y1 && y1 <= m &&
							0 <= z1 && z1 <= k) {
							for (int ind_o : cell[x1][y1][z1])
								if (used[ind_o] != cc) {
									used[ind_o] = cc;
									process(os[ind_o]);
								}
						}
					}
		}
		if (opt_d == inf)
			puts("-1 -1 -1");
		else {
			// printf("opt_d = %g\n", (double)opt_d);
			(o + v * opt_d).out();
		}
	}
}
