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
#define pb push_back
using namespace std;

const int dx[5]={0,-1,1,0,0};
const int dy[5]={0,0,0,1,-1};
const int INF=1<<27;
int tec[510][510];
int lf[510][510];
int lp[510][510];
int pf[510][510];
int n,m;
int ans;

bool good(int x,int y){
	return x>=0 && y>=0 && x<n && y<m;
}

void calcboat(){
	int x,y;
	scanf("%d %d",&y,&x);
	--x,--y;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			lf[i][j]=lp[i][j]=INF;
	lf[x][y]=0;
	for (int t=12;;t+=12){		
		int T=tec[x][y];
		x+=dx[T];
		y+=dy[T];
		if (!good(x,y))
			break;
		if (lp[x][y]!=INF)
			break;
		if (lf[x][y]!=INF){
			lp[x][y]=t-lf[x][y];
			if (lp[x][y]==12)
				lp[x][y]=0;			
		}
		else
			lf[x][y]=t;
	}
}

void calcpit(){
	int x,y;
	scanf("%d %d",&y,&x);
	--x,--y;
	for (int i=0;i<n;i++)	
		for (int j=0;j<m;j++)
			pf[i][j]=INF;
	queue<int> qx,qy;
	qx.push(x);
	qy.push(y);
	pf[x][y]=0;
	for (;!qx.empty();){
		int x=qx.front();qx.pop();
		int y=qy.front();qy.pop();
		int dst=pf[x][y];
		for (int i=1;i<5;i++){
			int nx=x+dx[i];
			int ny=y+dy[i];
			int speed=1;
			if (tec[x][y]==i)
				speed=2;
			else{
				nx+=dx[tec[x][y]];
				ny+=dy[tec[x][y]];
			}				
			if (!good(nx,ny)){
				ans=min(ans,dst+6/speed);				
			}
			else {
				if (pf[nx][ny] > dst+12/speed){					
					pf[nx][ny]=dst+12/speed;
					qx.push(nx);
					qy.push(ny);
				}
			}
		}
	}
}

int getafter(int t,int f,int p){
	if (p==0)
		return max(t,f);
	if (t<=f)
		return f;
	f+=((t-f)/p)*p;
	if (t==f)
		return f;
	return f+p;
}  



int main()
{
    ans=INF;                 
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d %d",&n,&m);
    for (int i=0;i<n;i++)
    	for (int j=0;j<m;j++){
    		char c;
    		scanf(" %c ",&c);
    		tec[i][j]=c-'0';
    	}    
    calcpit();
	calcboat();
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++){
			ans=min(ans,getafter(pf[i][j],lf[i][j],lp[i][j]));
			int tec=::tec[i][j];
			if (tec==0){
				for (int I=1;I<5;I++){
					int nx=i+dx[I];
					int ny=j+dy[I];
					if (!good(nx,ny))
						continue;
					if (nx+dx[::tec[nx][ny]]!=i || ny+dy[::tec[nx][ny]]!=j)
						continue;			
					int tmp=getafter(pf[i][j],lf[nx][ny],lp[nx][ny]);
					ans=min(ans,tmp+12/2);
					tmp=getafter(pf[i][j]-6,lf[nx][ny],lp[nx][ny]);
					ans=min(ans,tmp+6/2+6);					
				}					
			}
			int nx=i+dx[tec];
			int ny=j+dy[tec];			
			if (!good(nx,ny))
				continue;
			if (nx+dx[::tec[nx][ny]]!=i || ny+dy[::tec[nx][ny]]!=j)
				continue;			
			int tmp=getafter(pf[i][j],lf[nx][ny],lp[nx][ny]);
			ans=min(ans,tmp+12/3);
			tmp=getafter(pf[i][j]-6,lf[nx][ny],lp[nx][ny]);
			ans=min(ans,tmp+6/3+6);
		}
	if (ans==INF)
  	 	cout<<"SOS"<<endl;
	else{
	  	cout.precision(2);
  		cout<<fixed<<ans/12.0<<endl;
	}	
  return 0;
}