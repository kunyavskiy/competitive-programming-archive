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

bool used[250];

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  int n,m,k;
  scanf("%d %d %d",&n,&k,&m);
  setval(used,true);
  for (int i=0;i<m;i++)
  {
  	int a;
  	cin>>a;
  	used[--a]=false;
  }
  int kol=0;
  for (int i=0;i<n;i++)
  {
  	if (used[i])
  		kol++;
  	else
  		kol=0;
  	if (kol==k)
  	{
  		printf("%d",i-k+2);
  		return 0;
  	}
  }
  printf("No solution\n");
  return 0;
}