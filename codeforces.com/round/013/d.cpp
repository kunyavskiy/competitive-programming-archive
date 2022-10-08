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
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

struct point{
	int64 x,y;
	int num;
	point (int64 a=0,int64 b=0,int n=0){
		x=a;
		y=b;
		num=n;
	}
};

point operator-(point a,point b){
	return point(a.x-b.x,a.y-b.y);
}

int64 operator*(point a,point b){
	return a.x*b.y-a.y*b.x;
}

struct point_cmp{
	point cent;
	point_cmp(point c){
		cent=c;
	}
	bool operator()(const point& a,const point & b){
		return (a-cent)*(b-cent)>0;
	}
};

point p[1000];
int n,m,n0;

void find_ld(){
	for (int i=1;i<n+m;i++)
		if (p[0].y>p[i].y || (p[0].y==p[i].y && p[0].x>p[i].x))
			swap(p[0],p[i]);
};

int64 res;

void use(){
	if (p[0].num>=n0){
		swap(p[0],p[n+m-1]);
		--m;
		return;
	}
	sort(p+1,p+n+m,point_cmp(p[0]));
	for (int i=1;i<n+m;i++){
			if (p[i].num>=n0)
				continue;
			point mlast(-100,-100);
			for (int j=i+1;j<n+m;j++){
				if (p[j].num>=n0){
					if (mlast.y==-100 || ((mlast-p[i])*(p[j]-p[i])>0))
						mlast=p[j];
				}
				else{
				/*	cerr<<i<<" "<<j<<endl;
					cerr<<mlast.x<<" "<<mlast.y<<endl;
					cerr<<(mlast-p[i]).x<<" "<<(mlast-p[i]).y<<endl;
					cerr<<(p[j]-p[i]).x<<" "<<(p[j]-p[i]).y<<endl;
					cerr<<(mlast-p[i])*(p[j]-p[i])<<endl<<endl;*/
					if (mlast.y==-100 || ((mlast-p[i])*(p[j]-p[i])>0))
						res++;
				}
			}
	}
	swap(p[0],p[n+m-1]);
	--n;			
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	scanf("%d %d",&n,&m);
	n0=n;
	for (int i=0;i<n+m;i++)
		{
			cin>>p[i].x>>p[i].y;
			p[i].num=i;
		}
	res=0;
	for (;n>0;)
		{
			find_ld();
			use();
		}
	cout<<res<<endl;
  return 0;
}