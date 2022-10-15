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

using namespace std;

typedef long long int64;
typedef long double ld;

struct point{
	int x,y;	
};

struct line{
	int a,b,c;
	line(){};
	line(point p1,point p2){
		a=p1.y-p2.y;
		b=p2.x-p1.x;
		c=-a*p1.x-b*p1.y;		
	}		
};

int operator*(line l,point p){
	int64 tmp=l.a*p.x+l.b*p.y+l.c;
	if (tmp>0)
		return 1;
	if (tmp==0)
		return 0;
	return -1;
}

int operator*(point p,line l){
	return l*p;
}

point p[4];

bool check(){
	line l(p[0],p[1]);
	if (((l*p[2]) * (l*p[3])) != 1)
		return false;
		
	l = line(p[1],p[2]);
	if (((l*p[0]) * (l*p[3])) != 1)
		return false; 		
	
	l = line(p[2],p[3]);
	if (((l*p[1]) * (l*p[0])) != 1)
		return false;		
		
	l = line(p[0],p[3]);
	if (((l*p[2]) * (l*p[1])) != 1)
		return false;
	return true;
}

bool solve(){
	for (int i=0;i<4;i++)
		scanf("%d %d",&p[i].x,&p[i].y);	
	if (check())
		return true;
	swap(p[1],p[2]);
	if (check())
		return true;
	swap(p[1],p[2]);
	swap(p[2],p[3]);
	if (check())
		return true;
	return false;
}

int main()
{
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int t;
	scanf("%d",&t);
	for (;t;--t){
		bool q=solve();
		printf("%c\n","NY"[q]);
	}
    return 0;
}