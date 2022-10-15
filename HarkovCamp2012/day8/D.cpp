#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <iterator>

#define mp make_pair
#define pb push_back
#define sqr(a) ((a) * (a))
#define zero(a) memset (a, 0, sizeof(a))
#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define sz(a) (int)(a).size()
#define all(a) (a).begin(), (a).end()
#define BS_L(a, x, less) (lower_bound(all(a), x, less) - (a).begin())
#define BS_U(a, x, less) (upper_bound(all(a), x, less) - (a).begin())

#ifdef LOCAL
	#define LLD "%I64d"
#else 
	#define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int uint;

#define taskname "d"

const int inf = 1000000000;
const ld eps = 1e-9;
                    
                                                                     

typedef vector <int> vi;
typedef vector <vi> vvi;


//struct Structure{
     struct Point
     {
      int x, y, value;
      Point() { }
      Point( int _x, int _y, int _value ) : x(_x), y(_y), value(_value) { }
     };

     int N;
     vector <Point> P;
     vi Order;
     vvi T, Sum;

     inline bool xylessi( int a, int b ) { return mp(P[a].x, a) < mp(P[b].x, b); }
     inline bool yxlessi( int a, int b ) { return mp(P[a].y, a) < mp(P[b].y, b); }
     inline bool xyless( int a, int b ) { return P[a].x < P[b].x; }
     inline bool yxless( int a, int b ) { return P[a].y < P[b].y; }

     void Build( int n, int *x, int *y, int *value ) // NlogN
     {
      N = n;
      if (!N)
        return;
      P.resize(n + 2); // two extra points - for Get() function
      Order.resize(n);
      forn(i, n)
        P[i] = Point(x[i], y[i], value[i]), Order[i] = i;
      sort(all(Order), xylessi);

      T.resize(2 * N);
      Sum.resize(2 * N);
      forn(i, N)
        T[N + i] = vi(1, Order[i]);
      for (int i = N - 1; i >= 1; i--)
      {
        T[i].resize(sz(T[2 * i]) + sz(T[2 * i + 1]));
        merge(all(T[2 * i]), all(T[2 * i + 1]), T[i].begin(), yxlessi);
      }
      for (int i = 1; i < 2 * N; i++)
      {
        int m = sz(T[i]);
        vi &s = Sum[i] = vi(m * 2, 0);
        forn(j, m)
          s[j + m] = P[T[i][j]].value;
        for (int j = m - 1; j >= 1; j--)
          s[j] = s[2 * j] + s[2 * j + 1];
      }
     }

     void Change( int i, int newValue ) // log^2 N
     {  
      assert(0 <= i && i < N);
      int z = BS_L(Order, i, xylessi);
      for (z += N; z > 0; z /= 2)
      {
        int j = BS_L(T[z], i, yxlessi);
        vi &s = Sum[z];
        s[j += sz(T[z])] = newValue;
        for (j /= 2; j > 0; j /= 2)
          s[j] = s[2 * j] + s[2 * j + 1];
      }
     }

     int InnerGet( int i )
     {
      int l = BS_L(T[i], N, yxless);
      int r = BS_U(T[i], N + 1, yxless) - 1;
      int sum = 0;
      vi &s = Sum[i];
      for (l += sz(T[i]), r += sz(T[i]); l <= r; l /= 2, r /= 2)
      {                                                                    
        if (l % 2 == 1) sum += s[l++];
        if (r % 2 == 0) sum += s[r--];
      }
      return sum;
     }

     int Get( int x1, int y1, int x2, int y2 ) // log^2 N, sum on [x1..x2] x [y1..y2]
     {
      if (!N || x1 > x2 || y1 > y2)
        return 0;

      P[N] = Point(x1, y1, 0);
      P[N + 1] = Point(x2, y2, 0);

      int zl = BS_L(Order, N, xyless);
      int zr = BS_U(Order, N + 1, xyless) - 1;
      int sum = 0;
      for (zl += N, zr += N; zl <= zr; zl /= 2, zr /= 2)
      {
        if (zl % 2 == 1) sum += InnerGet(zl++);
        if (zr % 2 == 0) sum += InnerGet(zr--);
      }
      return sum;
     }

int x[210000];
int y[210000];
int val[210000];

const int ITER = 600;


int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);

  int n;
  scanf("%d",&n);

  for (int i = 0; i < n; i++){
  	scanf("%d %d",&x[i],&y[i]);
  	val[i] = 1;
  }


  int m;
  scanf("%d",&m);
  int n1 = n;

  int res = 0;

  for (int i = 0; i < m; i++){
  	if (i % ITER == 0){
  		cerr << i << " "<<n<<" "<<n1<<endl;
  		n = n1;
  		Build(n,x,y,val);
  	}
  	int a,b,c,d;
  	if (scanf(" ? %d %d %d %d",&a,&b,&c,&d) == 4){
  		int ans = Get(a,b,c,d);
  		for (int j = n; j < n1; j++)
			if (a <= x[j] && x[j] <= c && b <= y[j] && y[j] <= d)
				ans++;
		res = ans;
  		printf("%d\n",ans);
  	}
  	else {
  		scanf(" + %d %d",&x[n1],&y[n1]);
  		x[n1] += res%100;
  		y[n1] += res%101;
  		val[n1] = 1;
  		n1++;  		
  	}
  }

  return 0;
}

	
