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

int64 t[101][1000];
int64 good[101];
int64 rasl[101][102];

int main()
{
	setval(t,0);
	t[0][0]=1;
	int n,k;
	scanf("%d %d",&n,&k);
	if (k==9){
		printf("9");
		for (int i=0;i<n-1;i++)
			printf("0");
		printf("\n");
		return 0;
	}
	for (int i=1;i<=n;i++)
		for (int j=0;j<1000;j++)
			for (int l=1;l<=k;l++)
				if (j>=l)
				{
					t[i][j]+=t[i-1][j-l];
					assert(t[i][j]>=t[i-1][j-l]);					
				}
	for (int i=0;i<=n;i++)
		for (int j=0;j<=i;j++)
			for (int s=0;s<1000;s++)
			{
				int64 tmp=good[i];
				good[i]+=t[j][s]*t[i-j][s];
				assert(tmp<=good[i]);
			}
	setval(rasl,0);
	for (int j=0;j<=n+1;j++)
		rasl[0][j]=1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n+1;j++)
			for (int l=0;l<=i;l++)
				rasl[i][j]+=rasl[i-l][j-1];
	int64 ans=0;	
	for (int i=0;i<=n;i++){
		int64 kol=n-i;
		int64 pos=i+1;
		int64 coef=rasl[kol][pos];
		ans+=good[i]*coef;
	}
	int64 all=1;
	for (int i=0;i<n;i++)
		all*=(k+1);
	cout<<all-ans<<endl;;
	return 0;
}