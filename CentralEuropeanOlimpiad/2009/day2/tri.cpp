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
#define all(v) v.begin(),v.end()

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

struct point{
	int x,y;
	point(int x,int y):x(x),y(y){		
	}
	point(){
	}
};

int64 mult(const point& a,const point& b){
	return a.x*1LL*b.y - a.y*1LL*b.x;
}

bool operator<(const point& a,const point& b){
	int64 tmp = mult(a,b);
	if (tmp != 0)
		return tmp > 0;
	return a.x*1LL*a.x + a.y*1LL*b.y < b.x*1LL*b.x + b.y*1LL*b.y;
}

bool operator== (const point& a,const point& b){
	return (a.x == b.x) && (a.y == b.y);
}

bool cmpang(const point& a,const point& b){
	int64 tmp = mult(a,b);
	if (tmp != 0)
		return tmp > 0;
	return false;
}

point operator-(const point& a,const point& b){
	return point(a.x-b.x,a.y-b.y);
}

point operator+(const point& a,const point& b){
	return point(a.x+b.x,a.y+b.y);
}

bool cmpxy(const point& a,const point& b){
	if (a.y != b.y)
		return a.y < b.y;
	return a.x < b.x;
}

void convex(vector<point>& v){
	if (v.size() <= 1)
		return;
	sort(all(v),cmpxy);
	point zero = v[0];
	int n = v.size();
	for (int i=0;i<n;i++)
		v[i] = v[i] - zero;
		
	sort(v.begin()+1,v.end());	
		
	vector<point> conv;
	conv.pb(v[0]);
	conv.pb(v[1]);
	for (int i=2;i<n;i++){
		for (;conv.size() >= 2 && mult(conv.back()-conv[conv.size()-2],v[i] - conv[conv.size()-2]) <= 0;)
			conv.pop_back();
		conv.pb(v[i]);
	}			
	
	v = conv;
	
	n = v.size();
	for (int i=0;i<n;i++)
		v[i] = v[i] + zero;
}

void del_back(vector<point>& v){
	int minv = min_element(all(v)) - v.begin();
	rotate(v.begin(),v.begin()+minv,v.end());
	reverse(v.begin()+1,v.end());
	int maxv = max_element(all(v)) - v.begin();
	v.erase(v.begin()+maxv+1,v.end());
}

void del_point(vector<point>& v){
	sort(all(v));
	for (int i=1;i<v.size();i++)
		if (mult(v[i],v[i-1]) == 0)
			v[i] = v[i-1];
	v.erase(unique(all(v)),v.end());
}

void do_all(vector<point>& v){
//	del_point(v);
	convex(v);
	del_back(v);
/*	for (int i=0;i<v.size();i++)
		cerr<<v[i].x <<" "<<v[i].y <<endl;
	cerr<<endl<<endl;*/
}

struct line{
	int64 a,b,c;	
	line(){
	}
	line(const point& p1,const point& p2){
		a = p1.y - p2.y;
		b = p2.x - p1.x;
		c = -a * p1.x - b*p1.y;
		if (c > 0){
			a = -a,b=-b,c=-c;
		}	
	}
	int64 dst(const point& p) const{
		return a*p.x+b*p.y+c;
	}
};

bool check(const line& l,const vector<point>& p){
	int lf = 0;
	int rg = p.size()-1;
	
	for (;rg-lf > 5;){
		int x1 = lf + (rg-lf)/3;
		int x2 = rg - (rg-lf)/3;
		int64 f1 = l.dst(p[x1]);
		int64 f2 = l.dst(p[x2]);
		if (f1 <= 0 || f2 <= 0)
			return true;
		if (f1 < f2)
			rg = x2;
		else
			lf = x1;
	}
	
	for (int i=lf;i<=rg;i++)
		if (l.dst(p[i]) <= 0)
			return true;
	return false;
}


const int BSIZE = 1000;

vector<point> p;
vector<point> part[500];


point p1[110000];
point p2[110000];

int n,k;

char s[220000];

int main(){
//	ld start = clock();

    freopen("tri.in","r",stdin);
    freopen("tri.out","w",stdout);
	scanf("%d %d",&n,&k);
	p.resize(n);
	for (int i=0;i<n;i++)
		scanf("%d %d",&p[i].x,&p[i].y);
	del_point(p);
	sort(all(p));
	n = p.size();
	
	bool topart = true;
	
	for (int i=0;i<k;i++){
		scanf("%d %d %d %d",&p1[i].x,&p1[i].y,&p2[i].x,&p2[i].y);
		topart &= !p1[i].x;
		topart &= !p2[i].y;
	}
	
	if (topart){
		do_all(p);
	
	
		for (int i=0;i<k;i++){
			point p1 = ::p1[i];
			point p2 = ::p2[i];
			bool q = check(line(p1,p2),p);
			printf("%c\n","NY"[q]);
		}
		return 0;
	}

	
	for (int i=0;i*BSIZE < n;i++){
		part[i] = vector<point>(p.begin()+i*BSIZE,p.begin()+min(n,(i+1)*BSIZE));
		do_all(part[i]);
	}
	
	for (int it=0;it<k;it++){
	
		point p1 = ::p1[it];
		point p2 = ::p2[it];
		
		if (p2 < p1)
			swap(p1,p2);
			
		line l(p1,p2);
		
		bool q = false;	
		
		int lf = lower_bound(all(p),p1,cmpang) - p.begin();
		int rg = upper_bound(all(p),p2,cmpang) - p.begin();		
		
		int lblock = lf/BSIZE;
		int rblock = rg/BSIZE;
		

		
		for (int i = lf;i < (lblock+1)*BSIZE && i < rg && !q;i++)
			q |= (l.dst(p[i]) <= 0);
			
		for (int i = rg-1;i >= (rblock)*BSIZE && i >=lf && !q;i--)
			q |= (l.dst(p[i]) <= 0);
			
		for (int i = lblock+1;i<rblock && !q;i++)
			q |= check(l,part[i]);	
		
		s[2*it] = "NY"[q];
		s[2*it+1] = '\n';
	}
	
	puts(s);
	
//	cerr << (clock() - start) / CLOCKS_PER_SEC << endl;
	
	return 0;
}