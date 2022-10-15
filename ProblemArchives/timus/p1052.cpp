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

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int x[210];
int y[210];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int n;
  	scanf("%d",&n);

  	for (int i = 0; i < n; i++)
  		scanf("%d %d",&x[i],&y[i]);

  	int ans = 2;

  	for (int i = 0; i < n; i++)
  		for (int j = i+1; j < n; j++){
  			int cur = 0;
  			for (int k = 0; k < n; k++)
  				cur += !((x[k]-x[i])*(y[j]-y[i]) - (y[k]-y[i])*(x[j]-x[i]));
  			ans = max(ans,cur);
  		}

  	cout << ans << endl;


  return 0;
}