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

int lf[1000];
int rg[1000];

int main()
{
  //freopen("input.txt","r",stdin);
  //freopen("output.txt","w",stdout);
  int t;
  cin>>t;
  for (int test=1;test<=t;++test){
 	  int n;
	  scanf("%d",&n);
	  for (int i=0;i<n;i++)
  	scanf("%d %d",&lf[i],&rg[i]);
  	int ans=0;
	  for (int i=0;i<n;i++)
  		for (int j=i+1;j<n;j++)
	  		if ((lf[i]<lf[j]) ^ (rg[i]<rg[j]))
	  			ans++;
	  printf("Case #%d: %d\n",test,ans);
	}
  return 0;
}