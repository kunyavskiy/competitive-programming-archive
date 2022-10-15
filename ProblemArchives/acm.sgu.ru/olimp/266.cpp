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


struct rect{
	int x1,y1,x2,y2;
	rect(){};
	rect(int a,int b,int c,int d){
		x1=min(a,c);
		x2=max(a,c);
		y1=min(b,d);
		y2=max(b,d);
	}
};

rect read(){
	int a,b,c,d;
	scanf("%d %d %d %d",&a,&b,&c,&d);
	return rect(a,b,c,d);
}

int xs[300];
rect r[200];
int n;

const int inf=1<<30;

vector<rect> ans;



void solve(int lf,int rg){
	vector<pair<int,int> > evs;
	for (int i=0;i<n;i++)
		if (r[i].x1 <= lf && rg<=r[i].x2){
			evs.pb(mp(r[i].y1,-1));
			evs.pb(mp(r[i].y2,1));
		}
	sort(evs.begin(),evs.end());
	int last=inf;
	int bal=0;
	for (int i=0;i<evs.size();i++){
		bal-=evs[i].second;
		if (bal == 1)
			last=evs[i].first;		
		else if ((bal == 2 || bal==0) && last != inf){
			if (last != evs[i].first)
				ans.pb(rect(lf,last,rg,evs[i].first));
			last=inf;
		}
	}
}





int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	r[0]=read();
	scanf("%d",&n);
	++n;
	for (int i=1;i<n;i++){
		r[i]=read();
		r[i].x1=max(r[i].x1,r[0].x1);
		r[i].y1=max(r[i].y1,r[0].y1);
		r[i].x2=min(r[i].x2,r[0].x2);
		r[i].y2=min(r[i].y2,r[0].y2);
		if (r[i].x1 >= r[i].x2 || r[i].y1 >= r[i].y2)
			--i,--n;
	}
	int cnt=0;
	for (int i=0;i<n;i++){
		xs[cnt++]=r[i].x1;
		xs[cnt++]=r[i].x2;
	}
	sort(xs,xs+cnt);
	cnt=unique(xs,xs+cnt)-xs;
	for (int i=0;i<cnt-1;i++)
		solve(xs[i],xs[i+1]);
	cout<<ans.size()<<endl;
	for (int i=0;i<ans.size();i++)
		printf("%d %d %d %d\n",ans[i].x1,ans[i].y1,ans[i].x2,ans[i].y2);
    return 0;
}