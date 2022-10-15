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

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int n,m;
  cin>>n>>m;
  int a[3];
  for (int s=0;s<3;s++)
  {
  	a[s]=0;
	  for (int i=0;i<n;i++)
  		for (int j=0;j<m;j++)
  			if ((i+j)%3==s)
  				a[s]++;
  }
  int s;
  if (a[0]<=a[1] && a[0]<=a[2])
  	s=0;
  else if (a[1]<=a[2])
  	s=1;
  else
  	s=2;
  for (int i=0;i<n;i++)
		for (int j=0;j<=m;j++)
			cout<<"\n0#"[(((i+j)%3==s)+1)*(j!=m)];
	return 0;
}