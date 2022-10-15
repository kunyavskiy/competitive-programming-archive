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

bool xy[1024][1024];
int64 xz[1024][20];
int64 yz[1024][20];

int n;

int64 x6[1024];
int64 x63[1024];

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
	scanf("%d",&n);
	
	int maxn=(n/64+(!!(n%64)))*64;
	
	for (int i=0;i<1024;i++)
	{
		x6[i]=(i>>6);
		x63[i]=(1ll<<(i&63));
	}

	
	for (int i=0;i<n;i++)
		for (int j=n;j<maxn;j++)
			{
				xz[i][x6[j]]|=x63[j];
				yz[i][x6[j]]|=x63[j];
			}

	int k;
	scanf("%d",&k);
	for (int i=0;i<k;i++){
		int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		--x,--y,--z;
		xy[x][y]=1;
		xz[x][x6[z]]|=x63[z];
		yz[y][x6[z]]|=x63[z];
	}
	
	int maxn64=maxn/64;
	for (int i=0;i<n;i++)
		for (int j=0;j<maxn64;j++)
			{
				xz[i][j]=~xz[i][j];
				yz[i][j]=~yz[i][j];
			}
		
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (!xy[i][j])
				for (int k=0;k<maxn64;k++)
					if ((xz[i][k] & yz[j][k])!=0)
						{
							printf("NO\n");
							int64 tmp=xz[i][k] & yz[j][k];
							for (int b=0;b<64;b++)
								if ((1ll<<b) & tmp) 
								{
									printf("%d %d %d",i+1,j+1,k*64+b+1);
									return 0;
								}
						}
	printf("YES\n");	
  return 0;
}