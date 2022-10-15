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

int gcd(int a,int b){
	if (b==0)
		return a;
	return gcd(b,a%b);
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int n;
  cin>>n;
  int res=0;
  for (int i=1;i<=n;i++)
  	if (gcd(i,n)==1)
  		res++;
  cout<<res<<endl;
  return 0;
}