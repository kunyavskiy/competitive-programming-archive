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

ll f[50];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int n;
  	cin >> n;
  	f[1] = 2;
  	f[0] = 1;
  	for (int i = 2; i <= n; i++)
  		f[i] = f[i-1] + f[i-2];
  	int k;
  	cin >> k;

  	if (k > f[n]){
  		printf("-1\n");
  		return 0;
  	}

  	for (int i = 0; i < n; n--)
  		if (k <= f[n-1])
  			printf("0");
  		else {
  			k -= f[n-1];
  			printf("1");
  			if (n != 1){
  				printf("0");
	  			n--;
	  		}
  		}
  	printf("\n");
  return 0;
}