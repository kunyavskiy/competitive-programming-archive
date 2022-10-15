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
#define sqr(x) ((x)*(x))
using namespace std;

typedef long long int64;
typedef long double ld;
const ld eps=1e-09;


struct point{
	ld x,y;	
	point(){};
	point(ld X,ld Y){
		x=X;
		y=Y;
	}
};

ld operator* (const point& a,const point& b){
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}

bool operator< (const point& a,const point& b){
	if (abs(a.x-b.x)>eps)
		return a.x<b.x;
	return a.y<b.y-eps;
}

bool operator==(const point& a,const point& b){
	return abs(a.x-b.x)<eps && abs(a.y-b.y)<eps;
}

struct segment{
	point p1,p2;
	segment(){};
	segment(const point &a,const point &b){
		p1=a;
		p2=b;
	}
	bool isend(const point& a) const{
		return a==p1 || a==p2;
	}
};

istream& operator>>(istream& istr,point& p){
	istr>>p.x>>p.y;
	return istr;
}

istream& operator>>(istream& istr,segment& s){
	istr>>s.p1>>s.p2;
	return istr;
}

struct line{
	ld a,b,c;
	line(){};
	line(ld A,ld B,ld C){
		a=A;b=B;c=C;
	}
	line(const point& p1,const point& p2){
		a=p1.y-p2.y;
		b=p2.x-p1.x;
		c=-a*p1.x-b*p1.y;
	}
	line(const segment& s){
		a=s.p1.y-s.p2.y;
		b=s.p2.x-s.p1.x;
		c=-a*s.p1.x-b*s.p1.y;
	}
	ld operator* (point p) const{
		return a*p.x+b*p.y+c;
	}
	bool on(const point& p) const {
		return abs(this->operator*(p))<eps;
	}
	bool on(const segment& s) const{
		return on(s.p1) && on(s.p2);
	}
};

point p[50*50];
int pptr;
segment s[50];
int n;

int sign(ld a){
	if (a>eps)
		return 1;
	if (a<-eps)
		return -1;
	return 0;
}

bool intersec(const segment& a,const line& b){
	return sign(b*a.p1)*sign(b*a.p2)<0;
}

ld det (ld a, ld b, ld c, ld d) {
	return a * d - b * c;
}
 
point intersec (const line& m,const line& n) {
	point res;
	ld zn = det (m.a, m.b, n.a, n.b);
	assert(abs (zn) > eps);
	res.x = - det (m.c, m.b, n.c, n.b) / zn;
	res.y = - det (m.a, m.c, n.a, n.c) / zn;
	return res;
}
void intersec(const segment& a,const segment& b){
	line l1(a);
	line l2(b);
	if (intersec(a,l2) && intersec(b,l1))
		p[pptr++]=intersec(l1,l2);
}

void genall(){	
	for (int i=0;i<n;i++){
		p[pptr++]=s[i].p1;
		p[pptr++]=s[i].p2;
		for (int j=0;j<n;j++)
			intersec(s[i],s[j]);
	}
	sort(p,p+pptr);
	pptr=unique(p,p+pptr)-p;
}

vector<int> g[50*50];
bool used[50];

void genline(const line& l){
	vector<int> pl;
	for (int i=0;i<pptr;i++)
		if (l.on(p[i]))
			pl.pb(i);
	int sz=pl.size();
	int delt=0;
	for (int i=0;i<sz;i++)
	{
		if (delt>0){
			g[pl[i]].pb(pl[i-1]);
			g[pl[i-1]].pb(pl[i]);
		}
		for (int j=0;j<n;j++)
			{
				if (s[j].isend(p[pl[i]]) && l.on(s[j]))
				{
					if (used[j])
						--delt;
					else {
						++delt;
						used[j]=true;
					}
				}
			}
		assert(delt>=0);
	}	
}

void gengraf(){
	genall();
	for (int i=0;i<n;i++)
		if (!used[i])
			genline(line(s[i]));
}

ld ans=0;
int tin[50*50];
int tup[50*50];
int dused[50*50];

void dfs(int v,int p){
	static int counter=0;
	tup[v]=tin[v]=++counter;
	dused[v]=1;
	int sz=g[v].size();
	for (int i=0;i<sz;i++){
		if (g[v][i]==p)
			continue;
		if (dused[g[v][i]]==1){
			tup[v]=min(tup[v],tin[g[v][i]]);
			continue;
		}
		if (dused[g[v][i]]==0){
			dfs(g[v][i],v);
			if (tup[g[v][i]]>tin[v]){
				ans+=::p[v] * ::p[g[v][i]];
			}
		}
		tup[v]=min(tup[v],tup[g[v][i]]);
	}
	dused[v]=2;
}

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
	cin>>n;
	for (int i=0;i<n;i++)
		cin>>s[i];
	gengraf();
	for (int i=0;i<pptr;i++)
		if (dused[i]==0)
			dfs(i,-1);
	cout.precision(15);
	cout<<fixed<<ans<<endl;
  return 0;
}