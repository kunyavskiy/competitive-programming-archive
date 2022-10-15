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

int pr[30000];
int a[30000];
int n;

bool perebor(int st)
{            
	int l1=-1,l2=-1,d1=-1,d2=-1;
	for (int i=0;i<st;i++)
		if (pr[i]==1)
		{	
			if (l1==-1)
				l1=i;
			else
			{
				d1=a[i]-a[l1];
				l1=i;
			}
		}
		else
			{
				if (l2==-1)
					l2=i;
				else
					{
						d2=a[i]-a[l2];
						l2=i;
					}
			} 
	for (int i=st;i<n;i++)
	{
		if (d2!=-1)
			if ((a[l1]+d1==a[i]) && (a[l2]+d2==a[i]))
			{
				pr[i]=1;
				if (perebor(i+1))
					return true;
				pr[i]=2;     
				return perebor(i+1);
			}				
		if (a[l1]+d1==a[i])
			pr[l1=i]=1;
		else if (l2==-1)
					pr[l2=i]=2;
		else if (d2==-1){
					d2=a[i]-a[l2];
					pr[l2=i]=2;   
		}
		else if (a[l2]+d2==a[i])
			pr[l2=i]=2;
		else
			return false;
	}
	if (l2==-1)
		pr[n-1]=2;
	return true;
}

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  scanf("%d",&n);
  for (int i=0;i<n;i++)
  	scanf("%d",&a[i]);
  pr[0]=pr[1]=1;
  if (perebor(2))
  {
  	for (int i=0;i<n;i++)
  		if (pr[i]==1)
  			printf("%d ",a[i]);
  	printf("\n");
  	for (int i=0;i<n;i++)
  		if (pr[i]==2)
  			printf("%d ",a[i]);
  	printf("\n");
  	return 0;
  }
  pr[0]=pr[2]=1;
  pr[1]=2;
  if (perebor(3))
  {
  	for (int i=0;i<n;i++)
  		if (pr[i]==1)
  			printf("%d ",a[i]);
  	printf("\n");
  	for (int i=0;i<n;i++)
  		if (pr[i]==2)
  			printf("%d ",a[i]);
  	printf("\n");
  	return 0;
  }
  pr[1]=pr[2]=1;
  pr[0]=2;
  if (perebor(3))
  {
  	for (int i=0;i<n;i++)
  		if (pr[i]==1)
  			printf("%d ",a[i]);
  	printf("\n");
  	for (int i=0;i<n;i++)
  		if (pr[i]==2)
  			printf("%d ",a[i]);
  	printf("\n");
  	return 0;
  }
  printf("No solution\n");
  return 0;
}