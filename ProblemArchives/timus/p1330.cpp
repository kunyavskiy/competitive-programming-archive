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

int a[110000];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int n;
  	scanf("%d",&n);
  	for (int i = 0; i < n; i++){
  		scanf("%d",&a[i]);
  		if (i) a[i] += a[i-1];
  	}

  	int q;
  	scanf("%d",&q);

  	for (int i = 0; i < q; i++){
  		int a,b;
  		scanf("%d %d",&a,&b);
  		--a,--b;
  		printf("%d\n", ::a[b] - (a? ::a[a-1]:0));
  	}

  return 0;
}