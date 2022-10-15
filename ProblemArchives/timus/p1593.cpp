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

int chksq(ll a){
	ll b = (ll)sqrt((ld)a);
	while (b*b > a)
		b--;
	while ((b+1)*(b+1) <= a)
		b++;
    if (b*b == a)
    	return b;
    return -1;
}

int getsq(ll a){
	ll b = (ll)sqrt((ld)a);
	while (b*b > a)
		b--;
	while ((b+1)*(b+1) <= a)
		b++;
   	return b;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  ll n;
  cin >> n;
  if (chksq(n) != -1){
  	printf("1\n");
  	return 0;
  }


  ll ptr1 = 0;
  ll ptr2 = getsq(n);

  for (;ptr1*ptr1 <= n; ptr1++){
  	for (;ptr2*ptr2 + ptr1*ptr1 > n; --ptr2);
  	if (ptr2*ptr2 + ptr1*ptr1 == n){
  		printf("2\n");
  		return 0;
  	}
  }

  while (n % 4 == 0)
  	n /= 4;


  printf("%d\n",3+(n%8==7));	
  return 0;
}