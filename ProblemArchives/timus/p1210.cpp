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

int ans[50][50];



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  ans[0][0] = 0;


  int res = 1<<30;


  int n;
  scanf("%d",&n);
  for (int i = 1; i <= n; i++){
  	int k;
  	scanf("%d",&k);
  	for (int j = 1; j <= k; j++){
  		int m;
  		ans[i][j] = 1<<29;
  		for (int l = 1; ; l++){
  			int p,c;
			assert(scanf("%d",&p) == 1);
			if (p)
				scanf("%d",&c);
			else
				break;			
  			ans[i][j] = min(ans[i][j],ans[i-1][p] + c);
  		}
  		if (i == n)
  			res = min(res,ans[i][j]);  			
//  		cerr << i <<" "<<j<<" "<<ans[i][j] << endl;
  	}
  	scanf(" * ");
  }

  cout << res << endl;
                     
  return 0;
}