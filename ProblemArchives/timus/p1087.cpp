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

int res[11000];
int k[100],m,n;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	scanf("%d",&n);
  	scanf("%d",&m);
  	for (int i = 0; i < m; i++)
  		scanf("%d",&k[i]);

  	res[0] = 1;
  	for (int i = 1; i <= n; i++){
		for (int j = 0; j < m; j++)
			if (k[j] <= i)
				res[i] = max(res[i],1-res[i-k[j]]);
//		cerr << i<<" "<<res[i] << endl;
	}
	cout << (!res[n])+1 << endl;
  return 0;
}