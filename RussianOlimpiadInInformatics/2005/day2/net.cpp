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

struct square{
	int u,d,l,r;
	square(){
		u=d=l=r=-1;
	}
};

square pl[100][100];

bool t[1<<25];

int xmask[100];

int g[100];


int main()
{
    freopen("net.in","r",stdin);
    freopen("net.out","w",stdout);
  	int n;
  	scanf("%d",&n);
  	for (int i=0;i<n;i++){
  		int x,x1,y,y1;
  		scanf("%d %d %d %d",&x,&y,&x1,&y1);
  		x+=5,y+=5,x1+=5,y1+=5;
  		if (x>x1)
  			swap(x,x1);
  		if (y>y1)
  			swap(y,y1);
  		if (x == x1)
  			pl[x][y].l = pl[x-1][y].r = i;
  		else
  			pl[x][y].d = pl[x][y-1].u = i;
  	}
  	
  	int cnt = 0;
  	
  	for (int i=0;i<100;i++)
  		for (int j=0;j<100;j++)
  			if (pl[i][j].u!=-1 && pl[i][j].d!=-1 && pl[i][j].l!=-1 && pl[i][j].r!=-1){
  				xmask[pl[i][j].u] |= (1<<cnt);
				xmask[pl[i][j].d] |= (1<<cnt);
				xmask[pl[i][j].r] |= (1<<cnt);				
				xmask[pl[i][j].l] |= (1<<cnt);  				  				
				++cnt;
  			}
  			
  	int good = 0;
  	for (int i=0;i<n;i++)
  		if (xmask[i])
			g[good++]=i;

  	for (int i=0;i<(1<<cnt);i++){
  		for (int j=0;j<good;j++)
  			if ((i & xmask[g[j]]))
  				if (!t[i & (~xmask[g[j]])]){
  					t[i]=true;
  					break;
  				}
  	}	
  	
  	if (t[(1<<cnt)-1] == false)
  		printf("2\n");
  	else {
  		printf("1\n");
  		for (int j=0;j<good;j++)
			if (!t[((1<<cnt)-1) & (~xmask[g[j]])]){
				printf("%d",g[j]+1);
				break;
  			}
  	}
	return 0;
}