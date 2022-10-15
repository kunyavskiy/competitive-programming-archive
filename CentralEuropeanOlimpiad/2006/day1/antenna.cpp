#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define setval(a,v) memset(a,v,sizeof(a))

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#undef assert
#define assert(...) ;


using namespace std;

typedef long long int64;
typedef double ld;

struct point{
	ld x,y;
	point(){		
	}
	point(ld x,ld y):x(x),y(y){			
	}
};

inline point operator+(const point& a,const point& b){
	return point(a.x+b.x,a.y+b.y);
}

inline point operator/(const point& a,ld b){
	return point(a.x/b,a.y/b);
}

inline ld det(ld a,ld b,ld c,ld d){
	return a*d - b*c;
}

inline ld dest(const point& a,const point& b){
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

struct line{
	ld a,b,c;
	line(){
	}
	line(const point& p1,const point& p2){
		a = p1.y - p2.y;
		b = p2.x - p1.x;
		c = -a*p1.x - b*p1.y;		
		norm();
	}
	inline void norm(){
		ld nc = sqrt(a*a+b*b);
		a/=nc;
		b/=nc;
		c/=nc;
	}
	inline void inverse(){
		swap(a,b);
		a = -a;
	}
	inline void moveto(const point& p){
		c = -a*p.x - b*p.y;
	}
	inline bool intersec(const line& r,point& res){
		ld zn = det(a,b,r.a,r.b);
		if (abs(zn) < 1e-8){
			res.x = res.y = 0;
			return false;
		}
		res.x = det(-c,b,-r.c,r.b)/zn;
		res.y = det(a,-c,r.a,-r.c)/zn;
		return true;
	}
	inline bool on(const point& p){
		return abs(a*p.x+b*p.y+c) < 1e-7;
	}
};

inline line serper(const point& a,const point& b){
	line l(a,b);
	l.inverse();
	l.moveto((a+b)/2);
	return l;
}

struct circle{
	point c; ld r;
	
	circle():c(0,0),r(1e100){
	}
	
	circle(const point& p1,const point& p2,const point& p3){
		line l1 = serper(p1,p2);
		line l2 = serper(p1,p3);
		if (l1.intersec(l2,c)){
			r = dest(c,p1);			
			assert(on(p1));
			assert(on(p2));
			assert(on(p3));
		}
		else
			r = -1;
			
	}
	
	circle(const point& c,ld r):c(c),r(r){
	}
	
	inline bool operator<(const circle& a)const{
		return r < a.r;
	}
	inline bool in(const point& a){
		return dest(a,c) < r+(1e-7);
	}
	inline bool on(const point& p){
		return abs(dest(p,c) - r) < (1e-7);
	}
};


point pts[510];
int n,k;
circle best;


void solve(const point& p1,const point& p2,const point& p3){
	circle nc(p1,p2,p3);
	if (abs(p2.x - p3.x) < 1e-7 && abs(p2.x - p3.x) < 1e-7){
		nc.c = (p1+p2)/2;
		nc.r = dest(p1,p2)/2;
	}
	if (nc.r < 0)
		return;
	if (nc.r > best.r - 1e-7)
		return;
	int cnt = 0;
	for (int i=0;i<n && cnt < k;i++)
		if (nc.in(pts[i]))
			cnt++;
	cerr.precision(4);
//	cerr << fixed << nc.c.x <<" "<<nc.c.y <<" "<<nc.r <<" "<<cnt << endl;
	if (cnt < k)
		return;
	best = min(best,nc);		
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	scanf("%d %d",&n,&k);
	for (int i=0;i<n;i++)
		cin>>pts[i].x>>pts[i].y;

	for (int i=0;i<n;i++)
		for (int j=i+1;j<n;j++)
			for (int k=j;k<n;k++)
				solve(pts[i],pts[j],pts[k]);
	cout.precision(15);
	cout << best.r <<"\n" << fixed << best.c.x <<" "<<best.c.y << endl;		
	return 0;
}