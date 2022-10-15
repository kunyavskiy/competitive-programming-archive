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

const int dsz=8;
const int maxver=dsz*dsz*dsz*dsz*2+1000;

vector<int> g[maxver];
int d[maxver];
int ans[maxver];

int code(int x,int y,int x1,int y1,int h){
	return (((x*dsz+y)*dsz+x1)*dsz+y1)*2+h;
}

bool good(int x,int y){
	return 0<=x && x<dsz && 0<=y && y<dsz; 
}

void uncode(int c){
	int h,x,y,x1,y1;
	h=c%2;
	c/=2;
	y1=c%dsz;
	c/=dsz;
	x1=c%dsz;
	c/=dsz;
	y=c%dsz;
	c/=dsz;
	x=c%dsz;
	c/=dsz;
	//cerr<<x<<" "<<y<<" "<<x1<<" "<<y1<<" "<<h<<" : ";
}

void gen(int x,int y,int x1,int y1,int h){
	int mn=code(x,y,x1,y1,h);
	if (h==1){
		for (int dx=-1;dx<=1;++dx)
			for (int dy=-1;dy<=1;++dy)
				if (dx*dx+dy*dy>0)
					if (good(x+dx,y+dy))
						g[mn].pb(code(x+dx,y+dy,x1,y1,0));
	}
	else {
		for (int dx=-1;dx<=1;++dx)
			for (int dy=-1;dy<=1;++dy)
				if (dx*dx+dy*dy>0)
					if (good(x1+dx,y1+dy))
						g[mn].pb(code(x,y,x1+dx,y1+dy,1));
	}
	for (int i=0;i<g[mn].size();i++){
		d[g[mn][i]]++;
		if (g[mn][i]==code(1,1,0,0,1))
			{
				uncode(mn);
				//cerr<<endl;
			}
	}
}

void bfs(int end){
	memset(ans,-1,sizeof(ans));
	queue<int> q;
	for (int i=0;i<dsz;i++)
		for (int j=0;j<dsz;j++)
			{
				q.push(code(i,j,i,j,1));
				ans[code(i,j,i,j,1)]=0;
				q.push(code(i,j,i,j,0));
				ans[code(i,j,i,j,0)]=0;
			}
	for (;!q.empty();){
		int v=q.front();
		uncode(v);
		//cerr<<ans[v]<<endl;
		q.pop();
		if (v==end)
			{
				printf("%d\n",ans[v]);
				exit(0);
			}
		for (int i=0;i<g[v].size();i++){
			int to=g[v][i];
			if (v%2==1){
				if (ans[to]==-1){
					ans[to]=ans[v]+1;
					q.push(to);
				}
			}
			else {
				d[to]--;
				//cerr<<"GOTO ";
				uncode(to);
				//cerr<<" "<<d[to]<<endl;
				if (d[to]==0){
					q.push(to);
					ans[to]=ans[v];			
				}
			}
		}
	}
}


int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
	for (int i=0;i<dsz;i++)
		for (int j=0;j<dsz;j++)
			for (int i1=0;i1<dsz;i1++)
				for (int j1=0;j1<dsz;j1++)
					for (int k=0;k<2;k++)
						gen(i,j,i1,j1,k);
	char c1,c2;
	int a,b;
	cin>>c1>>a>>c2>>b;
	int start=code(c1-'a',a-1,c2-'a',b-1,0);
	bfs(start);
	printf("-1\n");
  return 0;
}