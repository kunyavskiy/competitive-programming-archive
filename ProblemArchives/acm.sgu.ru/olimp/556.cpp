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

int a[30000],b[30000];

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  int n;
  scanf("%d",&n);
  for (int i=0;i<n;i++)
  	scanf("%d",&b[i]);
  for (int i=0;i<n;i++)
  	scanf("%d",&a[i]);
  int sum=0;
  for (int i=0;i<n;i++)
  {
  	sum+=a[i];
  	b[i]-=a[i];
  }
  int ls=0;
  int s=0;
  int ms=0;
  for (int i=0;i<n;i++)
  {
  	s+=b[i];
  	ls=max(ls,s);
  	ms=min(ms,s-ls);
  }
  sum+=ms;
  printf("%d",sum);
  return 0;
}