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

int ans[10000010];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int n,p;
  	cin >> n >> p;
  	ans[2] = 1%p;
  	for (int i = 3; i <= n; i++){
  		ans[i] = ans[i-1];
  		if ((i & 1) == 0){
  			ans[i] += ans[i>>1];
  			if (ans[i] >= p)
  				ans[i] -= p;
  		}
  	}

  	cout << ans[n] << endl;

  return 0;
}