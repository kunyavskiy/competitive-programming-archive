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
	int num,pnum;
	point(int x,int y,int num,int pnum):x(x),y(y),num(num),pnum(pnum){
	}
	point(int x,int y):x(x),y(y){
	}
	point(){};
	ld dest(){
		return sqrt(x*x+y*y+0.0);
	}
};

struct segment{
	int x1,x2,y;
	int cost;
	segment(){}
	void load(){
		scanf("%d %d %d %d",&x1,&x2,&y,&cost);
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


namespace dp{
	const int MAXC=21000;
	int fen[MAXC];
	
	point p[1100];
	int cnt;
	int add;
	
	bool cmp(const point& a,const point& b){
		return a.x*b.y - b.x*a.y > 0;
	}
	
	bool eql(const point& a,const point& b){
		return a.x*b.y - b.x*a.y == 0;
	}
	
	int get(int r){
		r+=add;
		int ans = 0;
		for (;r!=-1;r=(r&(r+1))-1)
			ans += fen[r];
		return ans;
	}
	
	int get(int l,int r){
		return get(r)-get(l-1);
	}
	
	void update(int l,int x){
		l+=add;
		for (;l<MAXC;l=l|(l+1))
			fen[l]+=x;
	}
	
	bool use[1100];
	
	void init(int num){
		cnt = 0;
		memset(fen,0,sizeof(fen));
		for (int i=0;i<num;i++)
			if (::p[i].y > ::p[num].y)
				p[cnt++] = point(::p[i].x-::p[num].x,::p[i].y-::p[num].y,::p[i].num,::p[i].pnum);
		memset(use,0,sizeof(use));	
		add = ::p[num].y+10500;	
		update(0,s[::p[num].num].cost);		
		sort(p,p+cnt,cmp);
	}
	
	void calc(int num){
		t[num] = 1e100;
		init(num);
		for (int i=0;i<cnt;){
			int j = i;
			for (;j<cnt && eql(p[i],p[j]);j++);
			for (int k=i;k<j;k++)
				if (!use[p[k].num])
					update(p[k].y,s[p[k].num].cost);
			for (int k=i;k<j;k++)
				t[num] = min(t[num],t[p[k].pnum]-get(0,p[k].y-1)+p[k].dest());
			for (int k=i;k<j;k++)
				if (use[p[k].num])
					update(p[k].y,-s[p[k].num].cost);
			for (int k=i;k<j;k++)
				use[p[k].num]^=1;
			i=j;
		}
	}

}





bool cmpy(const point& a,const point& b){
	return a.y > b.y;
}


int main()
{
	freopen("skier.in","r",stdin);
	freopen("skier.out","w",stdout);
	scanf("%d",&n);
	scanf("%d %d",&p[0].x,&p[0].y);
	scanf("%d %d",&p[1].x,&p[1].y);
	p[0].num=p[1].num = n;
	s[n].cost = 0;
	t[0] = 0;
	for (int i=0;i<n;i++){
		s[i].load();
		p[2*i+2]=point(s[i].x1,s[i].y,i,-1);
		p[2*i+3]=point(s[i].x2,s[i].y,i,-1);
		t[0] += s[i].cost;
	}
	sort(p,p+2*n+2,cmpy);
	
	for (int i=0;i<(2*n+2);i++)
		p[i].pnum = i;
	
	for (int i=1;i<(2*n+2);i++)
		dp::calc(i);	
	cout.precision(15);
	cout<<fixed<<t[2*n+1]<<endl;
	return 0;
}