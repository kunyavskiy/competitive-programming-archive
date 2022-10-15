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

int a[17000];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int n;
  	scanf("%d",&n);
  	for (int i = 0; i < n; i++)
  		scanf("%d",&a[i]);
  	int m,ans;
  	ans = 0;
  	scanf("%d",&m);
  	int b;
  	for (int i = 0; i < m; i++){
  	    scanf("%d",&b);
  		ans += binary_search(a,a+n,b);
  	}
  	cout << ans << endl;
  return 0;
}