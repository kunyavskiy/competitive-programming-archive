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


const int maxn=1000000;
int a[maxn];

int main()
{
  freopen("dance.in","r",stdin);
  freopen("dance.out","w",stdout);
  int64 res=0;
  int n;
  scanf("%d",&n);
  for (int i=0;i<n;i++){
  	char c;
  	scanf(" %c ",&c);
  	if (c=='a')
  		a[i]=1;
  	else
  		a[i]=-1;  	
  }
  for (int i=0;i<n;i++){
  	int sum=0;
  	for (int j=i;j<n;j++){
  		sum+=a[j];
  		if (sum==0)
  			res++;
  	}
  }
  cout<<res<<endl;
  return 0;
}