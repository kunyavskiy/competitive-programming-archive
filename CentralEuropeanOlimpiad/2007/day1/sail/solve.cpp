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
#include <cmath>
#define mp make_pair
#define pb push_back                     
#define setval(a,v) memset(a,v,sizeof(a))

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;



typedef long long int64;
typedef double ld;

#ifndef M_PI
	const ld M_PI = acos(-1.0);
#endif

/*int64 abs(int64 x){
	return (x<0)?(-x):x;
}*/

struct point{
	int x,y;
	point(){
		x=y=0;
	}
	point(int x,int y):x(x),y(y){
	}
};

int X,Y;

inline bool operator<(const point& a,const point& b){
	if (a.y != b.y)
		return a.y < b.y;
	return a.x < b.x;
}

inline bool operator==(const point& a,const point& b){
	return a.x == b.x && a.y == b.y;
}

inline bool operator!=(const point& a,const point& b){
	return a.x != b.x || a.y != b.y;
}

inline point operator-(const point& a,const point& b){
	return point(a.x-b.x,a.y-b.y);
}

inline point operator+(const point& a,const point& b){
	return point(a.x+b.x,a.y+b.y);
}

inline int64 operator*(const point& a,const point& b){
	return a.x*1LL*b.y - a.y*1LL*b.x;
}

inline int64 operator^(const point& a,const point& b){
	return a.x*1LL*b.x + a.y*1LL*b.y;
}

inline point operator/(const point& a,int b){
	return point(a.x/b,a.y/b);
}


inline int sign(int64 x){
	if (x < 0)	return -1;
	if (x == 0) return 0;
	return 1;		
}

inline bool between(int l,int x,int r){
	if (r < l)
		swap(l,r);
	return (l <= x && x<=r);
}

struct line{
	int64 a,b,c;
	line(){
		a=b=c=0;
	}
	line(const point& p1,const point& p2){
		a = p1.y - p2.y;
		b = p2.x - p1.x;
		c = -a*p1.x - b*p1.y;		
	}
	int side(const point& p) const{
		return sign(a*p.x+b*p.y+c);
	}
};

struct segment{
	point p1,p2;
	line l;
	segment(){
		p1=p2=point();
	}
	segment(const point& p1,const point& p2):p1(p1),p2(p2),l(p1,p2){
	
	}
	bool intersec(const segment& b) const{
//		line l(p1,p2);
		if (l.side(b.p1) * l.side(b.p2) != -1)
			return false;
//		l = line(b.p1,b.p2);		
		if (b.l.side(p1) * b.l.side(p2) != -1)
			return false;
		return true;
	}
	bool on(const point& p) const{
		if (l.side(p) != 0)
			return false;
		if (!between(p1.x,p.x,p2.x) || !between(p1.y,p.y,p2.y))
			return false;
		return true;
	}
};

struct triangle{
	point p1,p2,p3;
	triangle(const point& p1,const point& p2,const point& p3):p1(p1),p2(p2),p3(p3){		
	}	
	triangle(){
		p1=p2=p3=point();
	}
	bool in(const point& a) const{
/*		int64 s1 = abs((p2-p1)*(p3-p1));
		int64 s2 = abs((p1-a)*(p2-a));
		int64 s3 = abs((p2-a)*(p3-a));
		int64 s4 = abs((p3-a)*(p1-a));
		return (s1 == s2+s3+s4) && s1 && s2 && s3 && s4;*/
		int s1 = sign((p1-a)*(p2-a));
		int s2 = sign((p2-a)*(p3-a));
		int s3 = sign((p3-a)*(p1-a));
		return s1  && s2 && s3 && (s1 == s2) && (s1 == s3);
	}
	bool intersec(const triangle& r) const{
		if (in(r.p1) || in(r.p2) || in(r.p3))
			return true;
	//	if (in((r.p1+r.p2)/2) || in((r.p2+r.p3)/2) || in((r.p1+r.p3)/2))
	//		return true;
		if (in((r.p1+r.p2+r.p3)/3))
			return true;
		if (r.in(p1) || r.in(p2) || r.in(p3))
			return true;
		//if (r.in((p1+p2)/2) || r.in((p2+p3)/2) || r.in((p1+p3)/2))
	//		return true;
		if (r.in((p1+p2+p3)/3))
			return true;
			
		segment p12(p1,p2),p13(p1,p3),p23(p2,p3);
		segment rp12(r.p1,r.p2),rp13(r.p1,r.p3),rp23(r.p2,r.p3);
			
		if (p12.intersec(rp12))
			return true;
		if (p12.intersec(rp23))
			return true;
		if (p12.intersec(rp13))
			return true;
			
		if (p23.intersec(rp12))
			return true;
		if (p23.intersec(rp23))
			return true;
		if (p23.intersec(rp13))
			return true;
			
		if (p13.intersec(rp12))
			return true;
		if (p13.intersec(rp23))
			return true;
		if (p13.intersec(rp13))
			return true;
		return false;
	}
	bool on(const point& p) const{
		return segment(p1,p2).on(p) || segment(p2,p3).on(p) || segment(p1,p3).on(p);
	}
};

inline triangle operator+(const triangle& a,const point& p){	
	return triangle(a.p1+p,a.p2+p,a.p3+p);
}

vector<triangle> cur;
vector<segment> curs;
triangle have[1100];
point pos[1100];
int n;

map<point,ld> need;

inline bool check(const point& a){
	return 0 <= a.x && a.x <= X && 0<=a.y && a.y <= Y;
}

inline ld angle(const point& a,const point& o,const point& b){
	return abs(atan2((long double)((a-o)*(b-o)),(long double)((a-o)^(b-o))));
}

void recalc(const point& p,ld& res){
	res = 2*M_PI;
	for (int i=0;i<cur.size();i++){
		if (cur[i].p1 == p)
			res -= angle(cur[i].p2,cur[i].p1,cur[i].p3);
		else if (cur[i].p2 == p)
			res -= angle(cur[i].p1,cur[i].p2,cur[i].p3);
		else if (cur[i].p3 == p)
			res -= angle(cur[i].p2,cur[i].p3,cur[i].p1);
		else if (cur[i].on(p))
			res -= M_PI;			
	}		
	if (p.x == 0 || p.y == 0 || p.x == X || p.y == Y)
		res -= M_PI;
	if (p == point(0,0) || p == point(0,Y) || p == point(X,0) || p == point(X,Y))
		res -= M_PI/2;		
}

bool check(const triangle& want,const point& p){
	if (!check(want.p1) || !check(want.p2) || !check(want.p3))
		return false;
	for (int i=0;i<cur.size();i++)
		if (want.intersec(cur[i]))
			return false;
	for (int i=0;i<curs.size();i++)
		if (curs[i].on(p)){
			if (curs[i].p1 != p){
				if (want.p1 != p && (want.p1-p)*(curs[i].p1-p) == 0)
					return true;
				if (want.p2 != p && (want.p2-p)*(curs[i].p1-p) == 0)
					return true;
				if (want.p3 != p && (want.p3-p)*(curs[i].p1-p) == 0)
					return true;					
			}
			if (curs[i].p2 != p){
				if (want.p1 != p && (want.p1-p)*(curs[i].p2-p) == 0)
					return true;
				if (want.p2 != p && (want.p2-p)*(curs[i].p2-p) == 0)
					return true;
				if (want.p3 != p && (want.p3-p)*(curs[i].p2-p) == 0)
					return true;					
			}
		}
	return false;
}

void add(const triangle& want){
	cur.pb(want);
	curs.pb(segment(want.p1,want.p2));
	curs.pb(segment(want.p2,want.p3));
	curs.pb(segment(want.p1,want.p3));
	need[want.p1] = need[want.p2] = need[want.p3] = 2*M_PI;
	for (map<point,ld>::iterator iter = need.begin();iter != need.end();++iter){
		if (iter->first == want.p1 || iter->first == want.p2 || iter->first == want.p3)
			recalc(iter->first,iter->second);
		else {
			if (want.on(iter->first))
				iter->second -= M_PI;			
		}	
	}
}

void del(){
	triangle want = cur.back();cur.pop_back();
	curs.pop_back();
	curs.pop_back();
	curs.pop_back();		
	need[want.p1] = need[want.p2] = need[want.p3] = 2*M_PI;
	for (map<point,ld>::iterator iter = need.begin();iter != need.end();++iter){
		if (iter->first == want.p1 || iter->first == want.p2 || iter->first == want.p3)
			recalc(iter->first,iter->second);
		else {
			if (want.on(iter->first))
				iter->second += M_PI;			
		}	
	}
}

point findbest(){
	vector<pair<point,ld> > v(need.begin(),need.end());
	int n = v.size();
	point p = point();
	ld val = 1e100;
	for (int i=0;i<n;i++){
		if (abs(v[i].second - 2*M_PI) < 1e-7)
			need.erase(v[i].first);
		if  (abs(v[i].second) < 1e-7)
			continue;
		if (val > v[i].second){
			val = v[i].second;
			p = v[i].first;
		}
	}
	if (val > 1e10)
		p = point(-1,-1);
	else
		assert(val < 2*M_PI-(1e-7) && val > -(1e-7));
	return p;
}

int id[1000];

ld minangle(int a){	
	ld ang1 = angle(have[a].p1,have[a].p2,have[a].p3);
	ld ang2 = angle(have[a].p2,have[a].p1,have[a].p3);
	ld ang3 = angle(have[a].p1,have[a].p3,have[a].p2);	
	return min(min(ang1,ang2),ang3);
}

bool comp(int a,int b){
	return minangle(a) > minangle(b);
}

void perebor(){
	point p = findbest();
	if (p.x == -1){
		for (int i=0;i<n;i++)
			printf("%d %d\n",pos[i].x/6,pos[i].y/6);
		exit(0);
	}	
	int cnt = 50;
	for (int I=0;I<n && cnt>0;I++){
		int i = id[I];
		if (pos[i].x == -1){
			if (check(have[i] + p,p)){				
				--cnt;
				pos[i] = p;
				add(have[i] + p);
				perebor();
				del();
				pos[i] = point(-1,-1);
			}
			if (check(have[i] + (p-have[i].p2),p)){				
				--cnt;
				pos[i] = (p-have[i].p2);
				add(have[i] + (p-have[i].p2));
				perebor();
				del();
				pos[i] = point(-1,-1);
			}
			if (check(have[i] + (p-have[i].p3),p)){				
				--cnt;
				pos[i] = (p-have[i].p3);
				add(have[i] + (p-have[i].p3));
				perebor();
				del();
				pos[i] = point(-1,-1);
			}
		}
	}
}




int main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
	scanf("%d %d %d",&n,&X,&Y);
	X *= 6,Y*=6;
	for (int i=0;i<n;i++){
		scanf("%d %d %d %d %d %d",&have[i].p1.x,&have[i].p1.y,&have[i].p2.x,&have[i].p2.y,&have[i].p3.x,&have[i].p3.y);
		pos[i] = point(-1,-1);
		have[i].p2 = have[i].p2 - have[i].p1;
		have[i].p3 = have[i].p3 - have[i].p1;
		have[i].p1 = point(0,0);
		have[i].p2.x *= 6;have[i].p2.y *= 6;
		have[i].p3.x *= 6;have[i].p3.y *= 6;
	}
	for (int i=0;i<n;i++)
		id[i] = i;
	sort(id,id+n,comp);
	need[point(0,0)] = M_PI/2;
	need[point(X,0)] = M_PI/2;
	need[point(0,Y)] = M_PI/2;
	need[point(X,Y)] = M_PI/2;		
	curs.pb(segment(point(0,0),point(X,0)));
	curs.pb(segment(point(0,0),point(0,Y)));
	curs.pb(segment(point(X,0),point(X,Y)));
	curs.pb(segment(point(0,Y),point(X,Y)));
	perebor();
	assert(false);
    return 0;
}