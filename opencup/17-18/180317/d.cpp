#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int N = 203;

int f[N][N][2];

int main() {
	ios_base::sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	vector<vector<bool>> c(n, vector<bool>(n));
	vector<int> p(n), size(n), edges(n);
	forn(i, n)
		p[i] = i, edges[i] = 0, size[i] = 1;
	function<int(int)> get = [&]( int a ) {
		return a == p[a] ? a : (p[a] = get(p[a]));
	};
	auto join = [&]( int a, int b ) {
		c[a][b] = c[b][a] = 1;
		a = get(a), b = get(b);
		if (a == b) {
			edges[a]--;
			return;
		}
		p[a] = b;
		edges[b] += edges[a] + size[a] * size[b] - 1;
		size[b] += size[a];
	};
	while (m--) {
		int a, b;
		cin >> a >> b, a--, b--;
		join(a, b);
	}
	memset(f, -1, sizeof(f));
	function<bool(int,int,int)> win = [&]( int a, int b, int e )  {
		if (a + b < 2) return 0;
		if (a + b == 2) return 1;
		int &res = f[a][b][e];
		if (res != -1) return res;
		res = 0;
		if (a >= 2) res |= !win(a - 1, b, e ^ 1);
		if (a >= 1 && b >= 1) res |= !win(a - 1, b, e ^ 1);
		if (b >= 2) res |= !win(a + 1, b - 2, e);
		if (e == 1) res |= !win(a, b, 0);
		return res;
	};
	int e, a, b;
	vector<int> v[3];
	auto cur_win = [&]() {
		e = 0, a = 0, b = 0;
		forn(t, 3)
			v[t].clear();
		forn(i, n)
			if (p[i] == i) {
				e += edges[i];
				((size[i] & 1) ? b : a) += 1;
				v[size[i] & 1].push_back(i);
				v[2].push_back(i);
			}
		e &= 1;
		return win(a, b, e);
	};
	auto read_move = [&]() {
		int a, b;
		if (!(cin >> a >> b))
			exit(0);
		a--, b--;
		if (a == -1 && b == -1)
			exit(0);
		join(a, b);
	};
	auto do_join = [&]( int a, int b ) {
		join(a, b);
		cout << a + 1 << " " << b + 1 << endl;
	};
	auto do_move = [&]() {
		assert(cur_win());
		assert(a + b >= 2);
		if (a + b == 2) {
			do_join(v[2][0], v[2][1]);
			exit(0);
		} else if (b >= 2 && !win(a + 1, b - 2, e)) {
			do_join(v[1][0], v[1][1]);
		} else if (a >= 2 && !win(a - 1, b, e ^ 1)) {
			do_join(v[0][0], v[0][1]);
		} else if (a && b && !win(a - 1, b, e ^ 1)) {
			do_join(v[0][0], v[1][0]);
		}
		else {
			assert(e > 0 && !win(a, b, 0));
			int good = 0;
			forn(i, n)
				forn(j, i)
					if (get(i) == get(j) && !c[i][j]) {
						do_join(i, j), i = j = n;
						good = 1;
					}
			assert(good);
		}
		cout.flush();
	};
	cur_win();
	if (a + b <= 1) {
		exit(0);
	}
	if (!cur_win()) {
		cout << 2 << endl;
		read_move();
	} else {
		cout << 1 << endl;
	}
	while (1) 
		do_move(), read_move();
}
