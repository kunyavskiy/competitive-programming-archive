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

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int p,q;
  double P;
  scanf("%lf",&P);
  p = (P * 100 +0.5);	
  scanf("%lf",&P);
  q = (P * 100 + 0.5);



  for (int ans = 1; ; ans++){
  	int down = (ans*p)/10000+1;
  	int up = (ans * q -1)/10000;
//  	cerr << ans <<" "<<down <<" "<<up << endl;
  	if (down <= up){
  		cout << ans <<endl;
  		return 0;
  	}  		
  }

  return 0;
}