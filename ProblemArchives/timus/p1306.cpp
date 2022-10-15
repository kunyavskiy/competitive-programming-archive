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


const int MAXN = 150000;

int a[MAXN];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  
  int n;
  scanf("%d",&n);

  int ptr = 0;

  for (int i = 0; i < n; i++){
  	scanf("%d",&a[ptr++]);
  	if (ptr == MAXN) {
  		sort(a,a+ptr);
  		ptr = n/2 + 10;
  	}
  }

  sort(a,a+ptr);


  if (n % 2 == 1)
  	cout << a[n/2] << endl;
  else
  	cout << ((ll)a[n/2]+(ll)a[n/2-1])/2 << ((((ll)a[n/2] + (ll)a[n/2-1])%2 == 1)?".5\n":"\n");


  	

  return 0;
}