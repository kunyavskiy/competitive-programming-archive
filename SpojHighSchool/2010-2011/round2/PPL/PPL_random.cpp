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

#undef assert
#define assert(e) ;


#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define hex botva

using namespace std;

const int MAXPT=40000;

typedef long long int64;
typedef double ld;

const ld eps=1e-9;

struct point{
	ld x,y;
	point(){};
	point(ld X,ld Y){
		x=X;y=Y;
	}
};

inline bool operator==(const point& a,const point& b){
	return abs(a.x-b.x)<eps && abs(a.y-b.y)<eps;
}

inline bool operator!=(const point& a,const point& b){
	return !(a==b);
}

inline bool operator<(const point& a,const point& b){
	if (abs(a.y - b.y) > eps)
		return a.y > b.y;
	return a.x < b.x-eps;
}

inline point operator+(const point& a,const point& b){
	return point(a.x+b.x,a.y+b.y);
}

inline point operator-(const point& a,const point& b){
	return point(a.x-b.x,a.y-b.y);
}

inline point operator*(const point& a,ld b){
	return point(a.x*b,a.y*b);
}

inline point operator/(const point& a,ld b){
	return point(a.x/b,a.y/b);
}

inline point operator!(const point& a){
	return point(-a.y,a.x);
}

inline ld operator*(const point& a,const point& b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

struct hex{
	vector<point> pts;
	vector<point> mdl;
	point center;
	hex(const point& a,const point& b){
		pts.resize(6);
		mdl.resize(6);
		ld r=a*b;
		center=a+(b-a)/2+(!(b-a))*sqrt(3)/2;
		for (int i=0;i<6;i++){
			ld ang=5*M_PI/6-M_PI/3*i;
			pts[i]=center+point(cos(ang),sin(ang))*r;
		}
		for (int i=0;i<6;i++)
			mdl[i]=(pts[i]+pts[(i+1)%6])/2;
	}
	hex(const point& a,ld b){
		pts.resize(6);
		mdl.resize(6);
		ld r=b;
		center=a;
		for (int i=0;i<6;i++){
			ld ang=5*M_PI/6-M_PI/3*i;
			pts[i]=center+point(cos(ang),sin(ang))*r;
		}
		for (int i=0;i<6;i++)
			mdl[i]=(pts[i]+pts[(i+1)%6])/2;
	}
	
	point& operator[](int a){
		return pts[a];
	}
	point operator[](int a) const{
		return pts[a];
	}
	point& operator()(int a){
		return mdl[a];
	}
	point operator()(int a) const{
		return mdl[a];
	}
};

bool operator<(const hex& a,const hex& b){
	for (int i=0;i<6;i++)
		if (a.pts[i]!=b.pts[i])
			return a.pts[i] < b.pts[i];
	return false;
}

inline bool operator!=(const hex& a,const hex& b){
	return a<b || b<a;
}

inline bool operator==(const hex& a,const hex& b){
	return !(a!=b);
}

vector<hex> h;
point mid1;

void gen(int r){
	h.pb(hex(point(0,0),5));
	assert(h[0].center==point(0,0));
	mid1=h[0](0);
	for (int it=0;it<r;it++){
		int sz=h.size();
		for (int i=0;i<sz;i++)
			for (int j=0;j<6;j++){
				h.pb(hex(h[i][j],h[i][(j+1)%6]));
				h.pb(hex(h[i][(j+1)%6],h[i][j]));
			}
		sort(h.begin(),h.end());
		h.erase(unique(h.begin(),h.end()),h.end());
	}
	for (int i=0;i<h.size();i++)
		if (h[i].center==point(0,0)){
			swap(h[i],h[h.size()-1]);
			break;
		}
	h.pop_back();
	sort(h.begin(),h.end());
}

vector<string> connectors;
vector<point> pt;
map<point,int> num;
vector<int> g[MAXPT];
bool used[MAXPT];

int getnum(point p,bool q=true){
	if (num.find(p)==num.end()){
		if (!q) return MAXPT-1;
		num[p]=pt.size();
		pt.pb(p);
		assert(pt.size()<=MAXPT-5);
	}
	return num[p];
}

void addcon(point a,point b){
	int num1=getnum(a);
	int num2=getnum(b);
	g[num1].pb(num2);
	g[num2].pb(num1);	
}

void addcon(hex a,string t,int rot){
	int last=-1;
	int first=-1;
	t=t+';';
	for (int i=0;i<t.size();i++){
		if (t[i]==';'){
			if (first!=-1)
				addcon(a((last+rot)%6),a((first+rot)%6));
			last=-1;
			first=-1;
		}
		else {
			int num=t[i]-'0';
			if (last!=-1)
				addcon(a((last+rot)%6),a((num+rot)%6));
			else
				first=num;	
			last=num;
		}
	}
}

void dfs(int v){
	used[v]=true;
	for (int i=0;i<g[v].size();i++)
		if (!used[g[v][i]])
			dfs(g[v][i]);
		
}

int connum[MAXPT];
int rot[MAXPT];
int bconnum[MAXPT];
int brot[MAXPT];
int bans;

void gengraf(){
	for (int i=0;i<pt.size();i++)
		g[i].clear();
	pt.clear();
	num.clear();
	addcon(point(0,0),mid1);
	for (int i=0;i<h.size();i++)
		addcon(h[i],connectors[connum[i]],rot[i]);
		
}

int calc(){
	memset(used,0,(pt.size()+2)*sizeof(int));
	dfs(getnum(point(0,0)));
	int cnt=0;
	for (int i=0;i<pt.size();i++)
		if (used[i])
			cnt+=g[i].size();
	cnt/=2;
	return cnt;	
}

void genrandom(int cnt){
	random_shuffle(connum,connum+cnt);
	for (int i=0;i<cnt;i++)
		rot[i]=rand()%6;
}

int calcall(){
	gengraf();
	return calc();
}

double start;
double globstart;
double TL,TL2;
int curtests;
int test;
int ITER;
int cnt;

void initTLE(){
	start=clock();
	#ifndef LOCAL
		ld done=(start-globstart)/CLOCKS_PER_SEC;
		if (curtests==9){
			TL2=(60.0-done)/test;
			ITER=50;
			TL=TL2*0.7;
		}
		else if (curtests==16){
			TL2=(85.0-done)/test;
			ITER=75;
			TL=TL2*0.6;
		}
		else {
			TL2=(95.0-done)/test;	
			ITER=25;
			TL=TL2*0.5;
		}
	#else
		ITER=10;
		TL=5;
		TL2=10;
	#endif
}

inline bool TLE(){
	return (clock()-start)/CLOCKS_PER_SEC > TL;
}

inline bool TLE2(){
	return (clock()-start)/CLOCKS_PER_SEC > TL2;
}

void optimize(){
	memcpy(connum,bconnum,cnt*sizeof(int));
	memcpy(rot,brot,cnt*sizeof(int));
	calcall();
	for (;!TLE2();){
		bool q=false;
		for (int i=0;i<h.size();i++){
			int kol=0;
			for (int j=0;j<6;j++)
				if (used[getnum(h[i](j),false)])
					kol++;
			if (kol==1){
				q=true;
				int best=rot[i],bval=-1;
				rot[i]=0;			
				for (int& I=rot[i];I<6;I++){
					int val=calcall();
					if (val > bval){
						best=I;
						bval=val;
					}						
				}
				if (best!=-1)
					rot[i]=best;
				calcall();
				break;
			}			
		}	
		if (!q)
			break;
	}
	memcpy(bconnum,connum,cnt*sizeof(int));
	memcpy(brot,rot,cnt*sizeof(int));
}



int main()
{
	globstart=clock();
	#ifdef LOCAL
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	scanf("%d",&test);
	curtests=test;
	for (;test;--test){
		initTLE();
		h.clear();
		connectors.clear();
		int r;
		scanf("%d\n",&r);
		gen(r);
		cnt=3*(r*r+r);
		for (int i=0;i<cnt;i++){	
			char s;
			string t="";
			for (scanf(" %c ",&s);s!='.';scanf(" %c ",&s))
				t+=s;
			connectors.pb(t);
		}
		for (int i=0;i<cnt;i++)
			connum[i]=i;
		bans=0;
		while (!TLE()){
			for (int iter=0;iter<ITER;++iter){
				genrandom(cnt);
				gengraf();
				int tmp=calc();
				if (tmp > bans){
					bans=tmp;
					memcpy(bconnum,connum,cnt*sizeof(int));
					memcpy(brot,rot,cnt*sizeof(int));
				}
			}
		}				
		optimize();
		for (int i=0;i<cnt;i++)
			printf("%d %d\n",bconnum[i],brot[i]);	
		if (test>1)
			printf("\n");
	}
    return 0;
}