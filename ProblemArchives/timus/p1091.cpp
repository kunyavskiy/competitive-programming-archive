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

ll c[100][100];

ll ans[100];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int k,s;
  	cin >> k >> s;
  	for (int i = 0; i <= s; i++)
  		for (int j = 0; j <= s;j++){
  			if (j == 0)
  				c[i][j] = 1;
  			else if (i == 0)
  				c[i][j] = 0;
  			else
  				c[i][j] = c[i-1][j] + c[i-1][j-1];
  		}

  	for (int i = s; i >= 1; i--){
  		ans[i] = c[s/i][k];
  		for (int j = i+1; j <= s; j++)
  			if (j % i == 0)
	  			ans[i] -= ans[j];
	}

//	for (int i = 1; i <= s; i++)
//		cerr << ans[i] << endl;

	cout << min(10000LL,c[s][k]-ans[1]) << endl;

  return 0;
}