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

int n;
ld a[1000];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	cin >> n;
  	for (int i = 0; i < n; i++)
  		cin >> a[i];
  	sort(a,a+n);
  	reverse(a,a+n);

  	ld ans = a[0];

  	for (int i = 1; i < n; i++)
  		ans = 2.0*sqrt(ans*a[i]);

  	cout.precision(15);
  	cout << fixed << ans << endl;
	
  return 0;
}