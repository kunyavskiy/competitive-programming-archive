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
#define y1 botva    


using namespace std;

struct point{
	int x,y,sum;
};

point pts[500];

int n,W;
int ans;

int x1,y1,x2,y2;

bool cmpy(const point& a,const point& b){
	return a.y > b.y;
}

bool cmpx(const point& a,const point& b){
	return a.x < b.x;
}



void solve(int l,int r){
	int Y=pts[l].y;
	sort(pts+l,pts+r+1,cmpx);	
	int sum=0;
	for (int lf=r,rg=r;lf>=l;--lf){
		sum+=pts[lf].sum;
		for (;pts[rg].x > pts[lf].x + ans;--rg)	
			sum-=pts[rg].sum;
		if (sum >= W){
			x1=pts[lf].x;
			x2=pts[lf].x + ans + 1;
			y1=Y;			
			y2=Y - ans - 1;
		}		
	}	
	sort(pts+l,pts+r+1,cmpy);
}

void solve(){
	x1=y1=x2=y2=-100000;		
	int lf=n-1;
	int rg=n-1;
	for (;lf>=0;--lf){
		for (;pts[rg].y < pts[lf].y - ans;--rg);
		solve(lf,rg);
	}
}

int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	scanf("%d %d",&n,&W);
	for (int i=0;i<n;i++)
		scanf("%d %d %d",&pts[i].x,&pts[i].y,&pts[i].sum);
	sort(pts,pts+n,cmpy);
	int l=-1;
	int r=11000;
	ans=r;
	solve();
	if (x1 < 0){
		printf("NO SOLUTION\n");
		return 0;
	}
	for (;r-l>1;){	
		ans=(l+r)/2;
		solve();
		if (x1 < 0)
			l=ans;
		else
			r=ans;
	}
	ans=r;
	solve();
	cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
    return 0;
}