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

int median(int a,int b,int c)
{
	int m1=min(min(a,b),c);
	int m2=max(max(a,b),c);
	return a+b+c-m1-m2;
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int a[3][3];
  for (int i=0;i<3;i++)
  	for (int j=0;j<3;j++)
  		cin>>a[i][j];
  int res[3];
  for (int i=0;i<3;i++)
  	res[i]=median(a[i][0],a[i][1],a[i][2]);
  cout<<median(res[0],res[1],res[2]);
  return 0;
}