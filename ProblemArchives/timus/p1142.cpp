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

ll ans[100][100];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	
  	ans[0][0] = 1;

  	for (int i = 0; i < 10; i++)
  		for (int j = 0; j <= i; j++){
  			ans[i+1][j] += j * ans[i][j];
  			ans[i+1][j+1] += (j+1)*ans[i][j];
  		}

  	int n;
  	for (;cin>>n;){
  		if (n == -1)
  		   break;
  		ll res = 0;
  		for (int i = 0; i <= 10; i++)
  			res += ans[n][i];
  		cout << res << endl;
  			
  	}


  return 0;
}