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
#define sz(a) (int)(a.size())

#ifdef LOCAL
	#define LLD "%I64d"
#else 
	#define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef double ld;
typedef unsigned long long ull;
typedef unsigned int uint;

#define taskname "e"

const int inf = 1000000000;
const ld eps = 1e-5;

struct point{
	ld x,y;

	point(){
	}
	point(ld x,ld y):x(x),y(y){
	}
	

	void load(){
		cin >> x >> y;
	}
};

inline ld dist2(const point& a,const point& b){
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

inline ld dist(const point& a,const point& b){
	return sqrt(dist2(a,b));
}

bool operator==(const point& a,const point& b){
	return abs(a.x-b.x) < eps && abs(a.y - b.y) < eps;
}

struct line{
	ld a,b,c;
	line(){
	}
	line(point p1,point p2){
		a = p1.x - p2.x;
		b = p1.y - p2.y;
		c = (-(a*p1.x-b*p1.y)-(a*p2.x-b*p2.y))/2;
	}
};

ld det(ld a,ld b,ld c,ld d){
	return a*d - b*c;
}

point intersec(line a,line b){
	if (fabs(det(a.a,a.b,b.a,b.b)) < eps)
		return point(0,0);
	ld x = det(-a.c,a.b,-b.c,b.b)/det(a.a,a.b,b.a,b.b);
	ld y = det(a.a,-a.c,b.a,-b.c)/det(a.a,a.b,b.a,b.b);
//	assert(abs(x*a.a+y*a.b+a.c) < eps);
//	assert(abs(x*b.a+y*b.b+b.c) < eps);
	return point(x,y);
}

struct circle{
  ld x,y,r;
  int mask;

  bool in(point p){
  	return dist2(point(x,y),p) <= r*r+eps;
  }

  circle(){
  }


  circle(point p){
 	mask = 0;
  	x = p.x;
  	y = p.y;
  	r = 1e-9;
  }

  circle(point p1,point p2){
  	mask = 0;
  	x = (p1.x + p2.x)/2;
  	y = (p1.y + p2.y)/2;
  	r = dist(point(x,y),p1);
  }

  circle(point p1,point p2,point p3){
   	 mask = 0;
  	 line l1(p1,p2);
  	 line l2(p1,p3);
  	 point p = intersec(l1,l2);
  	 x = p.x;
  	 y = p.y;
  	 r = dist(p,p1);
  }
};

vector<circle> v;
int testcase;
point p[15];
int n,m,K;

int dp[(1<<15)+10];
int prev[(1<<15)+10];

bool check(ld val){
   for (int i = 0; i < (1<<n); i++)
   	  dp[i] = 1<<20;

   for (int i = 0; i < m; i++)
   	  if (v[i].r < val)
	   	   dp[v[i].mask] = 1,prev[v[i].mask] = -i-1;

   for (int i = 0; i < (1<<n); i++)
     	if (dp[v[i].mask]){
     		for (int j = i; j; j=((j-1)&i))
     			dp[j] = 1,prev[j] = prev[i];
     	}


   dp[0] = 0,prev[0] = 0;

   for (int i = 0; i < (1<<n); i++){
   	  for (int j = i; j; j = ((j-1)&i))
   	  	if (i != j && dp[i] > dp[j] + dp[i^j]){
   	  		dp[i] = dp[j] + dp[i^j];
   	  		prev[i] = j;
   	  	}
   }

   return (dp[(1<<n)-1] <= K);
}


int printed;

void gen(int mask){
	if (mask == 0)
		return;
	if (prev[mask] < 0){
		printf("  circle %d at (%.10lf, %.10lf)\n",printed+1,v[-(prev[mask]+1)].x,v[-(prev[mask]+1)].y);
		printed++;
		return;
	}
	gen(prev[mask]);
	gen(mask ^ prev[mask]);
}

void print(ld val){
	printed = 0;
	if (testcase != 1)
		printf("\n");
	printf("Case %d: The minimal possible radius is %.10lf\n",testcase,val);
	gen((1<<n)-1);
	while (printed < K){		
		printf("  circle %d at (%.10lf, %.10lf)\n",printed+1,0.0,0.0);
		printed++;
	}
//	assert(printed == K);
//	assert(dp[(1<<n)-1] <= K);
}




bool solve(){
	testcase++;
	scanf("%d %d",&n,&K);
	if (n == 0 && K == 0)
		return false;

	v.clear();
	for (int i = 0; i < n; i++){
		p[i].load();
		v.pb(circle(p[i]));
	}

	for (int i = 0; i < n; i++)
		for (int j = i+1; j < n; j++)
			if (!(p[i] == p[j]))
				v.pb(circle(p[i],p[j]));

	for (int i = 0; i < n; i++)
		for (int j = i+1; j < n; j++)
			if (!(p[i] == p[j]))
				for (int k = j+1; k < n; k++)
					if (!(p[i] == p[k]) && !(p[j] == p[k])){
						ld d1 = dist2(p[i],p[j]);
						ld d2 = dist2(p[i],p[k]);
						ld d3 = dist2(p[j],p[k]);
						if (2*max(max(d1,d2),d3) <= d1+d2+d3 + eps)
							v.pb(circle(p[i],p[j],p[k]));
					}

   m = v.size();


   for (int i = 0; i < n; i++)
   	  for (int j = 0; j < m; j++)
   	  	if (v[j].in(p[i]))
   	  		v[j].mask |= (1<<i);




   ld l = 0;
   ld r = 1e9;

   assert(check(r));

   for (int it = 0; it < 100; it++){
   	 ld mid = (l+r)/2;

   	 if (check(mid))
   	 	r = mid;
   	 else
   	 	l = mid;
   }

   check(r);
   print(r);		
   return true;
}

int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);

  while (solve());
  return 0;
}

