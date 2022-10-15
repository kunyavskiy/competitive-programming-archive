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

const int ans[37] = { 31 , 61 , 89 , 107 , 127 , 521 , 607 , 1279 , 2203 , 2281 , 3217 , 4253 , 4423 , 9689 , 9941 , 11213 , 19937 , 21701 , 23209 , 44497 , 86243 , 110503 , 132049 , 216091, 756839 , 859433 , 1257787 , 1398269 , 2976221 , 3021377 , 6972593 , 13466917 , 20996011 , 24036583 , 25964951 };
//                    8    9    10   11    12    13    14    15     16     17     18     19     20     21     22     23      24      25      26      27      28      29       30       31       32       33

bool check(int n){
	for (ll i = 2; i*i <= n; i++)
		if (n % i == 0)
			return false;
	return true;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  	int n;
  	cin >> n;

  	while (cin >> n){
	  	if (n >= 8){
  			cout << ans[n-8] << endl;
	  		continue;
  		}

	  	for (int i = 2;;i++){	
	  		if (check((1<<i) -1)){
  				--n;
	  			if (n == 0){
  					cout << i << endl;
	  				break;
  				}
	  		}

  		}
  	}

  return 0;
}