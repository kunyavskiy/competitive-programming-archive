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

#define taskname "c"

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
//};


//Structure s;


int x[210000];
int y[210000];
int val[210000];


int rt[110000];
int ra[110000];
int rb[110000];
int rc[110000];
int rd[110000];


map<pair<int,int>,int> v;

int n,n1;

int add(int x,int y,int val){
	if (v.find(mp(x,y)) == v.end()){
		::x[n1] = x;
		::y[n1] = y;
		::val[n1] = 0;
		v[mp(x,y)] = n1++;
	}
    ::val[v[mp(x,y)]] += val;
	return v[mp(x,y)];
}




int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);

  scanf("%d",&n);
  n1 = 0;

  for (int i = 0; i < n; i++){
  	int x,y;
  	scanf("%d",&x);
  	scanf("%d",&y);
  	add(x,y,1);
  }

  int m;
  scanf("%d",&m);

  for (int i = 0; i < m; i++){
  	if (scanf(" ? %d %d %d %d",&ra[i],&rb[i],&rc[i],&rd[i]) == 4)
  		rt[i] = 0;
  	else {
  		int x,y;
  		scanf(" + %d %d",&x,&y);	
  		rt[i] = 1;
  		ra[i] = add(x,y,0);
  	}
  }


  Build(n1,x,y,val);

  for (int i = 0; i < m; i++){
  	if (rt[i] == 0)
  		printf("%d\n",Get(ra[i],rb[i],rc[i],rd[i]));  	
  	else {
  		val[ra[i]]++;
  		Change(ra[i],val[ra[i]]);
  	}
  }


  return 0;
}

