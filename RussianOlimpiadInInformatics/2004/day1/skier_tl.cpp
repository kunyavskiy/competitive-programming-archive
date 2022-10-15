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
typedef double ld;

#undef min
int min(int a,int b){
	return (a<b)?a:b;
}

struct point{
	int x,y;	
	point(int x,int y):x(x),y(y){
	}
	point(){};
	ld dest(const point& p){
		return sqrt((p.x-x)*(p.x-x)+(p.y-y)*(p.y-y));
	}
};

struct segment{
	int x1,x2,y;
	ld cost;
	segment(){}
	void load(){
		scanf("%d %d %d %lf",&x1,&x2,&y,&cost);
	}
};

int sign(int x){
	if (x > 0)
		return 1;
	if (x == 0)
		return 0;
	return -1;
}

struct line{
	int a,b,c;
	line(const point& p1,const point& p2){
		a = p1.y - p2.y;
		b = p2.x - p1.x;
		c = -a*p1.x -b*p1.y;
	}
	int side(const point& p){
		return sign(p.x*a+p.y*b+c);
	}
	bool intersec(const segment& s){
		return side(point(s.x1,s.y))*side(point(s.x2,s.y)) <= 0;
	}
};

ld t[1100];
point p[1100];
segment s[1100];
int n;

ld calc(int a,int b){
	ld ans = 0;
	line l(p[a],p[b]);
	for (int i=0;i<n;i++)
		if (p[a].y <= s[i].y && s[i].y < p[b].y && l.intersec(s[i]))
			ans += s[i].cost;
	return ans;
}

void calc(int num){
	t[num] = 1e100;
	for (int i=0;i<num;i++){
		if (p[i].y > p[num].y)
			t[num] = min(t[num],-calc(num,i)+t[i]+p[num].dest(p[i]));		
	}
}

bool cmp(const point& a,const point& b){
	return a.y > b.y;
}


int main()
{
	freopen("skier.in","r",stdin);
	freopen("skier.out","w",stdout);
	scanf("%d",&n);
	scanf("%d %d",&p[0].x,&p[0].y);
	scanf("%d %d",&p[1].x,&p[1].y);
	t[0] = 0;
	for (int i=0;i<n;i++){
		s[i].load();
		p[2*i+2]=point(s[i].x1,s[i].y);
		p[2*i+3]=point(s[i].x2,s[i].y);
		t[0] += s[i].cost;
	}
	sort(p,p+2*n+2,cmp);
	for (int i=1;i<(2*n+2);i++){
		calc(i);
	//	cerr<<t[i]<<endl;
	}
	cout.precision(15);
	cout<<fixed<<t[2*n+1]<<endl;
	return 0;
}