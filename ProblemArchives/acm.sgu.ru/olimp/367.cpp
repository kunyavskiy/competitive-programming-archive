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

int n;

int cnt(int x,int y)
{
	int n=::n;
	int al=min(min(x-1,n-y),y-x);
	int alc=3*n*al+6*al-9*(al*(al+1)/2);
	x-=al;
	y-=2*al;
	n-=3*al;
	if (((x!=1) && (y!=n)) || ((x==1) && (y==1)))
	{
		alc+=x;
		return alc;
	}
	alc+=n-1;
  if (y==n)
	{
		alc+=n-x+1;
		return alc;
	}
	alc+=n-1;
	alc+=n-y+1;
	return alc;
}

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  cin>>n;
  for (int i=1;i<=n;i++)
  {
  	for (int j=1;j<=i;j++)
  		printf("%d ",cnt(j,i));
  	printf("\n");
  }
  return 0;
}