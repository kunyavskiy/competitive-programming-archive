#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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
#define setval(a,v) memset(a,v,sizeof(a))

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif


#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int x[110000];
int y[110000];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int n;
  scanf("%d",&n);
  for (int i = 0; i < n; i++)
  	scanf("%d %d",&x[i],&y[i]);
  sort(x,x+n);
  sort(y,y+n);

  ll ans = 0;
  ll sum = 0;

  for (int i = 0; i < n; i++){
  	ans += x[i]*1LL*i - sum;
  	sum += x[i];
  }


  sum = 0;

  for (int i = 0; i < n; i++){
  	ans += y[i]*1LL*i - sum;
  	sum += y[i];
  }

  cout << ans / (n*1LL*(n-1)/2) << endl;

	
  return 0;
}