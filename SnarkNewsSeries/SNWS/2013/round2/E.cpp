#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

struct point{
 	int x,y;
 	point(){};
 	point(int x,int y):x(x),y(y){};
 	void load(){
 		scanf("%d %d",&x,&y);
 	}
};

point operator-(const point& a,const point& b){
	return point(a.x - b.x, a.y - b.y);
}

point operator+(const point& a,const point& b){
	return point(a.x + b.x, a.y + b.y);
}

int operator*(const point& a,const point& b){
	return a.x * b.y - a.y * b.x;
}

double dist(const point& a,const point& b){
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

struct segment{
	point p1,p2;
	segment(){};
	segment(point p1,point p2):p1(p1),p2(p2){};
};

int sign(int x){
	return (x > 0) - (x < 0);
}

struct line{
	int a,b,c;
	line(){};
	line(point p1,point p2){
		a = p1.y - p2.y;
		b = p2.x - p1.x;
		c = -a * p1.x - b * p1.y;
	}
	int side(point p){
		return sign(a * p.x + b * p.y + c);
	}
};

bool intersect(segment a,segment b){
	line l(a.p1,a.p2);
	if (l.side(b.p1) * l.side(b.p2) == 1)
		return false;
	line l2(b.p1,b.p2);
	if (l2.side(a.p1) * l2.side(a.p2) == 1)
		return false;
	return true;
}

bool cmp(const point& a,const point& b){
	return (a * b) > 0;
}

bool cmpxy(const point& a,const point& b){
	if (a.y != b.y)
		return a.y < b.y;
	return a.x < b.x;
}

bool check(const point& a,const point& b,const point& c){
	return cmp(b - a, c - a);
}


point p1,p2;
vector<point> p;

void convex(vector<point>& p){
	if (p.size() <= 2)
		return;
	swap(p[0],*min_element(p.begin(),p.end(),cmpxy));
	point d = p[0];
	for (int i = 0; i < (int)p.size(); i++)
		p[i] = p[i] - d;

	sort(p.begin()+1,p.end(),cmp);
	vector<point> res;

	res.pb(p[0]);
	res.pb(p[1]);


	for (int i = 2; i < (int)p.size(); i++){
		while (res.size() > 0 && !check(res[res.size()-2],res[res.size()-1],p[i]))
			res.pop_back();
		res.pb(p[i]);
	}

	p = res;

	for (int i = 0; i < (int)p.size(); i++)
		p[i] = p[i] + d;
}

bool inside(point p,vector<point> v){
	int s = 0;
	int s2 = 0;
	v.pb(v[0]);

	for (int i = 0; i+1 < (int)v.size(); i++){
		int t = (v[i] - p) * (v[i+1] - p);
		s += t;
		s2 += abs(t);
	}

	return (s == s2) && s != 0;
}

vector<double> dst;
double dstall;

void initdist(vector<point> p){
	dst.resize(p.size()-1);
	for (int i = 0; i+1 < (int)p.size(); i++)
		dst[i] = dist(p[i],p[i+1]);
	for (int i = 1; i < (int)dst.size(); i++)
		dst[i] += dst[i-1];
	dstall = dst.back() + dist(p.back(),p[0]);
}

double getdist(int i,int j){
	if (i > j)
		swap(i,j);
	double t = dst[j-1] - (i ? dst[i-1] : 0.0);
	return min(t, dstall - t);
}


void solve(){
	p1.load();
	p2.load();
	int n;
	scanf("%d",&n);
	p.resize(n);
	for (int i = 0; i < n; i++)
		p[i].load();
	convex(p);
                
	if (inside(p1,p) || inside(p2,p)){
		printf("-1\n");
		return;
	}


	initdist(p);

	bool ok = true;

	p.pb(p[0]);


	for (int i = 0; i < n; i++)
		ok &= !intersect(segment(p[i],p[i+1]),segment(p1,p2));

	if (ok) {
		printf("%.10lf\n",dist(p1,p2));
		return;
	}

	vector<bool> ok1,ok2;
	ok1.resize(n);
	ok2.resize(n);

	for (int i = 0; i < n; i++){
		ok1[i] = true;
		for (int j = 0; j < n; j++)
			if (j != i && (j + 1) % n != i)
				if (intersect(segment(p[j],p[j+1]),segment(p[i],p1)))
					ok1[i] = false;

	}

	for (int i = 0; i < n; i++){
		ok2[i] = true;
		for (int j = 0; j < n; j++)
			if (j != i && (j + 1) % n != i)
				if (intersect(segment(p[j],p[j+1]),segment(p[i],p2)))
					ok2[i] = false;
	}

	double ans = 1e100;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (ok1[i] && ok2[j])	
				ans = min(ans, dist(p1,p[i]) + dist(p2,p[j]) + getdist(i,j));

	printf("%.10lf\n",ans);
}


int main(){
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

    int t;
    scanf("%d",&t);

    while (t -- > 0)
    	solve();


    return 0;
} 