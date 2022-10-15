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

int f[11000];
int g[11000];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int n;
	scanf("%d",&n);


	for (int i = 1; i <= n; i++)
		scanf("%d",&f[i]);

	int obr = 0;
	for (int i = 0; i < 2007; i++)
		if ((i*f[1])%2007 == 1)
			obr = i;
    assert(obr);

    g[1] = obr;
    printf("%d ",g[1]);

    for (int i = 2; i <= n; i++)
    	g[i] = (g[1]*f[i]) % 2007;

	for (int i = 2; i <= n; i++){
		g[i] = (g[i] * obr) % 2007;
		g[i] = (2007-g[i]) % 2007;

		for (int k = 2; k*i <= n; k++)
			g[i*k] = (g[i*k] + f[k]*g[i]) % 2007;
		printf("%d ",g[i]);
	}

	

	

  return 0;
}