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
#define filename "candies"
using namespace std;

bool a[110][70100];

int b[110];

int main()
{
  freopen(filename".in","r",stdin);
  freopen(filename".out","w",stdout);
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d",&b[i]);
	int ans=-1,anskol=-1;
	for (int i=0;i<n;i++){
		memset(a,0,sizeof(a));
		a[0][0]=1;
		if (i!=0)
			a[0][b[0]]=1;
		int sum=b[0]*(i!=0);
		for (int j=1;j<n;j++){
			if (j!=i)
				sum+=b[i];
			for (int k=0;k<=sum;k++)
				{
					a[j][k]=a[j-1][k];
					if (k>=b[j] && j!=i)
						a[j][k]|=a[j-1][k-b[j]];
				}				
		}
		int kol=0;
		for (int j=0;j<=sum;j++)
			if (a[n-1][j])
				kol++;
		if (ans==-1 || kol>anskol || kol==anskol && b[ans]>b[i])
			{
				ans=i;
				anskol=kol;
			}
	}
	memset(a,0,sizeof(a));
	swap(b[n-1],b[ans]);
	--n;
	a[0][0]=a[0][b[0]]=1;
	int sum=b[0];
  for (int i=1;i<n;i++)
  	{
  		sum+=b[i];
  		for (int j=0;j<=sum;++j){
  			a[i][j]=(a[i-1][j] | a[i-1][j+b[i]] | a[i-1][abs(j-b[i])]);
  		}
  	} 
  for (int i=0;;i++)
  	if (!a[n-1][i])
  		{
  			printf("%d %d\n",b[n],i);
  			return 0;
  		}
  return 0;
}