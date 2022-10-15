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

int dx[4]={0,-1,0,1};
int dy[4]={1,0,-1,0};
int gnap[6][4]={          
								{2,1,4,3},
								{1,5,1,0},
								{5,2,0,2},
								{3,0,3,5},
								{0,4,5,4},
								{4,3,2,1},
							 };
						 
bool g[10][10][4];

int d[10][10][6];
int xsz,ysz;

bool check(int x,int y){
	return x>=0 && x<xsz && y>=0 && y<ysz;
}

const int inf=1<<25;

void bfs(int x,int y){

	for (int i=0;i<10;i++)
		for (int j=0;j<10;j++)
			for (int k=0;k<6;k++)
				d[i][j][k]=inf;

	queue<int> qx;
	queue<int> qy;
	queue<int> qnap;
	qx.push(x);
	qy.push(y);
	qnap.push(0);
	d[x][y][0]=0;
	for (;!qx.empty();){
		int tx=qx.front();qx.pop();
		int ty=qy.front();qy.pop();
		int tnap=qnap.front();qnap.pop();
//		cerr<<tx<<" "<<ty<<" "<<tnap<<":"<<d[tx][ty][tnap]<<endl;
		
		for (int i=0;i<4;i++)
		if (g[tx][ty][i])
		{
			int nx=tx+dx[i];
			int ny=ty+dy[i];
			int nnap=gnap[tnap][i];
			if (!check(nx,ny))
				continue;
			if (d[nx][ny][nnap]>d[tx][ty][tnap]+1){
				d[nx][ny][nnap]=d[tx][ty][tnap]+1;
				qx.push(nx);
				qy.push(ny);
				qnap.push(nnap);
			}
		}		
	}
}
					

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  
  cin>>xsz>>ysz;
  int fx,fy,ex,ey;
  scanf("%d %d %d %d\n",&fx,&fy,&ex,&ey);
  
  --fx;--fy;--ex;--ey;
  
	char s[100];
	memset(g,1,sizeof(g));
	
	
	for (;;){	
		s[0]=0;
		gets(s);
		if (s[0]=='h' || s[0]==0)
			break;
		if (s[0]=='v')
			continue;
		int a,b;
		sscanf(s,"%d %d",&a,&b);
		--a,--b;
		g[a][b][3]=0;
		g[a+1][b][1]=0;
	}
	
	
  for (;;){	
		s[0]=0;
		gets(s);
		if (s[0]==0)
			break;
		int a,b;
		sscanf(s,"%d %d",&a,&b);
		--a,--b;
		g[a][b][0]=0;
		g[a][b+1][2]=0;
	}
	

	bfs(fx,fy);
	if (d[ex][ey][0]==inf)
		printf("No solution\n");
	else
		printf("%d\n",d[ex][ey][0]);
	
  return 0;
}
