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

#define hex botva

using namespace std;

typedef long long int64;
typedef double ld;

const ld eps=1e-3;

struct point{
	ld x,y;
	point(){};
	point(ld X,ld Y){
		x=X;y=Y;
	}
};

bool operator==(const point& a,const point& b){
	return abs(a.x-b.x)<eps && abs(a.y-b.y)<eps;
}

bool operator!=(const point& a,const point& b){
	return !(a==b);
}

bool operator<(const point& a,const point& b){
	if (abs(a.y - b.y) > eps)
		return a.y > b.y;
	return a.x < b.x-eps;
}

point operator+(point a,point b){
	return point(a.x+b.x,a.y+b.y);
}

point operator-(point a,point b){
	return point(a.x-b.x,a.y-b.y);
}

point operator*(point a,ld b){
	return point(a.x*b,a.y*b);
}

point operator/(point a,ld b){
	return point(a.x/b,a.y/b);
}

point operator!(point a){
	return point(-a.y,a.x);
}

ld operator*(point a,point b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

struct hex{
	vector<point> pts;
	vector<point> mdl;
	point center;
	hex(point a,point b){
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
	hex(point a,ld b){
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

bool operator!=(const hex& a,const hex& b){
	return a<b || b<a;
}

bool operator==(const hex& a,const hex& b){
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
}

vector<string> connectors;
vector<point> pt;
map<point,int> num;
vector<int> g[100000];
bool used[100000];

int getnum(point p){
	if (num.find(p)==num.end()){
		num[p]=pt.size();
		pt.pb(p);
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
	for (int i=0;i<t.size();i++){
		if (t[i]==';')
			last=-1;
		else {
			int num=t[i]-'0';
			if (last!=-1)
				addcon(a((last+rot)%6),a((num+rot)%6));
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

int main()
{
	FILE* inp=fopen("input.txt","r");
	FILE* out=fopen("output.txt","r");
	int test;
	fscanf(inp,"%d",&test);
	for (;test;--test){
		h.clear();
		for (int i=0;i<pt.size();i++)
			g[i].clear();
		pt.clear();
		num.clear();
		connectors.clear();
		memset(used,false,sizeof(used));
		FILE* pic=fopen("picture0.txt","w");
		int r;
		fscanf(inp,"%d\n",&r);
		gen(r);
		for (int i=0;i<h.size();i++){
			for (int j=0;j<6;j++)
				fprintf(pic,"%.10lf %.10lf %.10lf %.10lf\n",h[i][j].x,h[i][j].y,h[i][(j+1)%6].x,h[i][(j+1)%6].y);
		}
		fclose(pic);
		int cnt=3*(r*r+r);
		assert(h.size()==cnt+1);
		for (int i=0;i<cnt;i++){	
			char s;
			string t="";
			for (fscanf(inp," %c ",&s);s!='.';fscanf(inp," %c ",&s))
				t+=s;
			connectors.pb(t);
		}
		addcon(point(0,0),mid1);
		vector<int> UC;
		for (int i=0;i<h.size();i++){
			if (h[i].center==point(0,0))
				continue;		
			int a,b;
			fscanf(out,"%d %d",&a,&b);
			assert (0<=b && b<=5);
			assert(0<=a && a<cnt);
			addcon(h[i],connectors[a],b);
			UC.pb(a);
		}
		sort(UC.begin(),UC.end());
		assert(unique(UC.begin(),UC.end())==UC.end());
		dfs(getnum(point(0,0)));
		pic=fopen("picture1.txt","w");
		for (int i=0;i<pt.size();i++)
			if (used[i])
				for (int j=0;j<g[i].size();j++)
					fprintf(pic,"%.10lf %.10lf %.10lf %.10lf\n",pt[i].x,pt[i].y,pt[g[i][j]].x,pt[g[i][j]].y);
		fclose(pic);
	
		pic=fopen("picture2.txt","w");
		for (int i=0;i<pt.size();i++)
			if (!used[i])
				for (int j=0;j<g[i].size();j++)
				fprintf(pic,"%.10lf %.10lf %.10lf %.10lf\n",pt[i].x,pt[i].y,pt[g[i][j]].x,pt[g[i][j]].y);
		fclose(pic);
		
		pic=fopen("picturev.txt","w");
		int score=0;
		for (int i=0;i<h.size();i++)
			if (h[i].center != point(0,0))
				for (int j=0;j<6;j++)
					if (used[getnum(h[i](j))])
						score++;
		fprintf(pic,"%d",score);
		fclose(pic);		
		system("CALL draw.exe");
		system("del picture*.txt");
	}
    return 0;
}