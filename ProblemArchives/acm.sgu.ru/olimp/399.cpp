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

int h[20];
int v[100];
int n;                           


int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  scanf("%d",&n);
  for (int i=0;i<n;i++)
  	scanf("%d",&h[i]);
  int l=40;
  int r=40;
  sort(h,h+n);
  v[l]=h[0];
	for (int i=1;i<n;i++)
		if (v[l]<v[r])
			v[--l]=h[i];
		else
			v[++r]=h[i];
	v[--l]=v[r];
	v[++r]=v[l+1];
	int ans=0;
	for (int i=l;i<r;i++)
		ans=max(ans,abs(v[i]-v[i+1]));
 cout<<ans<<endl; 
  return 0;
}