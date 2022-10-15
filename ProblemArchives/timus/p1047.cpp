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

ld k,b,k1,b1;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    ld a0,an1;
    int n;
    cin >> n >> a0 >> an1;

    k = 0,k1 = 1;
    b = a0,b1 = 0;

    for (int i = 1; i <= n; i++){
    	ld ci; cin >> ci;
    	ld k2,b2;
    	k2 = 2*k1 - k;
    	b2 = 2*b1 + 2 * ci - b;
        k = k1, b = b1;
        k1 = k2,b1 = b2;
   }

//   cerr << k1 <<" "<<b1 << endl;

   cout.precision(2);
   cout << fixed << (an1 - b1)/k1 << endl;

  return 0;
}