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
 
#define forv(i,v) for (int i=0,sz=v.size();i<sz;++i)
 
 
#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif
 
#define hex botva
 
using namespace std;
 
const int MAXPT=7000;
 
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
 
int ptkol;
map<point,int> num;
vector<point> pt;
int inhex[MAXPT];
 
 
int getnum(point p){
	if (num.find(p)==num.end()){
		num[p]=ptkol++;
		pt.pb(p);
		assert(pt.size() < MAXPT-5);
	}
	return num[p];
}
 
const ld sq3=sqrt(3.0)/2;
const ld si[6]={sq3,sq3,0,-sq3,-sq3,0};
const ld co[6]={-0.5,0.5,1,0.5,-0.5,-1};
 
 
struct hex{
	vector<int> mdl;
	point center;
	hex(const point& a){
		mdl.resize(6);
		center=a;
		for (int i=0;i<6;++i)
			mdl[i]=getnum(point(co[i],si[i])+center);		
	}
	
	int& operator[](int a){
		return mdl[a];
	}
	int operator[](int a) const{
		return mdl[a];
	}
};
 
bool operator<(const hex& a,const hex& b){
	return a.center < b.center;
}
 
inline bool operator!=(const hex& a,const hex& b){
	return a.center != b.center;
}
 
inline bool operator==(const hex& a,const hex& b){
	return a.center == b.center;
}
 
vector<hex> h;
int mid1;
 
void gen(int r){
	getnum(point(0,0));
	vector<point> H;
	H.pb(point(0,0));
	mid1=getnum(point(co[0],si[0]));
	for (int it=0;it<r;it++){
		int sz=H.size();
		for (int i=0;i<sz;++i)
			for (int j=0;j<6;++j){
				point c=H[i]+point(2*co[j],2*si[j]);			
				H.pb(c);
			}
		sort(H.begin(),H.end());
		H.erase(unique(H.begin(),H.end()),H.end());
	}
	forv (i,H)
		if (H[i]!=point(0,0))
			h.push_back(hex(H[i]));
	memset(inhex,0,sizeof(inhex));
	forv (i,h)
		for (int j=0;j<6;++j)
			inhex[h[i][j]]++;
	sort(h.begin(),h.end());
//	cerr<<pt.size()<<endl;
}
 
vector<string> connectors;
vector<int> g[MAXPT];
int used[MAXPT];
int connum[MAXPT];
int rot[MAXPT];
int bconnum[MAXPT];
int brot[MAXPT];
int bans;
 
inline void addcon(int num1,int num2){
	g[num1].pb(num2);
	g[num2].pb(num1);	
}
 
void addcon(hex a,string t,int rot){
	int last=-1;
	t=t+';';
	forv (i,t){
		if (t[i]==';')
			last=-1;	
		else {
			int num=t[i]-'0';
			if (last!=-1)
				addcon(a[(last+rot)%6],a[(num+rot)%6]);
			last=num;
		}
	}
}
 
inline void delcon(int num1,int num2){
	for (int it=0;it<2;++it){
		for (int i=0,sz=g[num1].size();i<sz;++i)
			if (g[num1][i]==num2){
				swap(g[num1][i],g[num1][g[num1].size()-1]);
				g[num1].pop_back();
				break;
			}
		swap(num1,num2);
	}
}
 
void delcon(hex a,string t,int rot){
	int last=-1;
	t=t+';';
	forv (i,t){
		if (t[i]==';')
			last=-1;	
		else {
			int num=t[i]-'0';
			if (last!=-1)
				delcon(a[(last+rot)%6],a[(num+rot)%6]);
			last=num;
		}
	}
}
 
void setrot(int v,int val){
	delcon(h[v],connectors[connum[v]],rot[v]);
	rot[v]=val;
	addcon(h[v],connectors[connum[v]],rot[v]);
}
 
 
int USEDITER;
 
int dfs(int v){
	int val=0;
	used[v]=USEDITER;
	forv (i,g[v]){
		if (used[g[v][i]] != USEDITER)
			val+=dfs(g[v][i]);
	}		
	return val+inhex[v];
}
 
 
void gengraf(){
	for (int i=0;i<ptkol;++i)
		g[i].clear();
	addcon(0,mid1);
	forv (i,h)
		addcon(h[i],connectors[connum[i]],rot[i]);
		
}
 
int calc(){
	++USEDITER;
	int cnt=dfs(0);
	return cnt;	
}
 
void genrandom(int cnt){
	random_shuffle(connum,connum+cnt);
	for (int i=0;i<cnt;++i)
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
			TL2=(59.0-done)/test;
			ITER=50;
			TL=TL2*0.7;
		}
		else if (curtests==16){
			TL2=(87.0-done)/test;
			ITER=75;
			TL=TL2*0.6;
		}
		else {
			TL2=(98.0-done)/test;	
			ITER=25;
			TL=TL2*0.5;
		}
	#else
		ITER=10;
		TL=1;
		TL2=1;
	#endif
}
 
inline bool TLE(){
	return (clock()-start)/CLOCKS_PER_SEC > TL;
}
 
inline bool TLE2(){
	return (clock()-start)/CLOCKS_PER_SEC > TL2;
}
 
int optimized[MAXPT];
int OPTITER;
 
namespace greedy{
 
	inline int kol(int a){
		string& s=connectors[a];
		int cnt=0;
		forv (i,s)
			cnt+=('0' <= s[i] && s[i]<='5');
		return cnt;
	}
 
	inline bool cmpkol(int a,int b){
		return kol(a) > kol(b);
	}
	
	inline bool cmpcenter(int a,int b){
		ld val1=h[a].center.x*h[a].center.x + h[a].center.y*h[a].center.y;
		ld val2=h[b].center.x*h[b].center.x + h[b].center.y*h[b].center.y;
		return val1 < val2-eps;
	}
	
	int por1[MAXPT];
	int por2[MAXPT];
	
	void gen(int* con,int* rot){
		for (int i=0;i<cnt;++i)
			por1[i]=por2[i]=i;
		sort(por1,por1+cnt,cmpkol);
		sort(por2,por2+cnt,cmpcenter);
		for (int i=0;i<cnt;++i){
			con[por2[i]]=por1[i];
			rot[i]=rand()%6;
		}
	}
}
 
 
void optimize(){
 
	if (h.size() > 300){		
		for (int i=0;i<40;++i)
			g[0].pb(h[greedy::por2[(h.size()/40)*i]][rand()%6]);
		calcall();
		++OPTITER;		
		for (int IT=0;IT<25;IT++){
			int usedpt[6];
			int cnt;	
			++OPTITER;
			bool q=false;
			forv (i,h){
				if (optimized[i]==OPTITER) continue;
				bool use=false;
				cnt=0;
				for (int j=0;j<6;++j)
					if (used[h[i][j]]==USEDITER)
						usedpt[cnt++]=h[i][j];
				if (!cnt) continue;
					if (cnt>1){
					for (int i=0;i<cnt && !use;++i)
						for (int j=i+1;j<cnt && !use;++j)
							for (int k=0,sz=g[usedpt[i]].size();k<sz && !use;k++)
								if (g[usedpt[i]][k] == usedpt[j])
									use=true;					
				}
				optimized[i]=OPTITER;
				if (!use){
					q=true;
					int best=rot[i],bval=-1;
					for (int I=0;I<6;++I){
						setrot(i,I);
						int val=calc();
						if (val > bval || (val == bval && (rand()&1))){
							best=I;
							bval=val;
						}						
					}
					if (best!=-1)
						setrot(i,best);					
				}
			}	
			if (!q)
				break;
		}		
	}
	g[0].clear();
	g[0].pb(mid1);
	
 
	while (!TLE2()){
		calcall();
		int usedpt[6];
		int cnt;	
		++OPTITER;
		for (;!TLE2();){
			bool q=false;
			forv (i,h){
				if (optimized[i]==OPTITER) continue;
				bool use=false;
				cnt=0;
				for (int j=0;j<6;++j)
					if (used[h[i][j]]==USEDITER)
						usedpt[cnt++]=h[i][j];
				if (!cnt) continue;
					if (cnt>1){
					for (int i=0;i<cnt && !use;++i)
						for (int j=i+1;j<cnt && !use;++j)
							for (int k=0,sz=g[usedpt[i]].size();k<sz && !use;k++)
								if (g[usedpt[i]][k] == usedpt[j])
									use=true;					
				}
				optimized[i]=OPTITER;
				if (!use){
					q=true;
					int best=rot[i],bval=-1;
					for (int I=0;I<6;++I){
						setrot(i,I);
						int val=calc();
						if (val > bval || (val == bval && (rand()&1))){
							best=I;
							bval=val;
						}						
					}
					if (best!=-1)
						setrot(i,best);					
				}
			}	
			if (!q)
				break;
		}
		
		
		
	
		++OPTITER;
		while (!TLE2()){
			bool q=false;
			forv (i,h){
				if (optimized[i]==OPTITER) continue;
				cnt=0;
				for (int j=0;j<6;++j)
					if (used[h[i][j]]==USEDITER)
						cnt++;
				if (cnt == 0)
					continue;
				optimized[i]=OPTITER;
				q=true;
				int best=rot[i],bval=-1;
				for (int I=0;I<6;++I){
					setrot(i,I);
					int val=calc();
					if (val > bval || (val == bval && (rand()&1))){
						best=I;
						bval=val;
					}						
				}
				if (best!=-1)
					setrot(i,best);
			}	
			if (!q)
				break;	
		}
	}
}
 
bool dogreedy(int cnt){
	if (curtests == 9)
		return true;
	int discon=0;
	for (int i=0;i<cnt;i++)
		if (connectors[i].find(';') != string::npos)
			discon++;
	return discon*20 > cnt;
}
 
int main()
{
	srand(time(NULL));
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
		for (int i=0;i<cnt;++i){	
			char s;
			string t="";
			for (scanf(" %c ",&s);s!='.';scanf(" %c ",&s))
				t+=s;
			connectors.pb(t);
		}
		for (int i=0;i<cnt;++i)
			connum[i]=i;
		if (dogreedy(cnt))
			greedy::gen(connum,rot);
		else
		    genrandom(cnt);
		gengraf();
		optimize();
		int tmp=calc();
		bans=tmp;
		memcpy(bconnum,connum,cnt*sizeof(int));
		memcpy(brot,rot,cnt*sizeof(int));
		while (!TLE2()){
			genrandom(cnt);
			gengraf();
			optimize();
			int tmp=calc();
			if (tmp > bans){
				bans=tmp;
				memcpy(bconnum,connum,cnt*sizeof(int));
				memcpy(brot,rot,cnt*sizeof(int));
			}
		}
		#ifdef LOCAL	
			cerr<<bans<<endl;
		#endif
		for (int i=0;i<cnt;++i)
			printf("%d %d\n",bconnum[i],brot[i]);	
		if (test>1)
			printf("\n");
	}
    return 0;
}   