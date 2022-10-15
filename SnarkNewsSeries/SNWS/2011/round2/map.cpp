#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "map"

using namespace std;

typedef long long int64;
typedef long double ld;

const int dx[4]={0,1,0,-1};
const int dy[4]={1,0,-1,0};
const char name[4]={'E','S','W','N'};



int d[110][110];
int power[110][110];
int nap[110][110];

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
	int n,m;
	scanf("%d %d",&m,&n);
	int x0,y0;
	scanf("%d %d",&y0,&x0);
	--x0;--y0;
	int t;
	scanf("%d",&t);
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++){
			char c1,c2;
			scanf(" %c %c ",&c1,&c2);
			power[i][j]=c1-'0';
			for (int k=0;k<4;k++)
				if (c2==name[k])
					nap[i][j]=k;
		}
	queue<int> qx,qy;
	qx.push(x0);
	qy.push(y0);
	memset(d,-1,sizeof(d));
	d[x0][y0]=0;
//	cerr<<qx.front()<<" "<<qy.front()<<endl;
	for (;!qx.empty();){
		int x=qx.front();qx.pop();
		int y=qy.front();qy.pop();
		if (d[x][y] >= t) continue;
		for (int i=1;i<=power[x][y];i++){
			int nx=x+dx[nap[x][y]]*i;
			int ny=y+dy[nap[x][y]]*i;
			if (nx<0 || ny<0 || nx>=n || ny>=m)
				continue;
			if (d[nx][ny]==-1){
				d[nx][ny]=d[x][y]+1;
				qx.push(nx);
				qy.push(ny);
			}
		}
	}
	for (int i=0;i<n;i++){
		for (int j=0;j<m;j++)
			printf("%c",".X"[d[i][j]!=-1]);
		printf("\n");
	}
	return 0;
} 