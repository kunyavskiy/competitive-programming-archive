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

const int dx[4]={1,0,-1,0};
const int dy[4]={0,-1,0,1};
const int xr[2]={3,1};

int type[1111][1111];

int timea[1111][1111][4];
int timeb[1111][1111][4];
int n,m;

void model(int x,int y,int side,typeof(timea) res){
	int time = 0;
	while (true){
		if (x < 0 || y<0 || x>=n || y>=m)
			break;
		res[x][y][side] = time;
		++time;
		if (type[x][y] != -1)
			side ^= xr[type[x][y]];
		x+=dx[side];
		y+=dy[side];
	}
}

int main()
{
 //   freopen("pinball.in","r",stdin);
//    freopen("pinball.out","w",stdout);
    int k;
	int xa,ya,ta,xb,yb,tb;
	cin>>n>>m>>k;
	--k;
	cin>>xa>>ya>>ta>>xb>>yb>>tb;
	--xa,--ya,--xb,--yb;
	--ta,--tb;
	memset(type,-1,sizeof(type));
	for (int i=0;i<k;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		--x,--y;
		scanf("%d",&type[x][y]);
		--type[x][y];
	}
	memset(timea,-1,sizeof(timea));
	memset(timeb,-1,sizeof(timeb));
	model(xa,ya,ta,timea);
	model(xb,yb,tb,timeb);
	int bestx,besty,bestnap;
	int best;
	best = bestx = besty = bestnap = -1;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++){
			if (type[i][j]!=-1) continue;
//			cerr<<"!!!"<<endl;
			for (int s=0;s<4;s++)
				for (int t=0;t<2;t++){
					if (timea[i][j][s]!=-1 && timeb[i][j][s^xr[t]]!= -1){

						if (timea[i][j][s] + timeb[i][j][s^xr[t]] < best || best == -1){
							best = timea[i][j][s] + timeb[i][j][s^xr[t]];
							bestx = i;
							besty = j;
							bestnap = 1-t;
						}
					}
				}
			
		}
	if (bestx == -1){
		for (int i=0;i<n;i++)
			for (int j=0;j<m;j++)
				if (type[i][j] == -1){
					bool q = true;
					for (int k=0;k<4;k++)
						if (timea[i][j][k] != -1)
							q=false;
					for (int k=0;k<4;k++)
						if (timeb[i][j][k] != -1)						
							q=false;
					if (q){
						bestx = i;
						besty = j;
						bestnap = 0;
					}
				}
	}
	cout << bestx+1 << " "<<besty+1 << " "<<bestnap+1 << endl;	
    return 0;
}