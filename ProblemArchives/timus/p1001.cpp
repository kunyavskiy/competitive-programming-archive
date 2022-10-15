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
#define ld double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

ld ans[300000];

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int64 tmp;
  int n=0;
  for (;cin>>tmp;n++){
  	ans[n]=sqrt(tmp*1.0);
  }
  cout.precision(6);
  for (int i=n-1;i>=0;i--)
  	cout<<fixed<<ans[i]<<"\n";
  return 0;
}