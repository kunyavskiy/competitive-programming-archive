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

int a[111][111];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int n;
  	cin >> n;
  	for (int i = 1; i <= n; i++)
  		for (int j = 1; j <= n; j++)
  			cin >> a[i][j];

  	for (int i = 1; i <= n; i++)
  		for (int j = 1; j <= n; j++)
  			a[i][j] = a[i][j] +  a[i][j-1] + a[i-1][j] - a[i-1][j-1];

  	int bestsum = -(1<<30);

  	for (int i = 1; i <= n; i++)
  		for (int j = i; j <= n; j++)
  			for (int k = 1; k <= n; k++)
  				for (int l = k;l <= n; l++){
  					int cur = a[j][l] - a[i-1][l] - a[j][k-1] + a[i-1][k-1];
  					if (cur > bestsum)
  						bestsum = cur;  				
  				}
 	cout << bestsum << endl;
  return 0;
}