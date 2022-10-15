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
    #define LLD "I64d"
#else
    #define LLD "lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


bool ok[1100000];
bool ok2[1100000];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n;
  ll x;
  cin >> n;

  if (n)
  	cin >> x;
  else
  	x = 0;


  for (;n < 8; n++)
  	x = 10*x+1;
  ll coef = 1;

  for (;n < 12; n++){
  	x *= 10;
  	coef *= 10;
  }
  	
  for (int i = 2; i <= 1000000; i++){
  	if (!ok[i]){
  		for (int j = i; i*1LL*j <= 1000000; j++)
  			ok[i*j] = true;

  		for (ll k = x/i+(!!(x%i)); k*i <= x + coef; k++)
  			ok2[k*i-x] = true; 
  	}
  }
  
  for (int j = 0; j < coef; j++)
  	if (!ok2[j]){
  		printf("%012"LLD,x+j);
  		return 0;
  	}

  return 0;
}