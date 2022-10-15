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

int a[1100000];
int b[1100000];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int n;
  	scanf("%d",&n);
  	for (int i = 1 ; i <= n; i++)
  		scanf("%d %d",&a[i],&b[i]);

  	for (int i = n; i>= 1; i--)
  		a[i] += b[i],a[i-1] += a[i]/10,a[i]%=10;

  	for (int j = !a[0]; j <= n; j++)
  		printf("%d",a[j]);
  	printf("\n");

  return 0;
}