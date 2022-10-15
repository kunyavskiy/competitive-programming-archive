#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#define forn(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;
#define pb push_back
typedef long long i64;

vector<int> factor(i64 x)
{
	vector<int> a;
	for (int i = 1; i <= 100000; i++)
		if (x%(i64)i == 0)
			a.pb(i);
	return a;
}

class RectangularSum
{
public:
i64 minimalArea(int n, int m, i64 ans)
{
	vector<int> a = factor(ans*2ll);
	a.pb(100000000);
	i64 res = (i64)1e18;
	for (int i = 0; a[i] <= n; i++) for (int j = 0; a[j] <= m; j++)
	{
		int l = a[i], k = a[j];
		if ((ans*2ll) % ((i64)k*l) != 0)
			continue;
		i64 t = ans*2ll/((i64)l*k);
		t -= (l-1);
		//cout << "t = " << t << endl;
		t -= (i64)m*(k-1);
		if (t%2 != 0)
			continue;
		t /= 2;
		// a = t
		i64 ii = t/m, jj = t%m;
		//cout << "a = " << t << ", " << ii << " " << jj << " " << endl;
		if (ii+k-1 < m && jj+l-1 < n)
		{
			//cout << k << " " << l << " " << t << endl;
			res = min(res, (i64)k*l);
		}
	}
	return res > 1e15 ? -1 : res;
}
};
